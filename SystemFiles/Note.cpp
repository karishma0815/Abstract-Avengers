/*Abstract Avengers*/

/**
 * @file Note.cpp
 * @brief Implementation of Note.
 */

#include "Note.h"
#include <memory>
#include <utility>

Note::Note(std::unique_ptr<Item> inner, double extra, std::string text)
: ItemDecorator(std::move(inner))
, extra_(extra)
, note_(std::move(text))
{}

double Note::priceFunc() const 
{
    return ItemDecorator::priceFunc() + extra_;
}

std::string Note::describe() const 
{
    return ItemDecorator::describe() + " + Note(\"" + note_ + "\")";
}

std::unique_ptr<Item> Note::clone() const 
{
    return std::unique_ptr<Item>( new Note( cloneInner(), extra_, note_ ) );
}
