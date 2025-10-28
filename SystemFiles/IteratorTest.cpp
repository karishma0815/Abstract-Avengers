// test_iterators.cpp
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "Plant.h"
#include "PlantInventory.h"
#include "Iterator.h"
#include "CareIterator.h"
#include "CartIterator.h"
#include "PlantIterator.h"
#include "PriceRangeIterator.h"
#include <vector>
#include <memory>

// Mock Plant class for testing (if your actual Plant class has dependencies)
class TestPlant : public Plant {
public:
    TestPlant(std::string name, double price, std::string careInstructions = "") 
        : Plant(name, false, "TEST_" + name, 5, 3, price) {
        setCareInstructions(careInstructions);
    }
};

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
    
    // Add test plants
    Plant* plant1 = new TestPlant("Rose", 25.0, "Water daily");
    Plant* plant2 = new TestPlant("Cactus", 15.0, "Low water needs");
    Plant* plant3 = new TestPlant("Fern", 35.0, "Medium water");
    
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

//Test case: CareIterator filters correctly
TEST_CASE("CareIterator Filters by Care Instructions") {
    PlantInventory inventory;
    
    Plant* lowCarePlant = new TestPlant("Cactus", 15.0, "Low maintenance plant");
    Plant* highCarePlant = new TestPlant("Rose", 25.0, "Needs daily care and attention");
    Plant* mediumCarePlant = new TestPlant("Fern", 20.0, "Medium care requirements");
    
    inventory.add(lowCarePlant);
    inventory.add(highCarePlant);
    inventory.add(mediumCarePlant);
    
    // Test filtering for "low" care plants
    CareIterator lowCareIterator(&inventory, "low");
    
    int count = 0;
    for (lowCareIterator.first(); !lowCareIterator.isDone(); lowCareIterator.next()) {
        std::string care = lowCareIterator.currentItem()->getCareInstructions();
        // Convert to lowercase for check
        std::string lowerCare = care;
        std::transform(lowerCare.begin(), lowerCare.end(), lowerCare.begin(), ::tolower);
        CHECK(lowerCare.find("low") != std::string::npos);
        count++;
    }
    
    CHECK(count == 1); // Only cactus should match
    
    // Cleanup
    //delete lowCarePlant;
    //delete highCarePlant;
    //delete mediumCarePlant;
}

// Test case: PriceRangeIterator filters by price
TEST_CASE("PriceRangeIterator Filters by Price Range") {
    PlantInventory inventory;
    
    Plant* cheapPlant = new TestPlant("Cactus", 10.0);
    Plant* mediumPlant = new TestPlant("Fern", 25.0);
    Plant* expensivePlant = new TestPlant("Rose", 50.0);
    
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
    
    Plant* plant1 = new TestPlant("Rose", 25.0);
    Plant* plant2 = new TestPlant("Cactus", 15.0);
    
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
    
    Plant* plant1 = new TestPlant("Plant1", 10.0);
    Plant* plant2 = new TestPlant("Plant2", 20.0);
    
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
    
    Plant* plant1 = new TestPlant("LowCarePlant", 10.0, "Low maintenance");
    Plant* plant2 = new TestPlant("HighCarePlant", 40.0, "High maintenance needed");
    Plant* plant3 = new TestPlant("BudgetPlant", 15.0, "Easy to care for");
    
    inventory.add(plant1);
    inventory.add(plant2);
    inventory.add(plant3);
    
    // Test different iterators on same inventory
    PlantIterator allIterator(&inventory);
    CareIterator careIterator(&inventory, "low");
    PriceRangeIterator priceIterator(&inventory, 10.0, 20.0);
    
    int allCount = 0, careCount = 0, priceCount = 0;
    
    // Count all plants
    for (allIterator.first(); !allIterator.isDone(); allIterator.next()) {
        allCount++;
    }
    
    // Count low care plants
    for (careIterator.first(); !careIterator.isDone(); careIterator.next()) {
        careCount++;
    }
    
    // Count plants in price range
    for (priceIterator.first(); !priceIterator.isDone(); priceIterator.next()) {
        priceCount++;
    }
    
    CHECK(allCount == 3);
    CHECK(careCount == 1); // Only "Low maintenance" contains "low"
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
        CareIterator careIt(&emptyInventory, "any");
        PriceRangeIterator priceIt(&emptyInventory, 0.0, 100.0);
        CartIterator cartIt(&emptyInventory);
        
        CHECK(plantIt.isDone() == true);
        CHECK(careIt.isDone() == true);
        CHECK(priceIt.isDone() == true);
        CHECK(cartIt.isDone() == true);
    }
    
    SUBCASE("Single plant inventory") {
        PlantInventory singleInventory;
        Plant* singlePlant = new TestPlant("Single", 10.0, "Test care");
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