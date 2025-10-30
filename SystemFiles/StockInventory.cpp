#include "StockInventory.h"
#include <iostream>
#include <iomanip>

StockInventory::StockInventory() {
}

StockInventory::~StockInventory() {
}

void StockInventory::updateInventory(const std::string& plantType, int quantity, double value) {
    plantTypeCount[plantType] += quantity;
    plantTypeValue[plantType] += value;
}

void StockInventory::removeFromInventory(const std::string& plantType, int quantity, double value) {
    if (plantTypeCount.find(plantType) != plantTypeCount.end()) {
        plantTypeCount[plantType] -= quantity;
        plantTypeValue[plantType] -= value;
        
        if (plantTypeCount[plantType] <= 0) {
            plantTypeCount.erase(plantType);
            plantTypeValue.erase(plantType);
        }
    }
}

int StockInventory::getTypeCount(const std::string& plantType) const {
    auto it = plantTypeCount.find(plantType);
    return (it != plantTypeCount.end()) ? it->second : 0;
}

double StockInventory::getTypeValue(const std::string& plantType) const {
    auto it = plantTypeValue.find(plantType);
    return (it != plantTypeValue.end()) ? it->second : 0.0;
}

std::map<std::string, int> StockInventory::getAllTypeCounts() const {
    return plantTypeCount;
}

std::map<std::string, double> StockInventory::getAllTypeValues() const {
    return plantTypeValue;
}

void StockInventory::displayInventorySummary() const {
    std::cout << "\n╔══════════════════════════════════════════════╗" << std::endl;
    std::cout << "║             INVENTORY BREAKDOWN              ║" << std::endl;
    std::cout << "╚══════════════════════════════════════════════╝" << std::endl;
    
    std::cout << std::left << std::setw(20) << "PLANT TYPE" 
              << std::setw(10) << "COUNT" 
              << std::setw(15) << "TOTAL VALUE" << std::endl;
    std::cout << "──────────────────────────────────────────────────" << std::endl;
    
    double grandTotal = 0.0;
    int totalCount = 0;
    
    for (const auto& entry : plantTypeCount) {
        double value = plantTypeValue.at(entry.first);
        std::cout << std::left << std::setw(20) << entry.first 
                  << std::setw(10) << entry.second 
                  << "R" << std::setw(14) << std::fixed << std::setprecision(2) << value << std::endl;
        
        grandTotal += value;
        totalCount += entry.second;
    }
    
    std::cout << "──────────────────────────────────────────────────" << std::endl;
    std::cout << std::left << std::setw(20) << "TOTALS" 
              << std::setw(10) << totalCount 
              << "R" << std::setw(14) << grandTotal << std::endl;
}