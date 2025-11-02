/*Abstract Avengers*/

/**
 * @file GiftWrap.cpp
 * @brief Implementation of GiftWrap.
 */

#include "GiftWrap.h"
#include <sstream>

GiftWrap::GiftWrap(std::unique_ptr<Item> inner, double extra, std::string message)
    : ItemDecorator(std::move(inner)), extra_(extra), message_(std::move(message)) {}

double GiftWrap::priceFunc() const {
    return inner_->priceFunc() + extra_;
}

std::string GiftWrap::describe() const {
    std::ostringstream os;
    os << inner_->describe() << " + Wrap(\"" << message_ << "\")";
    return os.str();
}
