/*Abstract Avengers*/

/**
 * @file GiftWrap.h
 * @brief ConcreteDecorator adding a gift wrap
 * @author Taskeen Abdoola
 * @date 2025-10-14
 */

#pragma once
#include "ItemDecorator.h"
#include <string>
#include <memory>

class GiftWrap : public ItemDecorator {
public:
    GiftWrap(std::unique_ptr<Item> inner, double extra, std::string message);

    double priceFunc() const override;
    std::string describe() const override;
    bool readyForSale() const override { return ItemDecorator::readyForSale(); }
    std::unique_ptr<Item> clone() const override;

private:
    double      extra_;
    std::string message_;
};
