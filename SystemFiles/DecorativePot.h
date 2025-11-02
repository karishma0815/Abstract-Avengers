/*Abstract Avengers*/

/**
 * @file DecorativePot.h
 * @brief ConcreteDecorator adding a decorative pot
 * @author Taskeen Abdoola
 * @date 2025-10-14
 */

#pragma once
#include "ItemDecorator.h"
#include <string>
#include <memory>

class DecorativePot : public ItemDecorator {
public:
    DecorativePot(std::unique_ptr<Item> inner, double extra, std::string color);

    double priceFunc() const override;
    std::string describe() const override;
    bool readyForSale() const override { return ItemDecorator::readyForSale(); }

private:
    double      extra_;
    std::string color_;
};
