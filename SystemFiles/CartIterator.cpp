#include"CartIterator.h"

CartIterator::CartIterator(PlantInventory* inventory) : Iterator() {
    current = 0;  // Initialize the protected member from Iterator base class
    // If caller passes a cart inventory, use its plants directly.
    // Do not call getCartInventory() here — that method is for main inventories
    // and may create/return different state. We only need the passed-in
    // inventory's plant snapshot.
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

