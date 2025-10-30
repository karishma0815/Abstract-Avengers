/**
 * @file CareCommand.h
 * @brief This is the implementation of the command design pattern for plant care operations
 * @author Karishma Boodhoo
 * @date 13-10-2025
 */

#ifndef CARECOMMAND_H
#define CARECOMMAND_H

#include <string>

class Plant;

/**
 * @class CareCommand
 * @brief This is an abstract base class defining the command interface for the plant care operations
 * This class provides the basic interface for encapsulating plant care operations as objects. Concrete command classes implement specific care actions like watering,
 * fertilizing, pruning and sunlight. it also allows for queuing, logging, and executing plant care routines
 */

class CareCommand{
    public:
        /**
         * @brief this is a virtual destructor for proper cleanup of the derived classes
         */
        virtual ~CareCommand(){};

        /**
         * @brief this function executes the plant care command
         * it performs the specific plant care action associated with this command and it must be implemented by all concrete command classes
         */
        virtual void execute() = 0;

        /**
         * @brief this is a pure virtual function that gives a description of the command when implemented in its derived classes
         * @return std::string this is a description of what the command does
         * it returns a string describing the plant care action that this command will perform when executed
         */
        virtual std::string getDescription() const = 0;

        /**
         * @brief this is pure virtual function that logs the command execution for auditing purposes
         * it outputs logging information about the command being executed.
         */
        virtual void logAction() const = 0;
};

#endif