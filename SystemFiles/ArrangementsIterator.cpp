/*Abstract Avengers*/

/**
 * @file ArrangementsIterator.cpp
 * @brief Implementation of ArrangementsIteratpr.
 */

#include "ArrangementsIterator.h"

ArrangementsIterator::ArrangementsIterator(const std::vector<const Item*>& items)
: items_(items), i_(0) {}

void ArrangementsIterator::first() 
{ 
    i_ = 0; 
}

void ArrangementsIterator::next()  
{ 
    if (i_ < items_.size()) ++i_; 
}

bool ArrangementsIterator::isDone() const 
{ 
    return i_ >= items_.size(); 
}

const Item* ArrangementsIterator::current() const 
{ 
    return isDone() ? 0 : items_[i_]; 
}