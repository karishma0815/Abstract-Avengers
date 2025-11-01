/*Abstract Avengers*/

/**
 * @file Note.cpp
 * @brief Implementation of Note.
 */

#include "Note.h"
#include <sstream>

Note::Note(std::unique_ptr<Item> inner, double extra, std::string note)
    : ItemDecorator(std::move(inner)), extra_(extra), note_(std::move(note)) {}

double Note::priceFunc() const {
    return inner_->priceFunc() + extra_;
}

std::string Note::describe() const {
    std::ostringstream os;
    os << inner_->describe() << " + Note(\"" << note_ << "\")";
    return os.str();
}
