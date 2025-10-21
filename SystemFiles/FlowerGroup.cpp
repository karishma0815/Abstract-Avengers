#include "FlowerGroup.h"
#include <algorithm>

FlowerGroup::FlowerGroup(std::string groupName)
    : FlowerProduct(groupName, 0.0) {
}

FlowerGroup::~FlowerGroup() {
    for (FlowerProduct* plant : plants) {
        delete plant;
    }
    plants.clear();
}

int FlowerGroup::getCount() const {
    int total = 0;
    for (const FlowerProduct* plant : plants) {
        total += plant->getCount();
    }
    return total;
}

void FlowerGroup::add(FlowerProduct* plant) {
    if (plant != nullptr) {
        plants.push_back(plant);
    }
}

void FlowerGroup::remove(FlowerProduct* plant) {
    auto it = std::find(plants.begin(), plants.end(), plant);
    if (it != plants.end()) {
        plants.erase(it);
    }
}

double FlowerGroup::getTotalValue() const {
    double total = 0.0;
    for (const FlowerProduct* plant : plants) {
        total += plant->getTotalValue();
    }
    return total;
}