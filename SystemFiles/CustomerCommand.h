/**
 * @file CustomerCommand.h
 * @brief Abstract CustomerCommand interface for the CustomerCommand design pattern
 */
#ifndef CUSTOMERCOMMAND_H
#define CUSTOMERCOMMAND_H  

#include<string>
#include"PlantInventory.h"
#include"CartIterator.h"

#include<iostream>
/**
 * @class CustomerCommand
 * @brief Abstract interface for executing operations
 * 
 * Defines the interface for CustomerCommand objects that encapsulate
 * a request as an object, allowing for parameterization and queuing of requests.
 */
class CustomerCommand {
    public:
    /**
     * @brief Virtual destructor
     */
    virtual ~CustomerCommand();
    /**
     * @brief Executes the CustomerCommand
     */
    virtual void execute(Plant* plant, PlantInventory* cartInven) = 0;

    protected:
    Plant* plant;
    PlantInventory* cartInven;

};
#endif