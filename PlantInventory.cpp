/**
 * @file PlantInventory.cpp
 * @brief Implementation of the PlantInventory class
 */
#include "PlantInventory.h"
#include "PlantIterator.h"
#include <algorithm>

PlantInventory::PlantInventory() {}

PlantInventory::~PlantInventory() {
    
    for (Plant* plant : plants) {
        delete plant;
    }
    plants.clear();
}

Iterator* PlantInventory::createIterator() {
    return new PlantIterator(this);
}

void PlantInventory::add(Plant* plant) {
    if (plant != NULL) {
        plants.push_back(plant);
    }
}

void PlantInventory::remove(Plant* plant) {
    auto it = std::find(plants.begin(), plants.end(), plant);
    if (it != plants.end()) {
        delete *it;
        plants.erase(it);
    }
}

int PlantInventory::size() const {
    return plants.size();
}

bool PlantInventory::isEmpty() const {
    return plants.empty();
}

Plant* PlantInventory::getPlant(int index) const {
    if (index >= 0 && index <static_cast<int>(plants.size())) {
        return plants[index];
        //what is the point of static cast here?
        //to avoid warnings about comparing signed and unsigned integers
        //since size() returns an unsigned type (size_t)
        //and index is an int (signed)
        //static_cast<int> converts size() result to int for safe comparison
    }
    return NULL;
}

const std::vector<Plant*>& PlantInventory::getPlants() const {
    return plants;
}