/*Abstract Avengers*/

/**
 * @file Note.cpp
 * @brief Implementation of Note.
 */

#include "Note.h"

#include <utility>

Note::Note(std::unique_ptr<Item> dec, std::string text, double extra)
  : ItemDecorator(std::move(dec)), text(std::move(text)), extra(extra) 
  {}

double Note::price() const 
{ 
    return wrapped->price() + extra; 
}

std::string Note::describe() const 
{
  return wrapped->describe() + " + Note(\"" + text + "\")";
}

bool Note::readyForSale() const 
{ 
    return wrapped->readyForSale(); 
}

std::unique_ptr<Item> Note::clone() const 
{
  return std::unique_ptr<Item>(new Note(wrapped->clone(), text, extra));
}

const std::string& Note::textFunc() const 
{ 
    return text; 
}

double Note::extraFunc() const 
{ 
    return extra; 
}