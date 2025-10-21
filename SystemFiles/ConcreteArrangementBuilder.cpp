/*Abstract Avengers*/

/**
 * @file COncreteArrangementBuilder.cpp
 * @brief Implementation of ConcreteArrangementBuilder.
 */

#include "ConcreteArrangementBuilder.h"
#include "Item.h"
#include "DecorativePot.h"
#include "GiftWrap.h"
#include "Note.h"        

#include <memory>

// Start with no product; each recipe begins with reset()
ConcreteArrangementBuilder::ConcreteArrangementBuilder() : single(nullptr) 
{}

// Clear any in-progress product so we can start a new build.
void ConcreteArrangementBuilder::reset() 
{ 
    single.reset(); 
}

// Step 1: clone a plant prototype to become the base Item.
// This keeps the builder decoupled from specific plant classes.
void ConcreteArrangementBuilder::buildBasePlant(const Item& plantProto) 
{
  single = plantProto.clone();
}

// Step 2: wrap current item in a pot. If there is no current item, no-op.
void ConcreteArrangementBuilder::buildPot(double extra, const std::string& colour) 
{
  if (!single) return;
  single.reset(new DecorativePot(std::move(single), colour, extra));
}

// Step 3: wrap current item in gift wrap layer (optional).
void ConcreteArrangementBuilder::buildWrap(double extra, const std::string& message) 
{
  if (!single) return;
  single.reset(new GiftWrap(std::move(single), message, extra));
}

void ConcreteArrangementBuilder::buildNote(double extra, const std::string& text) 
{
  if (!single) return;
  single.reset(new Note(std::move(single), text, extra));
}

// Return ownership of the finished product and clear the builder.
std::unique_ptr<Item> ConcreteArrangementBuilder::getResult() 
{
  return std::move(single);
}

// Let tests check whether a product exists during a recipe.
bool ConcreteArrangementBuilder::hasProduct() const 
{ 
    return single != nullptr; 
}