// test_iterators.cpp
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "Plant.h"
#include "PlantInventory.h"
#include "Iterator.h"
#include "CartIterator.h"
#include "PlantIterator.h"
#include "PriceRangeIterator.h"
#include "Rose.h"
#include "Cacti.h"
#include "Orchid.h"
#include "Jade.h"
#include "Lotus.h"
#include <vector>
#include <memory>

// Test case: PlantIterator with empty inventory
TEST_CASE("PlantIterator with Empty Inventory") {
    PlantInventory inventory;
    PlantIterator iterator(&inventory);
    
    iterator.first();
    CHECK(iterator.isDone() == true);
    CHECK(iterator.currentItem() == nullptr);
    
    iterator.next();
    CHECK(iterator.isDone() == true);
    
    CHECK(iterator.hasNext() == false);
}

// Test case: PlantIterator with multiple plants
TEST_CASE("PlantIterator with Multiple Plants") {
    PlantInventory inventory;
    
    // Add test plants using real plant classes
    Plant* plant1 = new Rose("Rose", 25.0);
    Plant* plant2 = new Cacti("Cactus", 15.0);
    Plant* plant3 = new Orchid("Fern", 35.0);
    
    inventory.add(plant1);
    inventory.add(plant2);
    inventory.add(plant3);
    
    PlantIterator iterator(&inventory);
    
    // Test iteration
    iterator.first();
    CHECK(iterator.isDone() == false);
    CHECK(iterator.currentItem()->getName() == "Rose");
    
    iterator.next();
    CHECK(iterator.isDone() == false);
    CHECK(iterator.currentItem()->getName() == "Cactus");
    
    iterator.next();
    CHECK(iterator.isDone() == false);
    CHECK(iterator.currentItem()->getName() == "Fern");
    
    iterator.next();
    CHECK(iterator.isDone() == true);
    CHECK(iterator.currentItem() == nullptr);
    
    // Cleanup
    //delete plant1;
    //delete plant2;
    //delete plant3;
}

// Test case: PriceRangeIterator filters by price
TEST_CASE("PriceRangeIterator Filters by Price Range") {
    PlantInventory inventory;
    
    Plant* cheapPlant = new Cacti("Cactus", 10.0);
    Plant* mediumPlant = new Orchid("Fern", 25.0);
    Plant* expensivePlant = new Rose("Rose", 50.0);
    
    inventory.add(cheapPlant);
    inventory.add(mediumPlant);
    inventory.add(expensivePlant);
    
    // Test price range 15-30
    PriceRangeIterator priceIterator(&inventory, 15.0, 30.0);
    
    int count = 0;
    for (priceIterator.first(); !priceIterator.isDone(); priceIterator.next()) {
        double price = priceIterator.currentItem()->getPrice();
        CHECK(price >= 15.0);
        CHECK(price <= 30.0);
        count++;
    }
    
    CHECK(count == 1); // Only fern should be in range
    
    // Cleanup
    //delete cheapPlant;
    //delete mediumPlant;
    //delete expensivePlant;
}

// Test case: CartIterator works with shopping cart
TEST_CASE("CartIterator with Shopping Cart") {
    PlantInventory cart; // Represents shopping cart
    
    Plant* plant1 = new Rose("Rose", 25.0);
    Plant* plant2 = new Cacti("Cactus", 15.0);
    
    cart.add(plant1);
    cart.add(plant2);
    
    CartIterator cartIterator(&cart);
    
    // Test cart iteration
    double total = 0.0;
    int count = 0;
    
    for (cartIterator.first(); !cartIterator.isDone(); cartIterator.next()) {
        total += cartIterator.currentItem()->getPrice();
        count++;
    }
    
    CHECK(count == 2);
    CHECK(total == 40.0); // 25 + 15
    
    // Cleanup
    //delete plant1;
    //delete plant2;
}

// Test case: Iterator hasNext() method
TEST_CASE("Iterator HasNext Method") {
    PlantInventory inventory;
    
    Plant* plant1 = new Jade("Plant1", 10.0);
    Plant* plant2 = new Lotus("Plant2", 20.0);
    
    inventory.add(plant1);
    inventory.add(plant2);
    
    PlantIterator iterator(&inventory);
    
    iterator.first();
    CHECK(iterator.hasNext() == true); // Should have next (plant2)
    
    iterator.next();
    CHECK(iterator.hasNext() == false); // No more plants
    
    // Cleanup
    //delete plant1;
    //delete plant2;
}

// Test case: Mixed iterator types
TEST_CASE("Multiple Iterator Types Work Independently") {
    PlantInventory inventory;
    
    Plant* plant1 = new Rose("LowCarePlant", 10.0);
    Plant* plant2 = new Orchid("HighCarePlant", 40.0);
    Plant* plant3 = new Cacti("BudgetPlant", 15.0);
    
    inventory.add(plant1);
    inventory.add(plant2);
    inventory.add(plant3);
    
    // Test different iterators on same inventory
    PlantIterator allIterator(&inventory);
    PriceRangeIterator priceIterator(&inventory, 10.0, 20.0);
    
    int allCount = 0, priceCount = 0;
    
    // Count all plants
    for (allIterator.first(); !allIterator.isDone(); allIterator.next()) {
        allCount++;
    }
    // Count plants in price range
    for (priceIterator.first(); !priceIterator.isDone(); priceIterator.next()) {
        priceCount++;
    }
    
    CHECK(allCount == 3);
    CHECK(priceCount == 2); // Plants costing 10 and 15
    
    // Cleanup
    //delete plant1;
    //delete plant2;
    //delete plant3;
}

// Test case: Edge cases for iterators
TEST_CASE("Iterator Edge Cases") {
    SUBCASE("Empty inventory for all iterator types") {
        PlantInventory emptyInventory;
        
        PlantIterator plantIt(&emptyInventory);
        PriceRangeIterator priceIt(&emptyInventory, 0.0, 100.0);
        CartIterator cartIt(&emptyInventory);
        
        CHECK(plantIt.isDone() == true);
        CHECK(priceIt.isDone() == true);
        CHECK(cartIt.isDone() == true);
    }
    
    SUBCASE("Single plant inventory") {
        PlantInventory singleInventory;
        Plant* singlePlant = new Jade("Single", 10.0);
        singleInventory.add(singlePlant);
        
        PlantIterator it(&singleInventory);
        it.first();
        CHECK(it.isDone() == false);
        CHECK(it.currentItem()->getName() == "Single");
        CHECK(it.hasNext() == false);
        
        it.next();
        CHECK(it.isDone() == true);
        
        //delete singlePlant;
    }
}