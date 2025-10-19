/**
 * @file CartIterator.h
 * @brief Concrete Iterator for iterating through plants in the customer's cart
 */
#ifndef CARTITERATOR_H
#define CARTITERATOR_H

#include "Iterator.h"
#include "PlantInventory.h"
#include <vector>
#include <string>
class PlantInventory;
/**
 * @class CartIterator
 * @brief Concrete iterator that traverses through all plants in the customer's cart
 * 
 * Implements the Iterator interface to provide sequential access to plants
 * in the cart.
 */
class CartIterator : public Iterator {
    public:
    /**
     * @brief Constructs a CartIterator
     * @param inventory Pointer to the PlantInventory representing the cart
     */
    CartIterator(PlantInventory* inventory);
    /**
     * @brief Destructor
     */
    ~CartIterator();
    /**
     * @brief Positions the iterator to the first plant in the cart
     */
    void first() override;
    
    /**
     * @brief Moves the iterator to the next plant in the cart
     */
    void next() override;
    
    /**
     * @brief Checks if iteration is complete
     * @return True if no more plants, false otherwise
     */
    bool isDone() const override;
    
    /**
     * @brief Gets the current plant in the cart
     * @return Pointer to the current Plant object
     */
    Plant* currentItem() const override;
    
    /**
     * @brief Checks if there is a next plant in the cart
     * @return True if there is a next plant, false otherwise
     */
    bool hasNext() const override;

    private:
    int currentIndex;///Current index in the cart

};
#endif