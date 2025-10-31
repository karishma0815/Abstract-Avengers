/*Abstract Avengers*/

/**
 * @file DecorativePot.cpp
 * @brief Implementation of DecorativePot.
 */

#include "DecorativePot.h"
#include <memory>
#include <utility>

DecorativePot::DecorativePot(std::unique_ptr<Item> inner, double extra, std::string color)
: ItemDecorator(std::move(inner))
, extra_(extra)
, color_(std::move(color))
{}

double DecorativePot::priceFunc() const 
{
    return ItemDecorator::priceFunc() + extra_;
}

std::string DecorativePot::describe() const 
{
    return ItemDecorator::describe() + " + Pot(" + color_ + ")";
}

std::unique_ptr<Item> DecorativePot::clone() const 
{
    return std::unique_ptr<Item>( new DecorativePot( cloneInner(), extra_, color_ ) );
}
