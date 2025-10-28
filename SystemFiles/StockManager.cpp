#include "StockManager.h"
#include <algorithm>
#include <iostream>

StockManager::StockManager() {
}

StockManager::~StockManager() {
    // Clean up all stock
    for (SucculentProduct* plant : succulentStock) {
        delete plant;
    }
    for (FlowerProduct* plant : flowerStock) {
        delete plant;
    }
    for (TreeProduct* plant : treeStock) {
        delete plant;
    }
    
    // Note: We don't delete observers as StockManager doesn't own them
}

void StockManager::attach(StockObserver* observer) {
    if (observer != nullptr) {
        observers.push_back(observer);
    }
}

void StockManager::detach(StockObserver* observer) {
    auto it = std::find(observers.begin(), observers.end(), observer);
    if (it != observers.end()) {
        observers.erase(it);
    }
}

void StockManager::notify(std::string plantType, int quantity, std::string action) {
    for (StockObserver* observer : observers) {
        observer->update(plantType, quantity, action);
    }
}

// Succulent methods
void StockManager::addSucculent(SucculentProduct* plant) {
    if (plant != nullptr) {
        succulentStock.push_back(plant);
        int quantity = plant->getCount();
        //here added value, plantType and update inventory

        double value = plant->getTotalValue();
        std::string plantType = plant->getPlantType();
        
        inventory.updateInventory(plantType, quantity, value);

        //this was already here
        notify(plant->getPlantType(), quantity, "added");
        
    }
}

void StockManager::removeSucculent(int index) {
    if (index >= 0 && index < static_cast<int>(succulentStock.size())) {
        SucculentProduct* plant = succulentStock[index];
        int quantity = plant->getCount();
        //here added value
        double value = plant->getTotalValue();

        //this was already here
        std::string plantType = plant->getPlantType();
        
        succulentStock.erase(succulentStock.begin() + index);

        //new update inventory removal
        inventory.removeFromInventory(plantType, quantity, value);

        notify(plantType, quantity, "removed");
        delete plant;
    }
}

SucculentProduct* StockManager::getSucculent(int index) const {
    if (index >= 0 && index < static_cast<int>(succulentStock.size())) {
        return succulentStock[index];
    }
    return nullptr;
}

int StockManager::getSucculentStockSize() const {
    return succulentStock.size();
}

// Flower methods
void StockManager::addFlower(FlowerProduct* plant) {
    if (plant != nullptr) {
        flowerStock.push_back(plant);
        int quantity = plant->getCount();

         //here added value, plantType and update inventory

        double value = plant->getTotalValue();
        std::string plantType = plant->getPlantType();
        
        inventory.updateInventory(plantType, quantity, value);

        //this was already here
        notify(plant->getPlantType(), quantity, "added");
    }
}

void StockManager::removeFlower(int index) {
    if (index >= 0 && index < static_cast<int>(flowerStock.size())) {
        FlowerProduct* plant = flowerStock[index];
        int quantity = plant->getCount();

        //here added value
        double value = plant->getTotalValue();

        std::string plantType = plant->getPlantType();
        
        flowerStock.erase(flowerStock.begin() + index);

        //new update inventory removal
        inventory.removeFromInventory(plantType, quantity, value);

        notify(plantType, quantity, "removed");
        delete plant;
    }
}

FlowerProduct* StockManager::getFlower(int index) const {
    if (index >= 0 && index < static_cast<int>(flowerStock.size())) {
        return flowerStock[index];
    }
    return nullptr;
}

int StockManager::getFlowerStockSize() const {
    return flowerStock.size();
}

// Tree methods
void StockManager::addTree(TreeProduct* plant) {
    if (plant != nullptr) {
        treeStock.push_back(plant);
        int quantity = plant->getCount();

         //here added value, plantType and update inventory

        double value = plant->getTotalValue();
        std::string plantType = plant->getPlantType();
        
        inventory.updateInventory(plantType, quantity, value);

        //this was already here
        notify(plant->getPlantType(), quantity, "added");
    }
}

void StockManager::removeTree(int index) {
    if (index >= 0 && index < static_cast<int>(treeStock.size())) {
        TreeProduct* plant = treeStock[index];
        int quantity = plant->getCount();
        
        //here added value
        double value = plant->getTotalValue();
        
        std::string plantType = plant->getPlantType();
        
        treeStock.erase(treeStock.begin() + index);
        
        //new update inventory removal
        inventory.removeFromInventory(plantType, quantity, value);

        notify(plantType, quantity, "removed");
        delete plant;
    }
}

TreeProduct* StockManager::getTree(int index) const {
    if (index >= 0 && index < static_cast<int>(treeStock.size())) {
        return treeStock[index];
    }
    return nullptr;
}

int StockManager::getTreeStockSize() const {
    return treeStock.size();
}

// General methods
//display all stock through console by iterating through each stock vector,
// because its const it cant modify any member variables so it just reads 
//them and displays all stock items based on their type and details like 
//name, value and count
void StockManager::displayAllStock() const {
    std::cout << "\n╔════════════════════════════════════════╗" << std::endl;
    std::cout << "║     NURSERY STOCK OVERVIEW            ║" << std::endl;
    std::cout << "╚════════════════════════════════════════╝" << std::endl;
    
    std::cout << "\n--- SUCCULENTS ---" << std::endl;
    if (succulentStock.empty()) {
        std::cout << "  No succulents in stock." << std::endl;
    } else {
        for (size_t i = 0; i < succulentStock.size(); ++i) {
            std::cout << "  [" << i << "] " << succulentStock[i]->getName() 
                     << " - R" << succulentStock[i]->getTotalValue()
                     << " (" << succulentStock[i]->getCount() << " plant(s))" << std::endl;
        }
    }
    
    std::cout << "\n--- FLOWERS ---" << std::endl;
    if (flowerStock.empty()) {
        std::cout << "  No flowers in stock." << std::endl;
    } else {
        for (size_t i = 0; i < flowerStock.size(); ++i) {
            std::cout << "  [" << i << "] " << flowerStock[i]->getName() 
                     << " - R" << flowerStock[i]->getTotalValue()
                     << " (" << flowerStock[i]->getCount() << " plant(s))" << std::endl;
        }
    }
    
    std::cout << "\n--- TREES ---" << std::endl;
    if (treeStock.empty()) {
        std::cout << "  No trees in stock." << std::endl;
    } else {
        for (size_t i = 0; i < treeStock.size(); ++i) {
            std::cout << "  [" << i << "] " << treeStock[i]->getName() 
                     << " - R" << treeStock[i]->getTotalValue()
                     << " (" << treeStock[i]->getCount() << " plant(s))" << std::endl;
        }
    }
    
    std::cout << "\n─────────────────────────────────────────" << std::endl;
    std::cout << "Total Items: " << getTotalStockCount() << std::endl;
    std::cout << "Total Value: R" << getTotalStockValue() << std::endl;
    std::cout << "═════════════════════════════════════════\n" << std::endl;
}


//add display inventory summary method here later
//why? to show inventory breakdown
//how is this different from display all stock? because this focuses on
//summarizing counts and values by plant type rather than individual items
//so why does it give me an error? because it wasnt declared in the header file
void StockManager::displayInventoryBreakdown() const {
    inventory.displayInventorySummary();
}




int StockManager::getTotalStockCount() const {
    int total = 0;
    
    for (const SucculentProduct* plant : succulentStock) {
        total += plant->getCount();
    }
    for (const FlowerProduct* plant : flowerStock) {
        total += plant->getCount();
    }
    for (const TreeProduct* plant : treeStock) {
        total += plant->getCount();
    }
    
    return total;
}

double StockManager::getTotalStockValue() const {
    double total = 0.0;
    
    for (const SucculentProduct* plant : succulentStock) {
        total += plant->getTotalValue();
    }
    for (const FlowerProduct* plant : flowerStock) {
        total += plant->getTotalValue();
    }
    for (const TreeProduct* plant : treeStock) {
        total += plant->getTotalValue();
    }
    
    return total;
}

std::vector<SucculentProduct*> StockManager::getSucculentStock() const {
    return succulentStock;
}

std::vector<FlowerProduct*> StockManager::getFlowerStock() const {
    return flowerStock;
}

std::vector<TreeProduct*> StockManager::getTreeStock() const {
    return treeStock;
}