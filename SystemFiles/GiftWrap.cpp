/*Abstract Avengers*/

/**
 * @file GiftWrap.cpp
 * @brief Implementation of GiftWrap.
 */

#include "GiftWrap.h"
#include <memory>
#include <utility>

GiftWrap::GiftWrap(std::unique_ptr<Item> inner, double extra, std::string message)
: ItemDecorator(std::move(inner))
, extra_(extra)
, message_(std::move(message))
{}

double GiftWrap::priceFunc() const 
{
    return ItemDecorator::priceFunc() + extra_;
}

std::string GiftWrap::describe() const 
{
    return ItemDecorator::describe() + " + Wrap(\"" + message_ + "\")";
}

std::unique_ptr<Item> GiftWrap::clone() const 
{
    return std::unique_ptr<Item>( new GiftWrap( cloneInner(), extra_, message_ ) );
}