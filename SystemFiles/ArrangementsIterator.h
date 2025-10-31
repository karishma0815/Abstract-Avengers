/*Abstract Avengers*/

/**
 * @file ArrangementsIterator.h
 * @brief Simple container of Arrangements built via the Builder.
 * @author Taskeen Abdoola
 * @date 2025-10-19
 */

#pragma once
#include <vector>
#include "Item.h"

class ArrangementsIterator 
{
public:
    explicit ArrangementsIterator(const std::vector<const Item*>& items);

    void first();
    void next();
    bool isDone() const;
    const Item* current() const;

private:
    std::vector<const Item*> items_;
    size_t i_;
};
