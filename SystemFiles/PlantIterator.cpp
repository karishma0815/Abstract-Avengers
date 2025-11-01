#include"PlantIterator.h"
#include <algorithm>

/**
 * @file PlantIterator.cpp
 * @brief Implementation of the PlantIterator class
 */
PlantIterator::PlantIterator(PlantInventory* inventory,const std::string& type) : type(type), currentIndex(0) {
    // Make a copy of the plants for robust iteration
    // This prevents issues if the inventory is modified during iteration
    if (inventory!=NULL) {
        plants=inventory->getPlants();
        if(!type.empty()){
            filterByType(inventory);
        }
    }
}

PlantIterator::~PlantIterator() {
    //We don't delete the plants as they're owned by PlamtInventory
    plants.clear();
}

void PlantIterator::first() {
    currentIndex = 0;
}

void PlantIterator::next() {
    if (!isDone()) {
        currentIndex++;
    }
}

bool PlantIterator::isDone() const {
    return currentIndex >= static_cast<int>(plants.size());
}

Plant* PlantIterator::currentItem() const {
    if (!isDone()) {
        return plants[currentIndex];
    }
    return NULL;
}

bool PlantIterator::hasNext() const {
    return currentIndex < (static_cast<int>(plants.size()) - 1);
}

void PlantIterator::filterByType(PlantInventory* inventory) {
    const std::vector<Plant*>& allPlants = inventory->getPlants();
    
    //lowercase for case-insensitive comparison
    std::string lowerType = this->type;
    std::transform(lowerType.begin(), lowerType.end(), 
                   lowerType.begin(), ::tolower);
    
    //Filter plants by type
    for (Plant* plant : allPlants) {
        if (plant != NULL) {
            std::string type = plant->getName();
            
            //Convert to lowercase for comparison
            std::transform(type.begin(), type.end(), type.begin(), ::tolower);
            
            if (type == lowerType) {
                filteredPlants.push_back(plant);
            }
        }
    }
}