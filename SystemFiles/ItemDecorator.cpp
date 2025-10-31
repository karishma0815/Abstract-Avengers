/*Abstract Avengers*/

/**
 * @file ItemDecorator.cpp
 * @brief Implementation of ItemDecorator.
 */

#include "ItemDecorator.h"

ItemDecorator::ItemDecorator(std::unique_ptr<Item> inner)
: inner_(std::move(inner)) {}

ItemDecorator::~ItemDecorator() = default;

double ItemDecorator::priceFunc() const 
{
    return inner_->priceFunc();
}

std::string ItemDecorator::describe() const 
{
    return inner_->describe();
}

bool ItemDecorator::readyForSale() const 
{
    return inner_->readyForSale();
}

Item* ItemDecorator::innerRaw() const 
{
    return inner_.get();
}

std::unique_ptr<Item> ItemDecorator::cloneInner() const 
{
    return inner_->clone();
}
