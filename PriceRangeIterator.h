/**
 * @file PriceRangeIterator.h
 * @brief Concrete Iterator that filters plants by price range
 */
#ifndef PRICERANGEITERATOR_H
#define PRICERANGEITERATOR_H

#include "Iterator.h"
#include "PlantInventory.h"
#include <vector>
/**
 * @class PriceRangeIterator
 * @brief Iterator that traverses plants within a specific price range
 * 
 * Useful for customers browsing plants within their budget
 */
class PriceRangeIterator : public Iterator { 
public:
    /**
     * @brief Constructs a PriceRangeIterator
     * @param inventory Pointer to the PlantInventory to iterate over
     * @param min Minimum price (inclusive)
     * @param max Maximum price (inclusive)
     */
    PriceRangeIterator(PlantInventory* inventory, double min, double max);
    
    /**
     * @brief Destructor
     */
    ~PriceRangeIterator();
    
    /**
     * @brief Positions the iterator to the first plant in range
     */
    void first() override;
    
    /**
     * @brief Moves the iterator to the next plant in range
     */
    void next() override;
    
    /**
     * @brief Checks if iteration is complete
     * @return True if no more plants in range, false otherwise
     */
    bool isDone() const override;
    
    /**
     * @brief Gets the current plant
     * @return Pointer to the current Plant object
     */
    Plant* currentItem() const override;
    
    /**
     * @brief Checks if there is a next plant in range
     * @return True if there is a next plant, false otherwise
     */
    bool hasNext() const override;
    /**
     * @brief Filters plants by price range
     * @param inventory Pointer to the PlantInventory to filter
     */
    void filterByPrice(PlantInventory* inventory);

    private:
    std::vector<Plant*> filteredPlants;
    double minPrice;
    double maxPrice;
};
#endif