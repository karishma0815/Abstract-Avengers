/**
 * @file DeliveryStaff.h
 * @brief this is the definition of DeliveryStaff class for handling plant deliveries
 * @author Karishma Boodhoo
 * @date 13-10-2025
 */

#ifndef DELIVERYSTAFF_H
#define DELIVERYSTAFF_H

#include "Staff.h"

/**
 * @class DeliveryStaff
 * @brief it has staff members responsible for plant transportation and deliveries
 * This class represents delivery personnel in the system who handle and delivery of plants to customers 
 */

class DeliveryStaff : public Staff{
    private:
        std::string vehicleType;
    public:
        /**
         * @brief this is a constructor that constructs a DeliveryStaff member
         * @param name this is the staff member's name
         * @param id this is a unique identifier for the staff member
         * @param med this is a pointer to the inventory mediator for coordination
         * @param vehicle this is a type of vehicle the staff member operates
         */
        DeliveryStaff(const std::string& name, int id, InventoryMediator* med, const std::string& vehicle);

        /**
         * @brief this function gets the role description of this staff member
         * @return std::string The role name "Delivery Staff"
         */
        std::string getRole() const;

        /**
         * @brief this function performs plant related duties specific to delivery staff
         * the delivery staff handle plants during transportation but don't perform actual care routines
         */
        void careForPlants();
};

#endif