#include "InventoryObserver.h"
#include <iostream>

InventoryObserver::InventoryObserver(int threshold) 
    : lowStockThreshold(threshold) {
}

InventoryObserver::~InventoryObserver() {
}

void InventoryObserver::update(std::string plantType, int quantity, std::string action) {
    if (action == "added") {
        inventoryLevels[plantType] += quantity;
        std::cout << "[INVENTORY] Added " << quantity << " " << plantType 
                  << "(s). Total: " << inventoryLevels[plantType] << std::endl;
    } else if (action == "removed") {
        inventoryLevels[plantType] -= quantity;
        std::cout << "[INVENTORY] Removed " << quantity << " " << plantType 
                  << "(s). Remaining: " << inventoryLevels[plantType] << std::endl;
        
        // Check for low stock
        if (inventoryLevels[plantType] <= lowStockThreshold) {
            std::cout << "⚠️  [LOW STOCK ALERT] " << plantType 
                     << " stock is low! Current: " << inventoryLevels[plantType] << std::endl;
        }
    }
}

int InventoryObserver::getStockLevel(std::string plantType) const {
    auto it = inventoryLevels.find(plantType);
    if (it != inventoryLevels.end()) {
        return it->second;
    }
    return 0;
}

void InventoryObserver::setLowStockThreshold(int threshold) {
    lowStockThreshold = threshold;
}

void InventoryObserver::displayInventory() const {
    std::cout << "\n=== INVENTORY LEVELS ===" << std::endl;
    for (const auto& pair : inventoryLevels) {
        std::cout << pair.first << ": " << pair.second;
        if (pair.second <= lowStockThreshold) {
            std::cout << " ⚠️ LOW";
        }
        std::cout << std::endl;
    }
}

int InventoryObserver::getTotalInventoryCount() const {
    int total = 0;
    for (const auto& pair : inventoryLevels) {
        total += pair.second;
         }
    return total;
}