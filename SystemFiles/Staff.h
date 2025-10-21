/**
 * @file Staff.h
 * @brief this is the efinition of Staff base class for all nursery staff members
 * @author Karishma Boodhoo
 * @date 13-10-2025
 */

#ifndef STAFF_H
#define STAFF_H

#include "CareCommand.h"
#include "InventoryMediator.h"
#include <vector>
#include <string>

/**
 * @class Staff
 * @brief this is the abstract base class for all staff members in the nursery system
 * this class serves as the foundation for the Factory Method pattern, defining the common interface and functionality for all staff roles. It integrates
 * both Command pattern for task management and Mediator pattern for inventory coordination while allowing specialization through derived classes
 */

class Staff{
    protected:
        std::vector<CareCommand*> taskQueue;
        InventoryMediator* inventoryCoordinator;
        std::string name;
        int id;
    public:
        /**
         * @brief this is a constructor that constructs a Staff member with basic information
         * @param staffName this is the staff members name
         * @param staffId this is a unique identifier for the staff member
         * @param med this is a pointer to the inventory mediator for coordination
         */
        Staff(const std::string& staffName, int staffId, InventoryMediator* med);

        /**
         * @brief this is a virtual destructor for cleanup of derived classes
         */
        virtual ~Staff();
        
        /**
         * @brief this function adds a plant care command to the task queue
         * @param task this is a pointer to the CareCommand to be queued
         * it queues a plant care command for later execution
         */
        void addTask(CareCommand* task);

        /**
         * @brief this function executes all queued plant care commands
         * it processes all commands in the task queue in sequence, executing each one and then clearing the queue and it provides logging of the execution process
         */
        void performTasks();

        /**
         * @brief this function clears all pending tasks from the queue
         * it removes all queued plant care commands without executing them, properly cleaning up the command objects to prevent memory leaks
         */
        void clearTasks();
        
        /**
         * @brief this function assigns an inventory coordinator to this staff member
         * @param coordinator this is a pointer to the inventory mediator for coordination
         * it sets the mediator that this staff member will use for inventory related communications, enabling coordination with other staff members.
         */
        void setInventoryCoordinator(InventoryMediator* coordinator);

        /**
         * @brief this function notifies the inventory coordinator of an event
         * @param event this is the type of inventory event
         * @param plant this is the plant affected by the event
         * @param quantity this is the quantity involved in the event
         * it sends inventory related notifications through the mediator pattern, allowing staff to communicate about stock changes without direct dependencies between staff classes.
         */
        void notify(const std::string& event, Plant* plant, int quantity);
        
        /**
         * @brief this function gets the staff members name
         * @return std::string The staff member's name
         */
        std::string getName() const;

        /**
         * @brief this function gets the staff members unique identifier
         * @return int this is the staff members ID
         */
        int getId() const;

        /**
         * @brief this function gets the role description of this staff member
         * @return std::string The specific role name
         * this is a pure virtual method that must be implemented by derived classes to return their specific role description like gardener
         */
        virtual std::string getRole() const = 0;
        
        /**
         * @brief this function performs plant care duties specific to the staff role
         * this is a pure virtual method that must be implemented by derived classes to define their specific plant care responsibilities
         */
        virtual void careForPlants() = 0;
};

#endif