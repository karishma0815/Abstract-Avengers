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

// Simple test framework
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
    
   