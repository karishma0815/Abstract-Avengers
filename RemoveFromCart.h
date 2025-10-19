/**
 * @file RemoveFromCart.h
 * @brief Concrete Command to remove a plant from the cart
 */
#ifndef REMOVEFROMCART_H
#define REMOVEFROMCART_H

#include "Command.h"

#include "Plant.h"
#include "CartIterator.h"
#include "PlantInventory.h"

class RemoveFromCart : public Command {
    public:
    /**
     * @brief Constructs a RemoveFromCart command
     * @param plant Pointer to the Plant to remove from the cart
     * @param cartIterator Pointer to the CartIterator managing the cart
     */
    RemoveFromCart();
    /**
     * @brief Destructor
     */
    ~RemoveFromCart();
    /**
     * @brief Executes the remove from cart command
     */
    void execute(Plant* plant, PlantInventory* cartIterator) override;

    ///Pointer to the CartIterator managing the cart, here is when iterator comes into use!!
};
#endif