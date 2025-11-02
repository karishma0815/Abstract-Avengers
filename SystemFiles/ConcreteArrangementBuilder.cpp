/*Abstract Avengers*/

/**
 * @file ConcreteArrangementBuilder.cpp
 * @brief Implementation of ConcreteArrangementBuilder.
 */

#include "ConcreteArrangementBuilder.h"
#include "DecorativePot.h"
#include "GiftWrap.h"
#include "Note.h"
#include <utility>

void ConcreteArrangementBuilder::reset() {
    current_.reset();
}

void ConcreteArrangementBuilder::buildBasePlant(std::unique_ptr<Item> base) {
    current_ = std::move(base); // NO CLONE
}

void ConcreteArrangementBuilder::buildPot(double extra, const std::string& color) {
    if (current_) current_ = std::unique_ptr<Item>(new DecorativePot(std::move(current_), extra, color));
}

void ConcreteArrangementBuilder::buildWrap(double extra, const std::string& message) {
    if (current_) current_ = std::unique_ptr<Item>(new GiftWrap(std::move(current_), extra, message));
}

void ConcreteArrangementBuilder::buildNote(double extra, const std::string& text) {
    if (current_) current_ = std::unique_ptr<Item>(new Note(std::move(current_), extra, text));
}

std::unique_ptr<Item> ConcreteArrangementBuilder::getResult() {
    return std::move(current_);
}
