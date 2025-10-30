#include "InventorySystem.h"

InventorySystem::InventorySystem() {
    plantCollection = new PlantInventory();
    growing = new PlantInventory();
}

InventorySystem::~InventorySystem() {
    delete plantCollection;
    delete growing;
}

void InventorySystem::addPlant(Plant* plant, bool ready) {
    if (ready) {
        plantCollection->add(plant);
    } else {
        growing->add(plant);
    }
}

void InventorySystem::ageReadyForSale(Iterator* iterator) {
    if (iterator == nullptr) {
        return;
    }
    
    for (iterator->first(); !iterator->isDone(); iterator->next()) {
        Plant* plant = iterator->currentItem();
        if (plant != nullptr) {
          
        }
    }
}

void InventorySystem::ageGrowingIterator(Iterator* iterator) {
    if (iterator == nullptr) {
        return;
    }
    
    for (iterator->first(); !iterator->isDone(); iterator->next()) {
        Plant* plant = iterator->currentItem();
        if (plant != nullptr) {

        }
    }
}

PlantInventory* InventorySystem::getPlantCollection() {
    return plantCollection;
}

PlantInventory* InventorySystem::getGrowing() {
    return growing;
}