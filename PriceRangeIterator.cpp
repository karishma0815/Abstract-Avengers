/**
 * @file PriceRangeIterator.cpp
 * @brief Implementation of the PriceRangeIterator class
 */

#include "PriceRangeIterator.h"

PriceRangeIterator::PriceRangeIterator(PlantInventory* inventory, double min, double max):currentIndex(0), minPrice(min), maxPrice(max) {
    if (inventory != NULL) {
        filterByPrice(inventory);
    }
}

PriceRangeIterator::~PriceRangeIterator() {
    filteredPlants.clear();
}

void PriceRangeIterator::filterByPrice(PlantInventory* inventory) {
    const std::vector<Plant*>& allPlants = inventory->getPlants();
    //filter plants within price range
    for (Plant* plant : allPlants) {
        if (plant != nullptr) {
            double price = plant->getPrice();
            if (price >= minPrice && price <= maxPrice) {
                filteredPlants.push_back(plant);
            }
        }
    }
}

void PriceRangeIterator::first() {
    currentIndex = 0;
}

void PriceRangeIterator::next() {
    if (!isDone()) {
        currentIndex++;
    }
}

bool PriceRangeIterator::isDone() const {
    return currentIndex >= static_cast<int>(filteredPlants.size());
}

Plant* PriceRangeIterator::currentItem() const {
    if (!isDone()) {
        return filteredPlants[currentIndex];
    }
    return NULL;
}

bool PriceRangeIterator::hasNext() const {
    return currentIndex < (static_cast<int>(filteredPlants.size()) - 1);
}