/**
 * @file Invoker.h
 * @brief Invoker class for the Command design pattern  
 */
#ifndef INVOKER_H
#define INVOKER_H   
#include "Command.h"
#include "State.h"
#include <vector>
/**
 * @class Invoker
 * @brief Invoker that executes commands
 * The Invoker class is responsible for executing commands. It holds a reference
 * to a Command object and calls its execute method when requested.
 */

class Invoker {
public:
    /**
     * @brief Constructs an Invoker with the given command
     * @param command Pointer to the Command to execute
     */
    Invoker(Command* command);
    /**
     * @brief Executes the stored commands
     */
    void execute(State& state);
    /**
     * @brief Sets a new command to be executed
     * @param command Pointer to the new Command
     */
    void setCommand(Command* command);

    void clearCommand();
    /**
     * @brief Executes all the commands
     */
    void executeALL();
    /**
     * @brief Stores a command for later execution, allows customers to the 'undo' options.
     */
    void storeCommand(Command* command);


private:        
    std::vector<Command*> command;///Pointer to the Command to execute

};
#endif
