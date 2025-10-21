/**
 * @file WaterCommand.h
 * @brief this is the definition of WaterCommand class for plant watering operations
 * @author Karishma Boodhoo
 * @date 13-10-2025
 */

#ifndef WATERCOMMAND_H
#define WATERCOMMAND_H

#include "CareCommand.h"
#include "Plant.h"

/**
 * @class WaterCommand
 * @brief this is the concrete command for watering plants in the nursery
 * this class implements the Water operation as a command object in the Command pattern. It encapsulates the details of providing specific water
 * amounts to plants, allowing the operation to be queued, logged, and executed as part of staff task management.
 */

class WaterCommand : public CareCommand{
    private:
        Plant* plant;
        double amount;
    public:
        /**
         * @brief this is a constructor that constructs a WaterCommand for a specific plant
         * @param plant this is a pointer to the plant that will receive water
         * @param amount this is the amount of water to provide in liters
         */
        WaterCommand(Plant* plant, double amount);

        /**
         * @brief this function executes the watering operation
         * it provides the specified amount of water to the plant, affecting its hydration level and overall health, The plant's response
         * depends on its specific water requirements and current condition
         */
        void execute();

        /**
         * @brief this function gets a description of the watering command
         * @return std::string Description of the watering action
         */
        std::string getDescription() const;

        /**
         * @brief this function logs the watering operation
         * it records details about the watering for auditing and plant care history tracking, including the amount of water provided
         */
        void logAction() const;
};

#endif