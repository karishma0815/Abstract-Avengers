
/*Abstract Avengers*/

/**
 * @file Director.cpp
 * @brief Implementation of Director.
 */
#include "Director.h"

void Director::setBuilder(ArrangementBuilder* b) 
{ 
    b_ = b; 
}

std::unique_ptr<Item> Director::buildGift(const Item& proto,
                                          double potExtra,  const std::string& potColor,
                                          double wrapExtra, const std::string& message)
{
    b_->reset();
    b_->buildBasePlant(proto);
    b_->buildPot(potExtra, potColor);
    b_->buildWrap(wrapExtra, message);
    return b_->getResult();
}

std::unique_ptr<Item> Director::buildGiftWithNote(const Item& proto,
                                                  double potExtra,  const std::string& potColor,
                                                  double wrapExtra, const std::string& message,
                                                  double noteExtra, const std::string& noteText)
{
    b_->reset();
    b_->buildBasePlant(proto);
    b_->buildPot(potExtra, potColor);
    b_->buildWrap(wrapExtra, message);
    b_->buildNote(noteExtra, noteText);
    return b_->getResult();
}