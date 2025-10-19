/**
 * @file AddToCart.h
 * @brief Concrete Command to add a plant to the cart
 * Implements the Command interface to encapsulate the action of adding
 * a plant to the shopping cart.
 */
#ifndef ADDTOCART_H
#define ADDTOCART_H
#include "Command.h"

#include "Plant.h"
#include "CartIterator.h"
#include "PlantInventory.h"

class AddToCart : public Command {
public:
    /**
     * @brief Constructs an AddToCart command
     * @param plant Pointer to the Plant to add to the cart
     * @param cartIterator Pointer to the CartIterator managing the cart
     */
    AddToCart();
    /**
     * @brief Destructor
     */
    ~AddToCart();
    /**
     * @brief Executes the add to cart command
     */
    void execute(Plant* plant, PlantInventory* cartIterator) override;

};
#endif