/*Abstract Avengers*/

/**
 * @file Director.cpp
 * @brief Implementation of Director.
 */

#include "Director.h"
#include "ArrangementBuilder.h"

void Director::setBuilder(ArrangementBuilder* b) 
{ 
    builder = b; 
}

ArrangementBuilder* Director::builderFunc() const 
{ 
    return builder; 
}

// Example recipe: base plant + pot + wrap (a "gift" preset). Can also add a note.
std::unique_ptr<Item> Director::buildGift(const Item& plantProto, double potExtra, const std::string& color, double wrapExtra, const std::string& message) 
{
  builder->reset();
  builder->buildBasePlant(plantProto);
  builder->buildPot(potExtra, color);
  builder->buildWrap(wrapExtra, message);
  return builder->getResult();
}
std::unique_ptr<Item> Director::buildGiftWithNote(const Item& plantPrototype, double potExtra, const std::string& color, double wrapExtra, const std::string& message, double noteExtra, const std::string& text) {
  builder->reset();
  builder->buildBasePlant(plantPrototype);
  builder->buildPot(potExtra, color);
  builder->buildWrap(wrapExtra, message);
  builder->buildNote(noteExtra, text);
  return builder->getResult();
}