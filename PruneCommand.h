/**
 * @file PruneCommand.h
 * @brief this is the definition of PruneCommand class for plant pruning operations
 * @author Karishma Boodhoo
 * @date 13-10-2025
 */

#ifndef PRUNECOMMAND_H
#define PRUNECOMMAND_H

#include "CareCommand.h"
#include "Plant.h"

/**
 * @class PruneCommand
 * @brief this is the concrete command for pruning plants in the nursery
 * this class implements the Prune operation as a command object in the Command pattern. It encapsulates the details of pruning specific plants
 * with controlled intensity levels, allowing the operation to be queued, logged, and executed as part of staff task management
 */

class PruneCommand : public CareCommand{
    private:
        Plant* plant;
        int intensity;
    public:
        /**
         * @brief this is a constructor that constructs a PruneCommand for a specific plant
         * @param plant this is a pointer to the plant that will be pruned
         * @param intensity this is the the pruning intensity level typically 1-3
         */
        PruneCommand(Plant* plant, int intensity);

        /**
         * @brief this function executes the pruning operation
         * it performs pruning on the specified plant according to the intensity level, which affects the plant's health and growth characteristics
         */
        void execute();

        /**
         * @brief this function gets a description of the pruning command
         * @return std::string Description of the pruning action
         */
        std::string getDescription() const;

        /**
         * @brief this function logs the pruning operation
         * it records details about the pruning activity for auditing and plant maintenance history tracking
         */
        void logAction() const;
};

#endif