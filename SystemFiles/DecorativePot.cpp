/*Abstract Avengers*/

/**
 * @file DecorativePot.cpp
 * @brief Implementation of DecorativePot.
 */

#include "DecorativePot.h"
#include <sstream>

DecorativePot::DecorativePot(std::unique_ptr<Item> inner, double extra, std::string color)
    : ItemDecorator(std::move(inner)), extra_(extra), color_(std::move(color)) {}

double DecorativePot::priceFunc() const {
    return inner_->priceFunc() + extra_;
}

std::string DecorativePot::describe() const {
    std::ostringstream os;
    os << inner_->describe() << " + Pot(" << color_ << ")";
    return os.str();
}
