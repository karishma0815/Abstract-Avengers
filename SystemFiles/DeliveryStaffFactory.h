/**
 * @file DeliveryStaffFactory.h
 * @brief this is the definition of DeliveryStaffFactory class for creating delivery staff instances
 * @author Karishma Boodhoo
 * @date 13-10-2025
 */

#ifndef DELIVERYSTAFFFACTORY_H
#define DELIVERYSTAFFFACTORY_H

#include "StaffFactory.h"

/**
 * @class DeliveryStaffFactory
 * @brief this is the concrete factory for creating DeliveryStaff objects
 * This class implements the Factory Method pattern to create and configure DeliveryStaff instances
 */

class DeliveryStaffFactory : public StaffFactory{
    public:
        /**
         * @brief this function creates a new DeliveryStaff instance
         * @return this is a Staff* pointer to the newly created DeliveryStaff object
         * it constructs a DeliveryStaff with default parameters
         */
        Staff* createStaff();

        /**
         * @brief this function gets the name of the role this factory creates
         * @return std::string The role name "Delivery Staff"
         */
        std::string getRoleName() const;
};

#endif