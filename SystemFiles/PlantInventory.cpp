/**
 * @file PlantInventory.cpp
 * @brief Implementation of the PlantInventory class
 */
#include "PlantInventory.h"
#include "PlantIterator.h"
#include "CareIterator.h"
#include "PriceRangeIterator.h"
#include "CartIterator.h"
#include <algorithm>

PlantInventory::PlantInventory() : cartInventory(nullptr), isCart(false) {
    // Cart will be created on first use through getCartInventory()
}

PlantInventory::~PlantInventory() {
    // ownedPlants will be automatically deleted via unique_ptr
    ownedPlants.clear();
    nonOwnedPlants.clear();
    
    // Only delete cart if this is a main inventory
    if (!isCart && cartInventory != nullptr) {
        delete cartInventory;
        cartInventory = nullptr;
    }
}

Iterator* PlantInventory::createPlantIterator(PlantInventory* inventory) {
    return new PlantIterator(this);
}

Iterator* PlantInventory::createCareIterator(PlantInventory* inventory, const std::string& care) {
    return new CareIterator(this,care);
}

Iterator* PlantInventory::createPriceRangeIterator(PlantInventory* inventory, double min, double max) {
    return new PriceRangeIterator(this,min,max);
}

Iterator* PlantInventory::createCartIterator(PlantInventory* inventory) {
    return new CartIterator(this->cartInventory);
}

void PlantInventory::add(Plant* plant) {
    if (plant != nullptr) {
        ownedPlants.emplace_back(plant);
    }
}

void PlantInventory::addNonOwning(Plant* plant) {
    if (plant != nullptr) {
        nonOwnedPlants.push_back(plant);
    }
}

void PlantInventory::remove(Plant* plant) {
    // remove from ownedPlants
    auto it = std::find_if(ownedPlants.begin(), ownedPlants.end(),
                           [&](const std::unique_ptr<Plant>& p){ return p.get() == plant; });
    if (it != ownedPlants.end()) {
        ownedPlants.erase(it);
        return;
    }
    // if not owned, try non-owned list
    removeNonOwning(plant);
}

void PlantInventory::removeNonOwning(Plant* plant) {
    auto it = std::find(nonOwnedPlants.begin(), nonOwnedPlants.end(), plant);
    if (it != nonOwnedPlants.end()) {
        nonOwnedPlants.erase(it);
    }
}

int PlantInventory::size() const {
    return static_cast<int>(ownedPlants.size() + nonOwnedPlants.size());
}

bool PlantInventory::isEmpty() const {
    return ownedPlants.empty() && nonOwnedPlants.empty();
}

Plant* PlantInventory::getPlant(int index) const {
    int ownedCount = static_cast<int>(ownedPlants.size());
    if (index >= 0 && index < ownedCount) {
        return ownedPlants[index].get();
    }
    int nonOwnedIndex = index - ownedCount;
    if (nonOwnedIndex >= 0 && nonOwnedIndex < static_cast<int>(nonOwnedPlants.size())) {
        return nonOwnedPlants[nonOwnedIndex];
    }
    return nullptr;
}

std::vector<Plant*> PlantInventory::getPlants() const {
    std::vector<Plant*> result;
    result.reserve(ownedPlants.size() + nonOwnedPlants.size());
    for (const auto& up : ownedPlants) result.push_back(up.get());
    for (Plant* p : nonOwnedPlants) result.push_back(p);
    return result;
}

PlantInventory* PlantInventory::getCartInventory() {
    // Lazy initialization of cart
    if (!isCart && cartInventory == nullptr) {
        cartInventory = new PlantInventory();
        cartInventory->isCart = true;
    }
    return cartInventory;
}

void PlantInventory::addToCart(Plant* plant) {
    if (cartInventory != nullptr && plant != nullptr) {
        cartInventory->addNonOwning(plant);  // Use non-owning reference for cart
    }
}

void PlantInventory::removeFromCart(Plant* plant) {
    if (cartInventory != nullptr && plant != nullptr) {
        cartInventory->removeNonOwning(plant);  // Use non-owning remove for cart
    }
}