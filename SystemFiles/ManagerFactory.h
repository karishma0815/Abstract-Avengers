/**
 * @file ManagerFactory.h
 * @brief this is the definition of ManagerFactory class for creating manager instances
 * @author Karishma Boodhoo
 * @date 13-10-2025
 */

#ifndef MANAGERFACTORY_H
#define MANAGERFACTORY_H

#include "StaffFactory.h"

/**
 * @class ManagerFactory
 * @brief this is the concrete factory for creating Manager objects
 * this class implements the Factory Method pattern to create and configure Manager instances
 */

class ManagerFactory : public StaffFactory{
    public:
        /**
         * @brief this functioncCreates a new Manager instance
         * @return this is the Staff* pointer to the newly created Manager object
         * it constructs a Manager with default parameters including operations department assignment
         */
        Staff* createStaff();

        /**
         * @brief this function gets the name of the role this factory creates
         * @return std::string The role name "Manager"
         */
        std::string getRoleName() const;
};

#endif