/**
 * @file SalesAssistantFactory.h
 * @brief this is the definition of SalesAssistantFactory class for creating sales assistant instances
 * @author Karishma Boodhoo
 * @date 13-10-2025
 */

#ifndef SALESASSISTANTFACTORY_H
#define SALESASSISTANTFACTORY_H

#include "StaffFactory.h"

/**
 * @class SalesAssistantFactory
 * @brief this is the concrete factory for creating SalesAssistant objects
 * this class implements the Factory Method pattern to create and configure SalesAssistant instances
 */

class SalesAssistantFactory : public StaffFactory{
    public:
        /**
         * @brief this function creates a new SalesAssistant instance
         * @return this is a Staff* pointer to the newly created SalesAssistant object
         * it constructs a SalesAssistant with default parameters including a standard commission rate
         */
        Staff* createStaff();

        /**
         * @brief this function gets the name of the role this factory creates
         * @return std::string The role name "Sales Assistant"
         */
        std::string getRoleName() const;
};

#endif