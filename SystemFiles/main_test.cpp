#include "PlantContext.h"
#include "PlantState.h"
#include "SeedlingState.h"
#include "FloweringState.h"
#include "MatureState.h"
#include "ReadyForSaleState.h"
#include "SoldState.h"
#include "Plant.h"
#include <iostream>
#include <string>
#include <vector>

class TestRunner {
private:
    int passedTests;
    int failedTests;
    std::string currentTest;
    
public:
    TestRunner() : passedTests(0), failedTests(0) {}
    
    void setTest(const std::string& name) {
        currentTest = name;
        std::cout << "\n=== Running: " << name << " ===" << std::endl;
    }
    
    void assert(bool condition, const std::string& message) {
        if (condition) {
            passedTests++;
            std::cout << " PASS: " << message << std::endl;
        } else {
            failedTests++;
            std::cout << " FAIL: " << message << std::endl;
        }
    }
    
       void assertEq(int actual, int expected, const std::string& message) {
        if (actual == expected) {
            passedTests++;
            std::cout << "  PASS: " << message << " (expected: " << expected 
                      << ", got: " << actual << ")" << std::endl;
        } else {
            failedTests++;
            std::cout << "  FAIL: " << message << " (expected: " << expected 
                      << ", got: " << actual << ")" << std::endl;
        }
    }
    
    void assertEq(double actual, double expected, const std::string& message) {
        if (actual == expected) {
            passedTests++;
            std::cout << "  PASS: " << message << " (expected: " << expected 
                      << ", got: " << actual << ")" << std::endl;
        } else {
            failedTests++;
            std::cout << "  FAIL: " << message << " (expected: " << expected 
                      << ", got: " << actual << ")" << std::endl;
        }
    }
    
    void assertEq(const std::string& actual, const std::string& expected, 
                  const std::string& message) {
        if (actual == expected) {
            passedTests++;
            std::cout << "  PASS: " << message << " (expected: '" << expected 
                      << "', got: '" << actual << "')" << std::endl;
        } else {
            failedTests++;
            std::cout << "  FAIL: " << message << " (expected: '" << expected 
                      << "', got: '" << actual << "')" << std::endl;
        }
    }
    
    void printSummary() {
        std::cout << "\n" << std::string(50, '=') << std::endl;
        std::cout << "TEST SUMMARY" << std::endl;
        std::cout << std::string(50, '=') << std::endl;
        std::cout << "Total Tests: " << (passedTests + failedTests) << std::endl;
        std::cout << "Passed: " << passedTests << std::endl;
        std::cout << "Failed: " << failedTests << std::endl;
        std::cout << std::string(50, '=') << std::endl;
        
        if (failedTests == 0) {
            std::cout << "All tests passed!" << std::endl;
        } else {
            std::cout << "Some tests failed!" << std::endl;
        }
    }
};


void testPlant(TestRunner& test) {
    test.setTest("Plant Class Tests");
    
    Plant plant("Rose", false, "P001", 6, 7);
    
    test.assertEq(plant.getName(), std::string("Rose"), "Plant name");
    test.assertEq(plant.getPlantID(), std::string("P001"), "Plant ID");
    test.assertEq(plant.getExposureSunlightHours(), 6, "Sunlight hours");
    test.assertEq(plant.getLastWaterLevel(), 7, "Water level");
    test.assert(!plant.isFertilized(), "Fertilized status");
    
    plant.setName("Tulip");
    plant.setFertilized(true);
    plant.setExposureSunlightHours(8);
    
    test.assertEq(plant.getName(), std::string("Tulip"), "Updated plant name");
    test.assert(plant.isFertilized(), "Updated fertilized status");
    test.assertEq(plant.getExposureSunlightHours(), 8, "Updated sunlight hours");
}

void testSeedlingState(TestRunner& test) {
    test.setTest("SeedlingState Tests");
    
    SeedlingState seedling;
    
    test.assertEq(seedling.getStateName(), std::string("Seedling"), "State name");
    test.assertEq(seedling.getDaysinState(), 0, "Initial days in state");
    test.assert(seedling.ageDataValid(), "Age data validity");
    
    seedling.setDaysinState(5);
    seedling.setMinDaysInState(10);
    seedling.setHasReceivedProperCare(true);
    
    test.assertEq(seedling.getDaysinState(), 5, "Days in state after setting");
    test.assertEq(seedling.getRequiredDaysInState(), 10, "Required days");
    test.assert(seedling.isValid(), "State validity");
}

void testFloweringState(TestRunner& test) {
    test.setTest("FloweringState Tests");
    
    FloweringState flowering;
    
    test.assertEq(flowering.getStateName(), std::string("Flowering"), "State name");
    test.assertEq(flowering.getDaysinState(), 0, "Initial days in state");
    test.assert(!flowering.getIsInSeason(), "Initial season status");
    test.assert(flowering.ageDataValid(), "Age data validity");
    
    flowering.setDaysinState(15);
    flowering.setRequestDays(20);
    flowering.setIsInSeason(true);
    
    test.assertEq(flowering.getDaysinState(), 15, "Days in state after setting");
    test.assert(flowering.getIsInSeason(), "Season status after setting");
    
    flowering.increaseDay();
    test.assertEq(flowering.getDaysinState(), 16, "Days after increment");
}

void testMatureState(TestRunner& test) {
    test.setTest("MatureState Tests");
    
    MatureState mature;
    
    test.assertEq(mature.getStateName(), std::string("Mature"), "State name");
    test.assertEq(mature.getDaysinState(), 0, "Initial days in state");
    test.assert(!mature.getIsPrimeForSale(), "Initial prime for sale status");
    test.assert(mature.isValid(), "State validity");
    test.assert(mature.ageDataValid(), "Age data validity");
    
    mature.setDaysinState(30);
    mature.setIsPrimeForSale(true);
    mature.setIsInInSeason(true);
    
    test.assertEq(mature.getDaysinState(), 30, "Days in state after setting");
    test.assert(mature.getIsPrimeForSale(), "Prime for sale after setting");
    
    std::string readiness = mature.evaluateSaleReadiness(30);
    test.assertEq(readiness, std::string("Ready for sale"), "Sale readiness evaluation");
}

void testReadyForSaleState(TestRunner& test) {
    test.setTest("ReadyForSaleState Tests");
    
    ReadyForSaleState ready;
    
    test.assertEq(ready.getStateName(), std::string("Ready for Sale"), "State name");
    test.assertEq(ready.getDaysinState(), 0, "Initial days in state");
    test.assertEq(ready.getPrice(), 0.0, "Initial price");
    test.assert(ready.ageDataValid(), "Age data validity");
    
    ready.setPrice(25.50);
    ready.setDaysinState(5);
    ready.setSeason("Spring");
    
    test.assertEq(ready.getPrice(), 25.50, "Price after setting");
    test.assertEq(ready.getDaysinState(), 5, "Days in state after setting");
    test.assert(ready.isValid(), "State validity with price");
    
    std::string saleInfo = ready.prepareSaleForSale(30.0, "Summer");
    test.assert(saleInfo.find("30") != std::string::npos, "Sale preparation info");
}

void testSoldState(TestRunner& test) {
    test.setTest("SoldState Tests");
    
    SoldState sold;
    
    test.assertEq(sold.getStateName(), std::string("Sold"), "State name");
    test.assertEq(sold.getSoldPrice(), 0.0, "Initial sold price");
    test.assert(sold.ageDataValid(), "Age data validity");
    
    double price = sold.soldSequence(45.75, "2025-10-25", "Fall");
    
    test.assertEq(price, 45.75, "Sold price from sequence");
    test.assertEq(sold.getSoldPrice(), 45.75, "Stored sold price");
    
    std::string data = sold.getData();
    test.assert(data.find("2025-10-25") != std::string::npos, "Sale data contains date");
    test.assert(data.find("45.75") != std::string::npos, "Sale data contains price");
    test.assert(data.find("Fall") != std::string::npos, "Sale data contains season");
}

void testPlantContext(TestRunner& test) {
    test.setTest("PlantContext Tests");
    
    PlantContext context("Rose", "Spring", "", 20.0);
    
    test.assertEq(context.getPlantType(), std::string("Rose"), "Plant type");
    test.assertEq(context.getSeason(), std::string("Spring"), "Season");
    test.assertEq(context.getCurrentStateName(), std::string("Seedling"), 
                  "Initial state");
    test.assertEq(context.getAge(), 0, "Initial age");
    test.assert(!context.isReadyForSale(), "Not ready for sale initially");
    
    context.ageState(5);
    test.assertEq(context.getAge(), 5, "Age after aging");
    
    Plant* plant = context.getPlant();
    test.assert(plant != nullptr, "Plant pointer is valid");
    test.assertEq(plant->getName(), std::string("Rose"), "Plant name from context");
}

void testStateTransitions(TestRunner& test) {
    test.setTest("State Transition Tests");
    
    PlantContext context("Sunflower", "Summer", "", 15.0);
    
    test.assertEq(context.getCurrentStateName(), std::string("Seedling"), 
                  "Starts in Seedling");
    
    
    SeedlingState* seedling = dynamic_cast<SeedlingState*>(context.getState());
    if (seedling) {
        seedling->setMinDaysInState(10);
        seedling->setHasReceivedProperCare(true);
    }
    
    context.ageState(10);
    test.assertEq(context.getCurrentStateName(), std::string("Flowering"), 
                  "Transitions to Flowering");
    
    FloweringState* flowering = dynamic_cast<FloweringState*>(context.getState());
    if (flowering) {
        flowering->setRequestDays(15);
        flowering->setIsInSeason(true);
    }
    
    context.ageState(15);
    test.assertEq(context.getCurrentStateName(), std::string("Mature"), 
                  "Transitions to Mature");
    
 
    MatureState* mature = dynamic_cast<MatureState*>(context.getState());
    if (mature) {
        mature->setIsInInSeason(true);
        mature->setIsPrimeForSale(true);
    }
    
    context.harvest();
    test.assertEq(context.getCurrentStateName(), std::string("Ready for Sale"), 
                  "Transitions to Ready for Sale");
    
    test.assert(context.isReadyForSale(), "Context recognizes ready for sale state");
    
    context.harvest();
    test.assertEq(context.getCurrentStateName(), std::string("Sold"), 
                  "Transitions to Sold");
}

void testCompleteLifecycle(TestRunner& test) {
    test.setTest("Complete Plant Lifecycle Test");
    
    PlantContext context("Tomato", "Spring", "", 12.50);
    
    std::cout << "\n--- Starting Complete Lifecycle ---" << std::endl;
    
    
    context.checkReadiness();
    SeedlingState* seedling = dynamic_cast<SeedlingState*>(context.getState());
    if (seedling) {
        seedling->setMinDaysInState(7);
        seedling->setHasReceivedProperCare(true);
        context.ageState(7);
    }
    
    test.assertEq(context.getCurrentStateName(), std::string("Flowering"), 
                  "Lifecycle: Moved to Flowering");
    
    
    FloweringState* flowering = dynamic_cast<FloweringState*>(context.getState());
    if (flowering) {
        flowering->setRequestDays(14);
        flowering->setIsInSeason(true);
        context.ageState(14);
    }
    
    test.assertEq(context.getCurrentStateName(), std::string("Mature"), 
                  "Lifecycle: Moved to Mature");
    
   
    MatureState* mature = dynamic_cast<MatureState*>(context.getState());
    if (mature) {
        mature->setIsInInSeason(true);
        context.ageState(30);
    }
    
    test.assert(mature->getIsPrimeForSale(), "Lifecycle: Plant is prime for sale");
    

    context.harvest();
    test.assertEq(context.getCurrentStateName(), std::string("Ready for Sale"), 
                  "Lifecycle: Ready for sale after harvest");
    
    ReadyForSaleState* ready = dynamic_cast<ReadyForSaleState*>(context.getState());
    if (ready) {
        ready->setPrice(25.00);
    }
    
    context.harvest();
    test.assertEq(context.getCurrentStateName(), std::string("Sold"), 
                  "Lifecycle: Sold after final harvest");
    
    int totalAge = context.getAge();
    test.assert(totalAge >= 51, "Lifecycle: Total age is correct");
    
    std::cout << "--- Lifecycle Complete ---\n" << std::endl;
}
