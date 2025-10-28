/*#include<iostream>

#include"Iterator.h"
#include"PlantInventory.h"
#include"Plant.h"
#include"PlantIterator.h"
#include"CareIterator.h"
#include"PriceRangeIterator.h"
//#include"InventorySystem.h"
using namespace std;

int main(){
    cout<<"Iterator design pattern testting!!"<<endl;
    //plants
    Plant p1("Rose", true, "P001", 6, 50, 10);
    Plant p2("Tulip", false, "P002", 4, 30, 8);
    Plant p3("Daisy", true, "P003", 5, 40, 6);

    p1.setCareInstructions("Fertilized");
    p2.setCareInstructions("Low");
    p3.setCareInstructions("Fertilized");
    //first create an invenory and put things in it. First iterator im testing is the PlantIterator
    PlantInventory* inventory = new PlantInventory();
    inventory->add(&p1);
    inventory->add(&p2);
    inventory->add(&p3);

    std::cout << "\n1. DEMO: PlantIterator (All Plants)" << std::endl;
    PlantIterator allPlantsIterator(inventory,"Rose");
    std::cout << "All plants in inventory:" << std::endl;
    for (allPlantsIterator.first(); !allPlantsIterator.isDone(); allPlantsIterator.next()) {
        Plant* plant = allPlantsIterator.currentItem();
        std::cout << " - " << plant->getName() << " (R" << plant->getPrice() << ")" << std::endl;
    }

    ///Testing care iterator

    std::cout << "\n2. DEMO: CareIterator (Fertilized Plants)" << std::endl;
    CareIterator careIterator(inventory, "Fertilized");
    std::cout << "Fertilized plants in inventory:" << std::endl;
    for (careIterator.first(); !careIterator.isDone(); careIterator.next()) {   
        Plant* plant = careIterator.currentItem();
        std::cout << " - " << plant->getName() << " (R" << plant->getPrice() << ")" << std::endl;
    }

   
    //delete plantIterator;
    
    return 0;

}*/
// demo_iterators.cpp
#include <iostream>
#include <vector>
#include <memory>
#include "Plant.h"
#include "PlantInventory.h"
#include "CareIterator.h"
#include "CartIterator.h"
#include "PlantIterator.h"
#include "PriceRangeIterator.h"

void demoIteratorPattern() {
    std::cout << "=== ITERATOR PATTERN DEMO ===" << std::endl;
    
    // Create a test inventory
    PlantInventory *inventory=new PlantInventory();
    
    // Add some test plants with different care instructions and prices
    Plant* plant1 = new Plant("Rose", false, "P001", 6, 3, 25);
    plant1->setCareInstructions("Water daily and provide full sunlight");
    
    Plant* plant2 = new Plant("Cactus", false, "P002", 8, 1, 15);
    plant2->setCareInstructions("Low water needs, full sunlight");
    
    Plant plant3 ("Fern", true, "P003", 4, 4, 35);
    plant3.setCareInstructions("Medium water, shade preferred");
    
    Plant plant4("Succulent", false, "P004", 6, 2, 20);
    plant4.setCareInstructions("Low maintenance, occasional watering");
    
    inventory->add(plant1);
    inventory->add(plant2);
   inventory->add(&plant3);
    inventory->add(&plant4);
    
    std::cout << "\n1. DEMO: PlantIterator (All Plants)" << std::endl;
    PlantIterator allPlantsIterator(inventory);
    std::cout << "All plants in inventory:" << std::endl;
    for (allPlantsIterator.first(); !allPlantsIterator.isDone(); allPlantsIterator.next()) {
        Plant* plant = allPlantsIterator.currentItem();
        std::cout << " - " << plant->getName() << " (R" << plant->getPrice() << ")" << std::endl;
    }
    
    /*std::cout << "\n2. DEMO: CareIterator (Low Maintenance Plants)" << std::endl;
    CareIterator lowMaintenanceIterator(inventory, "low");
    std::cout << "Low maintenance plants:" << std::endl;
    for (lowMaintenanceIterator.first(); !lowMaintenanceIterator.isDone(); lowMaintenanceIterator.next()) {
        Plant* plant = lowMaintenanceIterator.currentItem();
        std::cout << " - " << plant->getName() << ": " << plant->getCareInstructions() << std::endl;
    }
    */
    std::cout << "\n3. DEMO: PriceRangeIterator (R15-R25)" << std::endl;
    PriceRangeIterator budgetIterator(inventory, 15.0, 20.0);
    std::cout << "Plants in price range R15-R25:" << std::endl;
    for (budgetIterator.first(); !budgetIterator.isDone(); budgetIterator.next()) {
        Plant* plant = budgetIterator.currentItem();
        std::cout << " - " << plant->getName() << " (R" << plant->getPrice() << ")" << std::endl;
    }
    
    std::cout << "\n4. DEMO: CartIterator (Shopping Cart)" << std::endl;
    // Create a separate inventory for cart
    PlantInventory cart;
    cart.add(plant1); // Add rose to cart
    cart.add(&plant4); // Add succulent to cart
    
    CartIterator cartIterator(&cart);
    std::cout << "Plants in shopping cart:" << std::endl;
    double total = 0.0;
    for (cartIterator.first(); !cartIterator.isDone(); cartIterator.next()) {
        Plant* plant = cartIterator.currentItem();
        std::cout << " - " << plant->getName() << " (R" << plant->getPrice() << ")" << std::endl;
        total += plant->getPrice();
    }
    std::cout << "Cart Total: R" << total << std::endl;
    
    // Cleanup
    delete plant1;
    delete plant2;
    //delete plant3;
    //delete plant4;
}

int main() {
    demoIteratorPattern();
    return 0;
}