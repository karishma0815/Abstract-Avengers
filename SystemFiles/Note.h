/*Abstract Avengers*/

/**
 * @file Note.h
 * @brief ConcreteDecorator adding a small note to the arrangement
 * @author Taskeen Abdoola
 * @date 2025-10-14
 */

#pragma once
#include "ItemDecorator.h"
#include <string>
#include <memory>

class Note : public ItemDecorator {
public:
    Note(std::unique_ptr<Item> inner, double extra, std::string note);

    double priceFunc() const override;
    std::string describe() const override;
    bool readyForSale() const override { return ItemDecorator::readyForSale(); }

private:
    double      extra_;
    std::string note_;
};
