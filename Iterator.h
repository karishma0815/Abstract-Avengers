/**
 * @file Iterator.h
 * @brief Abstract Iterator interface for the Iterator design pattern
 */
#ifndef ITERATOR_H
#define ITERATOR_H
#include "Plant.h"
#include <vector>
/**
 * @class Iterator
 * @brief Abstract interface for accessing and traversing elements
 * 
 * Defines the interface for iterating through a collection of plants
 * following the Iterator design pattern
 */
class Iterator {
public:
    /**
     * @brief Virtual destructor
     */
    virtual ~Iterator() {}
    /**
     * @brief Positions the iterator to the first element
     */
    virtual void first() = 0;
    /**
     * @brief Moves the iterator to the next element
     */
    virtual void next() = 0;
        /**
     * @brief Checks if iteration is complete
     * @return True if no more elements, false otherwise
     */
    virtual bool isDone() const = 0;
    /**
     * @brief Gets the current element
     * @return Pointer to the current Plant object
     */
    virtual Plant* currentItem() const = 0;
    /**
     * @brief Checks if there is a next element
     * @return True if there is a next element, false otherwise
     */
    virtual bool hasNext() const = 0;

    protected:
    /**
     * @brief List of filtered plants for iteration. Used by all concrete iterators
     */
    std::vector<Plant*> filteredPlants;
    int current;
};
#endif 