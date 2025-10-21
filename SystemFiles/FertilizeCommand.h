/**
 * @file FertilizeCommand.h
 * @brief this is the definition of FertilizeCommand class for plant fertilization operations
 * @author Karishma Boodhoo
 * @date 13-10-2025
 */

#ifndef FERTILIZECOMMAND_H
#define FERTILIZECOMMAND_H

#include "CareCommand.h"
#include "Plant.h"

/**
 * @class FertilizeCommand
 * @brief this is the concrete command for fertilizing plants in the nursery
 * This class implements the Fertilize operation and it encapsulates the details of applying fertilizer to specific plants, allowing the operation to be logged, and executed
 */

class FertilizeCommand : public CareCommand{
    private:
        Plant* plant;
        std::string fertilizerType;
    public:
        /**
         * @brief this is a constructor that constructs a FertilizeCommand for a specific plant
         * @param plant this is a pointer to the plant that will receive fertilizer
         * @param type this is the type of fertilizer to apply
         */
        FertilizeCommand(Plant* plant, const std::string& type);

        /**
         * @brief this function executes the fertilization operation
         * it applies the specified fertilizer to the plant and updates the plants health and nutrient status accordingly
         */
        void execute();

        /**
         * @brief this function gets a description of the fertilization command
         * @return std::string Description of the fertilization action
         */
        std::string getDescription() const;

        /**
         * @brief this function logs the fertilization operation
         * it records details about the fertilization for plant care history tracking
         */
        void logAction() const;
};

#endif