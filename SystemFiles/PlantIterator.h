/**
 * @file PlantIterator.h
 * @brief Concrete Iterator for iterating through all plants
 */
#ifndef PLANTITERATOR_H
#define PLANTITERATOR_H
#include "Iterator.h"

//Concreteaggregate class 
#include "PlantInventory.h"
#include <vector>
#include <string>

class PlantInventory;
/**
 * @class PlantIterator
 * @brief Concrete iterator that traverses through all plants in inventory,this can be 
 * used by both customers and staff to view plants.
 * 
 * Implements the Iterator interface to provide sequential access to plants
 */
class PlantIterator : public Iterator {
public:
    /**
     * @brief Constructs a PlantIterator for the given inventory
     * @param inventory Pointer to the PlantInventory to iterate over
     */
    PlantIterator(PlantInventory* inventory,const std::string& type="");
    /**
     * @brief Destructor
     */
    ~PlantIterator();
    
    /**
     * @brief Positions the iterator to the first element
     */
    void first() override;
    /**
     * @brief Moves the iterator to the next element
     */
    void next() override;
    /**
     * @brief Checks if iteration is complete
     * @return True if no more elements, false otherwise
     */
    bool isDone() const override;
     /**
     * @brief Gets the current element
     * @return Pointer to the current Plant object
     */
    Plant* currentItem() const override;
    /**
     * @brief Checks if there is a next element
     * @return True if there is a next element, false otherwise
     */
    bool hasNext() const override;
    /**
     * @brief Filters the iterator to only include plants of a specific type
     * @param inventory Pointer to the PlantInventory to filter
     */
    void filterByType(PlantInventory* inventory);

    private:
    std::vector<Plant*> plants;
    int currentIndex;   
    std::string type;//filter for iterating through plants
};
#endif

