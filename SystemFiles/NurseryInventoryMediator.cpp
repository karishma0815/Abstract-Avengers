#include "NurseryInventoryMediator.h"
#include "Staff.h"
#include "Plant.h"
#include <iostream>

NurseryInventoryMediator::NurseryInventoryMediator(){
    
}

void NurseryInventoryMediator::notify(Staff *sender, const std::string &event, Plant *plant, int quantity){
    std::string senderName = (sender != nullptr) ? sender->getName() : "System";
    std::cout << " Inventory mediator: " << senderName << " triggered event: " << event << std::endl;
    
    std::string plantId = getPlantId(plant);
    int currentSalesFloorStock = getSalesFloorStock(plant);
    
    if(event == "plant moved to sales"){
        updateInventory(plant, quantity);
        std::cout << " Moved " << quantity << " " << plantId << " from greenhouse to sales floor. Sales floor now has: " 
                  << getSalesFloorStock(plant) << std::endl;
        
    } else if(event == "plant sold"){
        if(quantity > currentSalesFloorStock) {
            std::cout << "WARNING: Only " << currentSalesFloorStock << " available on sales floor. Selling " << currentSalesFloorStock << " instead of " << quantity << std::endl;
            quantity = currentSalesFloorStock;
        }
        
        if (quantity > 0) {
            updateInventory(plant, -quantity);
            std::cout << " Sold " << quantity << " " << plantId << " from sales floor. Remaining: " 
                      << getSalesFloorStock(plant) << std::endl;
            autoRestockIfNeeded(plantId);
        } else {
            std::cout << " Cannot sell " << plantId << " - out of stock on sales floor!" << std::endl;
        }
        
    } else if(event == "customer delivery"){
        if(quantity > currentSalesFloorStock) {
            std::cout << "WARNING: Only " << currentSalesFloorStock << " available on sales floor. Delivering " << currentSalesFloorStock << " instead of " << quantity << std::endl;
            quantity = currentSalesFloorStock;
        }
        
        if (quantity > 0) {
            updateInventory(plant, -quantity);
            std::cout << " Delivered " << quantity << " " << plantId << " to customer. Sales floor remaining: " 
                      << getSalesFloorStock(plant) << std::endl;
            
            autoRestockIfNeeded(plantId);
        }
        
    } else if(event == "new shipment"){
        std::cout << " Greenhouse always has stock for " << plantId << ". No need for new shipments." << std::endl;
        
    } else if(event == "return to greenhouse"){
        if(quantity > currentSalesFloorStock) {
            std::cout << "WARNING: Only " << currentSalesFloorStock << " available on sales floor. Returning " << currentSalesFloorStock << " instead of " << quantity << std::endl;
            quantity = currentSalesFloorStock;
        }
        
        updateInventory(plant, -quantity);
        std::cout << " Returned " << quantity << " " << plantId << " from sales floor to greenhouse. Sales floor now has: " 
                  << getSalesFloorStock(plant) << std::endl;
        
    } else if(event == "check stock"){
        std::cout << " Current stock for " << plantId << " - Greenhouse: ALWAYS IN STOCK, Sales Floor: " << currentSalesFloorStock << std::endl;
        
    } else if(event == "restock from greenhouse"){
        restockFromGreenhouse(plant, quantity);
        
    } else {
        std::cout << " Unknown event: " << event << std::endl;
    }
}

void NurseryInventoryMediator::updateInventory(Plant *plant, int salesFloorQuantity){
    std::string plantId = getPlantId(plant);
    
    if (salesFloorStock.find(plantId) == salesFloorStock.end()) {
        salesFloorStock[plantId] = 0;
    }
    
    salesFloorStock[plantId] += salesFloorQuantity;
    
    if (salesFloorStock[plantId] < 0) {
        salesFloorStock[plantId] = 0;
    }
}

int NurseryInventoryMediator::getGreenhouseStock(Plant *plant) const{
    return 1000000;
}

int NurseryInventoryMediator::getSalesFloorStock(Plant *plant) const{
    std::string plantId = getPlantId(plant);
    std::unordered_map<std::string, int>::const_iterator it = salesFloorStock.find(plantId);
    return (it != salesFloorStock.end()) ? it->second : 0;
}

std::string NurseryInventoryMediator::getPlantId(Plant *plant) const{
    if (plant == nullptr) {
        return "NULL_PLANT";
    }
    
    std::string name = plant->getName();
    
    std::string lowerName = name;
    for (size_t i = 0; i < lowerName.length(); i++) {
        lowerName[i] = std::tolower(lowerName[i]);
    }
    
    if (lowerName.find("rose") != std::string::npos) {
        return "rose";
    } else if (lowerName.find("orchid") != std::string::npos) {
        return "orchid";
    } else if (lowerName.find("jade") != std::string::npos) {
        return "jade";
    }
    
    return name;
}

void NurseryInventoryMediator::autoRestockIfNeeded(const std::string &plantId){
    if (salesFloorStock.find(plantId) == salesFloorStock.end()) {
        return;
    }
    
    int currentStock = salesFloorStock[plantId];
    
    if (INITIAL_SALES_FLOOR_STOCK.find(plantId) == INITIAL_SALES_FLOOR_STOCK.end()) {
        return;
    }
    
    int initialStock = INITIAL_SALES_FLOOR_STOCK.at(plantId);
    
    if (currentStock == 0) {
        int restockAmount = initialStock;
        salesFloorStock[plantId] = initialStock;
        std::cout << " AUTO-RESTOCK: Restocked " << restockAmount << " " << plantId 
                  << " from greenhouse. Sales floor now has: " << salesFloorStock[plantId] << std::endl;
    }
}

void NurseryInventoryMediator::restockFromGreenhouse(Plant *plant, int quantity){
    if (quantity <= 0) {
        throw std::invalid_argument("Restock quantity must be positive");
    }
    
    std::string plantId = getPlantId(plant);
    
    salesFloorStock[plantId] += quantity;
    std::cout << " RESTOCKED " << quantity << " " << plantId 
              << " from greenhouse. Sales floor now has: " << salesFloorStock[plantId] << std::endl;
}

bool NurseryInventoryMediator::canSellFromSalesFloor(Plant *plant){
    std::string plantId = getPlantId(plant);
    return (salesFloorStock.find(plantId) != salesFloorStock.end() && salesFloorStock[plantId] > 0);
}
