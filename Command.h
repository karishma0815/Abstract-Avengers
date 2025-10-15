/**
 * @file Command.h
 * @brief Abstract Command interface for the Command design pattern
 */
#ifndef COMMAND_H
#define COMMAND_H  

#include "State.h"
/**
 * @class Command
 * @brief Abstract interface for executing operations
 * 
 * Defines the interface for command objects that encapsulate
 * a request as an object, allowing for parameterization and queuing of requests.
 */
class Command {
public:
    /**
     * @brief Virtual destructor
     */
    virtual ~Command();
    /**
     * @brief Executes the command
     */
    virtual void execute(State& state) = 0;
};
#endif