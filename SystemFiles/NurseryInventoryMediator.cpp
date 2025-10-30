#include "NurseryInventoryMediator.h"
#include "Staff.h"
#include "Plant.h"
#include <iostream>

NurseryInventoryMediator::NurseryInventoryMediator(){
}

void NurseryInventoryMediator::notify(Staff *sender, const std::string &event, Plant *plant, int quantity){
    std::string senderName = (sender != nullptr) ? sender->getName() : "System";
    std::cout << "Inventory mediator: " << senderName << " triggered event: " << event << std::endl;
    
    std::string plantId = getPlantId(plant);
    int currentGreenhouseStock = getGreenhouseStock(plant);
    int currentSalesFloorStock = getSalesFloorStock(plant);
    
    if(event == "plant moved to sales"){
        if(quantity > currentGreenhouseStock) {
            std::cout << "WARNING: Only " << currentGreenhouseStock << " available in greenhouse. Moving " << currentGreenhouseStock << " instead of " << quantity << std::endl;
            quantity = currentGreenhouseStock;
        }
        updateInventory(plant, -quantity, quantity);
        std::cout << "Updated " << plantId << ": Greenhouse -" << quantity << ", Sales Floor +" << quantity << std::endl;
        
    } else if(event == "plant sold"){
        if(quantity > currentSalesFloorStock) {
            std::cout << "WARNING: Only " << currentSalesFloorStock << " available on sales floor. Selling " << currentSalesFloorStock << " instead of " << quantity << std::endl;
            quantity = currentSalesFloorStock;
        }
        updateInventory(plant, 0, -quantity);
        std::cout << "Updated " << plantId << ": Sales Floor -" << quantity << " (sold)" << std::endl;
        
    } else if(event == "customer delivery"){
        if(quantity > currentSalesFloorStock) {
            std::cout << "WARNING: Only " << currentSalesFloorStock << " available on sales floor. Delivering " << currentSalesFloorStock << " instead of " << quantity << std::endl;
            quantity = currentSalesFloorStock;
        }
        updateInventory(plant, 0, -quantity);
        std::cout << "Updated " << plantId << ": Sales Floor -" << quantity << " (delivered to customer)" << std::endl;
        
    } else if(event == "new shipment"){
        updateInventory(plant, quantity, 0);
        std::cout << "Updated " << plantId << ": Greenhouse +" << quantity << " (new shipment received)" << std::endl;
        
    } else if(event == "return to greenhouse"){
        if(quantity > currentSalesFloorStock) {
            std::cout << "WARNING: Only " << currentSalesFloorStock << " available on sales floor. Returning " << currentSalesFloorStock << " instead of " << quantity << std::endl;
            quantity = currentSalesFloorStock;
        }
        updateInventory(plant, quantity, -quantity);
        std::cout << "Updated " << plantId << ": Greenhouse +" << quantity << ", Sales Floor -" << quantity << " (returned)" << std::endl;
        
    } else if(event == "check stock"){
        std::cout << "Current stock for " << plantId << " - Greenhouse: " << currentGreenhouseStock << ", Sales Floor: " << currentSalesFloorStock << std::endl;
        
    } else {
        std::cout << "Unknown event: " << event << std::endl;
    }
}

void NurseryInventoryMediator::updateInventory(Plant *plant, int greenhouseQuantity, int salesFloorQuantity){
    std::string plantId = getPlantId(plant);
    
    if (greenhouseStock.find(plantId) == greenhouseStock.end()) {
        greenhouseStock[plantId] = 0;
    }
    if (salesFloorStock.find(plantId) == salesFloorStock.end()) {
        salesFloorStock[plantId] = 0;
    }
    
    greenhouseStock[plantId] += greenhouseQuantity;
    salesFloorStock[plantId] += salesFloorQuantity;
    
    if (greenhouseStock[plantId] < 0) greenhouseStock[plantId] = 0;
    if (salesFloorStock[plantId] < 0) salesFloorStock[plantId] = 0;
}

int NurseryInventoryMediator::getGreenhouseStock(Plant *plant) const{
    std::string plantId = getPlantId(plant);
    std::unordered_map<std::string, int>::const_iterator it = greenhouseStock.find(plantId);
    return (it != greenhouseStock.end()) ? it->second : 0;
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
    
    return plant->getName();
}