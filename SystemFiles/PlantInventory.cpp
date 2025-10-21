#include "PlantInventory.h"
#include "PlantIterator.h"

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

void PlantInventory::addPlant(Plant* plant) {
    plants.push_back(plant);
}

int PlantInventory::getSize() const {
    return plants.size();
}

Plant* PlantInventory::getPlantAt(int index) const {
    if (index >= 0 && static_cast<size_t>(index) < plants.size()) {
        return plants[index];
    }
    return nullptr;
}