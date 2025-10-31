/*Abstract Avengers*/

/**
 * @file ConcreteArrangementBuilder.cpp
 * @brief Implementation of ConcreteArrangementBuilder.
 */

#include "ConcreteArrangementBuilder.h"
#include "DecorativePot.h"   // your concrete decorator
#include "GiftWrap.h"        // your concrete decorator
#include "Note.h"            // your concrete decorator
#include <utility>           // std::move
#include <memory>
// Clear any in-progress product so we can start a new build.
void ConcreteArrangementBuilder::reset() {
    current_.reset();
}

// Step 1: clone a plant prototype to become the base Item.
// This keeps the builder decoupled from specific plant classes.
void ConcreteArrangementBuilder::buildBasePlant(const Item& proto) {
    current_ = proto.clone(); // deep copy of prototype (std::unique_ptr<Item>)
}



void ConcreteArrangementBuilder::buildPot(double extra, const std::string& color) {
    if (current_) {
        current_ = std::unique_ptr<Item>( new DecorativePot(std::move(current_), extra, color) );
    }
}

// Step 3: wrap current item in gift wrap layer (optional).
void ConcreteArrangementBuilder::buildWrap(double extra, const std::string& message) {
    if (current_) {
        current_ = std::unique_ptr<Item>( new GiftWrap(std::move(current_), extra, message) );
    }
}

void ConcreteArrangementBuilder::buildNote(double extra, const std::string& text) {
    if (current_) {
        current_ = std::unique_ptr<Item>( new Note(std::move(current_), extra, text) );
    }
}

std::unique_ptr<Item> ConcreteArrangementBuilder::getResult() {
    return std::move(current_);
}
