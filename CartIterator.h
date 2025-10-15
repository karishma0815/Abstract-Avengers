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

};
#endif