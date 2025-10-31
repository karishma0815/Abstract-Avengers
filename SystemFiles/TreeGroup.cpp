#include "TreeGroup.h"
#include <algorithm>

TreeGroup::TreeGroup(std::string groupName)
    : TreeProduct(groupName, 0.0) {
}

TreeGroup::~TreeGroup() {
    for (TreeProduct* plant : plants) {
        delete plant;
    }
    plants.clear();
}

std::string TreeGroup::getPlantType() const{
    return "Tree Group";
}

int TreeGroup::getCount() const
{
    int total = 0;
    for (const TreeProduct* plant : plants) {
        total += plant->getCount();
    }
    return total;
}

void TreeGroup::add(TreeProduct* plant) {
    if (plant != nullptr) {
        plants.push_back(plant);
    }
}

void TreeGroup::remove(TreeProduct* plant) {
    auto it = std::find(plants.begin(), plants.end(), plant);
    if (it != plants.end()) {
        plants.erase(it);
    }
}

double TreeGroup::getTotalValue() const {
    double total = 0.0;
    for (const TreeProduct* plant : plants) {
        total += plant->getTotalValue();
    }
    return total;
}