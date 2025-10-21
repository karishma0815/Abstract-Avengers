#include"CartIterator.h"

CartIterator::CartIterator(PlantInventory* inventory)  {
    if (inventory != nullptr) {
        filteredPlants = inventory->getPlants();
    }
}

CartIterator::~CartIterator() {
    filteredPlants.clear();
}   

void CartIterator::first() {
    current = 0;
}

void CartIterator::next() {
    if (!isDone()) {
        current++;
    }
}

bool CartIterator::isDone() const {
    return current >= static_cast<int>(filteredPlants.size());
}

Plant* CartIterator::currentItem() const {
    if (!isDone()) {
        return filteredPlants[current];
    }
    return nullptr;
}

bool CartIterator::hasNext() const {
    return current + 1 < static_cast<int>(filteredPlants.size());
}

