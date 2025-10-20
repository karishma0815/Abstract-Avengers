/**
 * @file AddToCart.h
 * @brief Concrete CustomerCommand to add a plant to the cart
 * Implements the CustomerCommand interface to encapsulate the action of adding
 * a plant to the shopping cart.
 */
#ifndef ADDTOCART_H
#define ADDTOCART_H
#include "CustomerCommand.h"

#include "Plant.h"
#include "CartIterator.h"
#include "PlantInventory.h"

class AddToCart : public CustomerCommand {
public:
    /**
     * @brief Constructs an AddToCart CustomerCommand
     * @param plant Pointer to the Plant to add to the cart
     * @param cartIterator Pointer to the CartIterator managing the cart
     */
    AddToCart();
    /**
     * @brief Destructor
     */
    ~AddToCart();
    /**
     * @brief Executes the add to cart CustomerCommand
     */
    void execute(Plant* plant, PlantInventory* cartInven) override;

};
#endif