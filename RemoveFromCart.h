/**
 * @file RemoveFromCart.h
 * @brief Concrete CustomerCommand to remove a plant from the cart
 */
#ifndef REMOVEFROMCART_H
#define REMOVEFROMCART_H

#include "CustomerCommand.h"

#include "Plant.h"
#include "CartIterator.h"
#include "PlantInventory.h"

class RemoveFromCart : public CustomerCommand {
    public:
    /**
     * @brief Constructs a RemoveFromCart CustomerCommand
     * @param plant Pointer to the Plant to remove from the cart
     * @param cartIterator Pointer to the CartIterator managing the cart
     */
    RemoveFromCart();
    /**
     * @brief Destructor
     */
    ~RemoveFromCart();
    /**
     * @brief Executes the remove from cart CustomerCommand
     */
    void execute(Plant* plant, PlantInventory* cartInven) override;

    ///Pointer to the CartIterator managing the cart, here is when iterator comes into use!!
};
#endif