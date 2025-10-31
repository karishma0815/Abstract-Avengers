/*Abstract Avengers*/

/**
 * @file ItemDecorator.h
 * @brief Decorator class for decorator pattern
 * @author Taskeen Abdoola
 * @date 2025-10-14
 */

#pragma once
#include "Item.h"
#include <memory>

class ItemDecorator : public Item {
public:
    explicit ItemDecorator(std::unique_ptr<Item> inner);
    ~ItemDecorator() override;

    double priceFunc() const override;
    std::string describe() const override;
    bool readyForSale() const override;

protected:
    Item* innerRaw() const;
    /**
        * @brief Deep clone this decorator and its wrapped chain.
        * @return Newly allocated decorated item copy.
        */
    std::unique_ptr<Item> cloneInner() const;

    std::unique_ptr<Item> inner_;
};