/**
 * @file GardenerFactory.h
 * @brief this is the definition of GardenerFactory class for creating gardener instances
 * @author Karishma Boodhoo
 * @date 13-10-2025
 */

#ifndef GARDENERFACTORY_H
#define GARDENERFACTORY_H

#include "StaffFactory.h"

/**
 * @class GardenerFactory
 * @brief this is the concrete factory for creating Gardener objects
 * This class implements the Factory Method pattern to create and configure Gardener instances
 */

class GardenerFactory : public StaffFactory{
    public:
        /**
         * @brief this function creates a new Gardener instance
         * @return ths is a Staff* pointer to the newly created Gardener object
         * it constructs a Gardener with default parameters including a general expertise area
         */
        Staff* createStaff();

        /**
         * @brief this function gets the name of the role this factory creates
         * @return std::string The role name "Gardener"
         */
        std::string getRoleName() const;
};

#endif