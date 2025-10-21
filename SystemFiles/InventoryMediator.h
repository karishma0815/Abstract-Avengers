/**
 * @file InventoryMediator.h
 * @brief this is the definition of InventoryMediator interface for inventory coordination
 * @author Karishma Boodhoo
 * @date 13-10-2025
 */

#ifndef INVENTORYMEDIATOR_H
#define INVENTORYMEDIATOR_H

#include <string>

class Staff;
class Plant;

/**
 * @class InventoryMediator
 * @brief this is an abstract mediator interface for coordinating inventory operations between staff
 * This class defines the Mediator pattern interface for handling inventory-related communication between different staff members. It decouples staff classes
 * allowing staff to communicate through the mediator rather than directly with each other.
 */

class InventoryMediator{
    public:
        /**
         * @brief this is a virtual destructor for cleanup of derived classes
         */
        virtual ~InventoryMediator();

        /**
         * @brief this function notifies the mediator of an inventory-related event
         * @param sender this is the staff member triggering the event
         * @param event this is the type of inventory event
         * @param plant this is the plant affected by the event
         * @param quantity this is the quantity involved in the event
         * Staff members call this method to report inventory changes. The mediator then coordinates the necessary updates and notifications to other staff members
         */
        virtual void notify(Staff* sender, const std::string& event, Plant* plant, int quantity) = 0;
};

#endif