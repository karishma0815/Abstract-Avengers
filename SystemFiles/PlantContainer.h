/**
 * @file PlantContainer.h
 * @brief Abstract Aggregate interface for the Iterator design pattern
 */
#ifndef PLANTCONTAINER_H
#define PLANTCONTAINER_H

#include "Plant.h"
#include "Iterator.h"
//#include"PlantInventory.h"
class PlantInventory;
/**
 * @class PlantContainer
 * @brief Abstract interface for creating Iterator objects
 * 
 * Defines the aggregate interface that creates appropriate iterators
 * following the Iterator design pattern
 */
class PlantContainer {
public:
    /**
     * @brief Virtual destructor
     */
    virtual ~PlantContainer();
    /**
     * @brief Creates an iterator for this container
     * @return Pointer to a new Iterator object
     */
    virtual Iterator* createPlantIterator(PlantInventory* inventory) = 0;
    /**
     * @brief Creates a price range iterator for this container
     * @return Pointer to a new PriceRangeIterator object
     */
    virtual Iterator* createPriceRangeIterator(PlantInventory*, double min, double max) = 0;
    /**
     * @brief Creates a cart iterator for this container
     * @return Pointer to a new CartIterator object
     */
    virtual Iterator* createCartIterator(PlantInventory* inventory) = 0;
    /**
     * @brief Adds a plant to the container
     * @param plant Pointer to the Plant to add
     */
    virtual void add(Plant* plant) = 0;
    /**
     * @brief Removes a plant from the container
     * @param plant Pointer to the Plant to remove
     */
    virtual void remove(Plant* plant) = 0;
    
    /**
     * @brief Gets the number of plants in the container
     * @return The size of the container
     */
    virtual int size() const = 0;
    
    /**
     * @brief Checks if the container is empty
     * @return True if empty, false otherwise
     */
    virtual bool isEmpty() const = 0;
};

#endif