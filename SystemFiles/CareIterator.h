/**
 * @file CareIterator.h
 * @brief Concrete Iterator that filters plants by care requirements
 */
#ifndef CAREITERATOR_H
#define CAREITERATOR_H

#include "Iterator.h"
#include "PlantInventory.h"
#include <vector>
#include <string>
/**
 * @class CareIterator
 * @brief Iterator that traverses plants with specific care requirements
 * 
 * Useful for customers who want plants with specific maintenance levels
 * (e.g., "low", "medium", "high" maintenance) or specific care keywords
 */
class CareIterator:public Iterator {
public:
    /**
     * @brief Constructs a CareIterator
     * @param inventory Pointer to the PlantInventory to iterate over
     * @param keyword Care keyword to filter by (e.g., "low", "daily watering")
     */
    CareIterator(PlantInventory* inventory, const std::string& care);
    /**
     * @brief Destructor
     */
    ~CareIterator();
    /**
     * @brief Positions the iterator to the first matching plant
     */
    void first() override;
    
    /**
     * @brief Moves the iterator to the next matching plant
     */
    void next() override;
    
    /**
     * @brief Checks if iteration is complete
     * @return True if no more matching plants, false otherwise
     */
    bool isDone() const override;
    
    /**
     * @brief Gets the current plant
     * @return Pointer to the current Plant object
     */
    Plant* currentItem() const override;
    
    /**
     * @brief Checks if there is a next matching plant
     * @return True if there is a next plant, false otherwise
     */
    bool hasNext() const override;
    /**
     * @brief Filters plants by care requirements
     * @param inventory Pointer to the PlantInventory to filter
     */
    void filterByCare(PlantInventory* inventory);

    private:
    std::string careKey;
};
#endif