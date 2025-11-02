
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

std::unique_ptr<Item> Director::buildGift(std::unique_ptr<Item> base,
                                          double potExtra,  const std::string& potColor,
                                          double wrapExtra, const std::string& message)
{
    if (!b_) return std::unique_ptr<Item>();
    b_->reset();
    b_->buildBasePlant(std::move(base));   // NO CLONE
    if (potExtra  > 0.0) b_->buildPot (potExtra,  potColor);
    if (wrapExtra > 0.0) b_->buildWrap(wrapExtra, message);
    return b_->getResult();
}

std::unique_ptr<Item> Director::buildGiftWithNote(std::unique_ptr<Item> base,
                                                  double potExtra,  const std::string& potColor,
                                                  double wrapExtra, const std::string& message,
                                                  double noteExtra, const std::string& noteText)
{
    if (!b_) return std::unique_ptr<Item>();
    b_->reset();
    b_->buildBasePlant(std::move(base));   // NO CLONE
    if (potExtra  > 0.0) b_->buildPot (potExtra,  potColor);
    if (wrapExtra > 0.0) b_->buildWrap(wrapExtra, message);
    if (noteExtra > 0.0) b_->buildNote(noteExtra, noteText);
    return b_->getResult();
}