/**
 * @file Invoker.h
 * @brief Invoker class for the CustomerCommand design pattern  
 */
#ifndef INVOKER_H
#define INVOKER_H   
#include "CustomerCommand.h"
#include"Plant.h"
#include"PlantInventory.h"
#include"CartIterator.h"
#include <vector>
#include <iostream>
/**
 * @class Invoker
 * @brief Invoker that executes commands
 * The Invoker class is responsible for executing CustomerCommands. It holds a reference
 * to a CustomerCommand object and calls its execute method when requested.
 */

class Invoker {
public:
    /**
     * @brief Constructs an Invoker with the given CustomerCommand
     * @param cmd Pointer to the CustomerCommand to execute
     */
    Invoker(CustomerCommand* cmd);
    /**
     * @brief Executes the stored CustomerCommands
     */
    ~Invoker();
    void execute(Plant* plant, PlantInventory* cartInven);
    /**
     * @brief Sets a new CustomerCommand to be executed
     * @param cmd Pointer to the new CustomerCommand
     */
    void setCommand(CustomerCommand* cmd);

    void clearCommand();
    /**
     * @brief Executes all the CustomerCommands
     */
    void executeALL();

    /**
     * @brief Stores a cmd for later execution, allows customers to the 'undo' options.
     * @param cmd Pointer to the CustomerCommand to store
     */
    void storeCommand(CustomerCommand*cmd);


private:        
    std::vector<CustomerCommand*> cmd;

};
#endif
