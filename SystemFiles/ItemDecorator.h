/*Abstract Avengers*/

/**
 * @file ItemDecorator.h
 * @brief Decorator base for personalization layers
 * @author Taskeen Abdoola
 * @date 2025-10-11
 */

#ifndef ITEMDECORATOR_H
#define ITEMDECORATOR_H

#include "Item.h"

#include <memory>

class Item;

class ItemDecorator : public Item
{
    public:
        double price() const override;
        std::string describe() const override;
        bool readyForSale() const override;

        /**
        * @brief Deep clone this decorator and its wrapped chain.
        * @return Newly allocated decorated item copy.
        */
        virtual std::unique_ptr<Item> clone() const override = 0; //prototype

        /** @return Read-only reference to the wrapped item. */
        const Item& wrappedFunc() const; //accessor
    
    protected:
        std::unique_ptr<Item> wrapped;
        explicit ItemDecorator(std::unique_ptr<Item> dec);
};

#endif