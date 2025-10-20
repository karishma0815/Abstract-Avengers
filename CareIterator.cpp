/**
 * @file CareIterator.cpp
 * @brief Implementation of the CareIterator class
 */
#include "CareIterator.h"
#include <algorithm>

CareIterator::CareIterator(PlantInventory* inventory, const std::string& care) :careKey(care) {
    if (inventory != nullptr) {
        filterByCare(inventory);
    }
}

CareIterator::~CareIterator() {
    filteredPlants.clear();
}

void CareIterator::filterByCare(PlantInventory* inventory) {
    const std::vector<Plant*>& allPlants = inventory->getPlants();
    
    // Convert keyword to lowercase for case-insensitive comparison
    std::string lowerKeyword = careKey;
    std::transform(lowerKeyword.begin(), lowerKeyword.end(), 
                   lowerKeyword.begin(), ::tolower);
    
    // Filter plants that contain the care keyword in their care instructions
    for (Plant* plant:allPlants) {
        if (plant != nullptr) {
            std::string careInstructions = plant->getCareInstructions();
            
            // Convert to lowercase for comparison
            std::transform(careInstructions.begin(), careInstructions.end(),
                          careInstructions.begin(), ::tolower);
            
            // Check if keyword is found in care instructions
            if (careInstructions.find(lowerKeyword) != std::string::npos) {
                filteredPlants.push_back(plant);
            }
        }
    }
}

void CareIterator::first() {
    current = 0;
}

void CareIterator::next() {
    if (!isDone()) {
        current++;
    }
}

bool CareIterator::isDone() const {
    return current >= static_cast<int>(filteredPlants.size());
}

Plant* CareIterator::currentItem() const {
    if (!isDone()) {
        return filteredPlants[current];
    }
    return nullptr;
}

bool CareIterator::hasNext() const {
    return current < static_cast<int>(filteredPlants.size()) - 1;
}