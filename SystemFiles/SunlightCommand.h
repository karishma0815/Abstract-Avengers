/**
 * @file SunlightCommand.h
 * @brief this is the Ddefinition of SunlightCommand class for plant sunlight management
 * @author Karishma Boodhoo
 * @date 13-10-2025
 */

#ifndef SUNLIGHTCOMMAND_H
#define SUNLIGHTCOMMAND_H

#include "CareCommand.h"
#include "Plant.h"

/**
 * @class SunlightCommand
 * @brief this is a concrete command for managing plant sunlight exposure
 * this class implements the Sunlight operation as a command object in the Command pattern. It encapsulates the details of providing specific sunlight
 * conditions to plants, including duration and intensity levels, allowing the operation to be queued, logged, and executed as part of staff task management.
 */

class SunlightCommand : public CareCommand{
    private:
        Plant* plant;
        int hours;
        std::string intensity; //can be low/medium/high
    public:
        /**
         * @brief this is a constructor that constructs a SunlightCommand for a specific plant
         * @param plant this is a pointer to the plant that will receive sunlight
         * @param hours this is the Duration of sunlight exposure in hours
         * @param intensity this is the sunlight intensity level ("low", "medium", "high")
         */
        SunlightCommand(Plant* plant, int hours, const std::string& intensity);

        /**
         * @brief this function executes the sunlight exposure operation
         * it provides the specified sunlight conditions to the plant, affecting its health and growth based on the duration and intensity levels. The plant's response depends on its specific sunlight preferences
         */
        void execute();

        /**
         * @brief this function gets a description of the sunlight command
         * @return std::string Description of the sunlight exposure action
         */
        std::string getDescription() const;

        /**
         * @brief this function logs the sunlight exposure operation
         * it records details about the sunlight conditions provided for auditing and plant care history tracking, including duration and intensity levels
         */
        void logAction() const;
};

#endif