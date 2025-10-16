#include "NurseryInventoryMediator.h"
#include "Staff.h"
#include "Plant.h"
#include <iostream>

NurseryInventoryMediator::NurseryInventoryMediator() : greenhouseStock(0), salesFloorStock(0){

}

void NurseryInventoryMediator::notify(Staff *sender, const std::string &event, Plant *plant, int quantity){
    std::cout<<"Inventory mediator: "<<sender->getName()<<" triggered event: "<<event<<std::endl;
    
    if(event == "plant moved to sales"){
        updateInventory(plant, -quantity, quantity);
        std::cout<<"Updated: Greenhouse -"<<quantity<<", Sales Floor +"<<quantity<<std::endl;
    } else if(event == "plant sold"){
        updateInventory(plant, 0, -quantity);
        std::cout<<"Updated: Sales Floor -"<<quantity<<" (sold)"<<std::endl;
        
        if(getSalesFloorStock(plant) < 5){
            std::cout<<"ALERT: Low stock for "<<plant->getName()<<". Notifying gardeners..."<<std::endl;
        }  
    } else if(event == "new delivery"){
        updateInventory(plant, quantity, 0);
        std::cout<<"Updated: Greenhouse +"<<quantity<<" (new delivery)"<<std::endl;
    } else if(event == "return to greenhouse"){
        updateInventory(plant, quantity, -quantity);
        std::cout<<"Updated: Greenhouse +"<<quantity<<", Sales Floor -"<<quantity<<" (returned)"<<std::endl;
    } else if(event == "check stock"){
        std::cout<<"Current stock - Greenhouse: "<<getGreenhouseStock(plant)<<", Sales Floor: "<<getSalesFloorStock(plant)<<std::endl;
    } else {
        std::cout<<"Unknown event: "<<event<<std::endl;
    }
}

void NurseryInventoryMediator::updateInventory(Plant *plant, int greenhouseQuantity, int salesFloorQuantity){
    greenhouseStock += greenhouseQuantity;
    salesFloorStock += salesFloorQuantity;
    
    if (greenhouseStock < 0){
        greenhouseStock = 0;
    }

    if (salesFloorStock < 0){
        salesFloorStock = 0;
    }
}

int NurseryInventoryMediator::getGreenhouseStock(Plant *plant) const{
    return greenhouseStock;
}

int NurseryInventoryMediator::getSalesFloorStock(Plant *plant) const{
    return salesFloorStock;
}
