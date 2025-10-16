#include "SucculentGroup.h"
#include <algorithm>

SucculentGroup::SucculentGroup(std::string groupName)
    : SucculentProduct(groupName, 0.0) {
}

SucculentGroup::~SucculentGroup() {
    for (SucculentProduct* plant : plants) {
        delete plant;
    }
    plants.clear();
}

int SucculentGroup::getCount() const {
    int total = 0;
    for (const SucculentProduct* plant : plants) {
        total += plant->getCount();
    }
    return total;
}

void SucculentGroup::add(SucculentProduct* plant) {
    if (plant != nullptr) {
        plants.push_back(plant);
    }
}

void SucculentGroup::remove(SucculentProduct* plant) {
    auto it = std::find(plants.begin(), plants.end(), plant);
    if (it != plants.end()) {
        plants.erase(it);
    }
}

double SucculentGroup::getTotalValue() const {
    double total = 0.0;
    for (const SucculentProduct* plant : plants) {
        total += plant->getTotalValue();
    }
    return total;
}