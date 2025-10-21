/**
 * @file Manager.h
 * @brief this is the definition of Manager class for overseeing nursery operations and handling escalations
 * @author Karishma Boodhoo
 * @date 13-10-2025
 */

#ifndef MANAGER_H
#define MANAGER_H

#include "Staff.h"
#include "CustomerQueryHandler.h"

/**
 * @class Manager
 * @brief this is the senior staff member responsible for nursery oversight and escalated customer issues
 * This class represents management staff who participate in both the Factory Method pattern as Staff members and the Chain of Responsibility pattern as final escalators
 * for customer queries. Managers handle complex customer complaints
 */

class Manager : public Staff, public CustomerQueryHandler{
    private:
        std::string department;
    public:
        /**
         * @brief this is a constructor that constructs a Manager with departmental responsibility
         * @param name this is the manager's name
         * @param id this is a unique identifier for the manager
         * @param med this is a pointer to the inventory mediator for coordination
         * @param dept this is the department the manager oversees
         */
        Manager(const std::string& name, int id, InventoryMediator* med, const std::string& dept);

        /**
         * @brief this function gets the role description of this staff member
         * @return std::string The role name including department
         */
        std::string getRole() const;

        /**
         * @brief this function performs plant care oversight duties
         * the managers oversee plant care operations rather than performing hands-on work. This includes monitoring plant health, coordinating
         * care schedules, and ensuring quality standards are maintained.
         */
        void careForPlants();

        /**
         * @brief this function handles escalated customer queries requiring managerial authority
         * @param query this is the customer query to process
         * it processes customer complaints and special requests that require managerial approval or authority. Serves as the final escalation
         * point in the customer query chain for issues that cannot be resolved by junior staff or specialists.
         */
        void handleQuery(const CustomerQuery& query);

        /**
         * @brief this function determines if this handler can process the given customer query
         * @param query this is the customer query to evaluate
         * @return it returns true if this handler can resolve the query otherwise false
         * the managers handle customer complaints requiring resolution authority and special requests needing managerial approval. Routine questions
         * are handled by junior staff and specialists earlier in the chain
         */
        bool canHandle(const CustomerQuery& query) const;
};

#endif