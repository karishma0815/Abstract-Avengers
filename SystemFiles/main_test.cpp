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


