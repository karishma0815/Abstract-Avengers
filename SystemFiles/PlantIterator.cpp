#include "PlantIterator.h"

PlantIterator::PlantIterator(PlantInventory* inventory) 
    : plantInventory(inventory), current(0) {}

void PlantIterator::first() {
    current = 0;
}

void PlantIterator::next() {
    current++;
}

bool PlantIterator::isDone() {
    return current >= plantInventory->getSize();
}

Plant* PlantIterator::currentItem() {
    if (isDone()) {
        return nullptr;
    }
    return plantInventory->getPlantAt(current);
}