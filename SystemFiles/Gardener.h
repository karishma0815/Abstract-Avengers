/**
 * @file Gardener.h
 * @brief this is the definition of Gardener class for plant care specialists
 * @author Karishma Boodhoo
 * @date 13-10-2025
 */

 #ifndef GARDENER_H
#define GARDENER_H

#include "Staff.h"

/**
 * @class Gardener
 * @brief this is the staff member responsible for plant cultivation and maintenance
 * This class represents gardening professionals who focus on plant care, cultivation, and maintenance within the nursery. Gardeners use the
 * Command pattern to execute various plant care routines and coordinate with other staff through the Mediator pattern for inventory management.
 */

class Gardener : public Staff{
    private:
        std::string expertise;
    public:
        /**
         * @brief this is a constructor that constructs a Gardener with specific expertise
         * @param name this is the gardener's name
         * @param id this is a unique identifier for the gardener
         * @param med this is a oointer to the inventory mediator for stock coordination
         * @param expertise this is the gardener's area of specialization
         */
        Gardener(const std::string& name, int id, InventoryMediator* med, const std::string& expertise);

        /**
         * @brief this function gets the role description of this staff member
         * @return std::string The role name including specialization
         */
        std::string getRole() const;

        /**
         * @brief this function performs plant care duties
         * it executes gardening tasks and plant maintenance routines using the Command pattern, 
         * this includes watering, pruning, fertilizing and other plant care operations specific to the gardener's expertise.
         */
        void careForPlants();
};

#endif