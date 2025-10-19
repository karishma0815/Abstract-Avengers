#include"CartIterator.h"

CartIterator::CartIterator(PlantInventory* inventory) : currentIndex(0) {
    if (inventory != nullptr) {
        filteredPlants = inventory->getPlants();
    }
}

CartIterator::~CartIterator() {
    filteredPlants.clear();
}   

void CartIterator::first() {
    currentIndex = 0;
}

void CartIterator::next() {
    if (!isDone()) {
        currentIndex++;
    }
}

bool CartIterator::isDone() const {
    return currentIndex >= static_cast<int>(filteredPlants.size());
}

Plant* CartIterator::currentItem() const {
    if (!isDone()) {
        return filteredPlants[currentIndex];
    }
    return nullptr;
}

bool CartIterator::hasNext() const {
    return currentIndex + 1 < static_cast<int>(filteredPlants.size());
}

