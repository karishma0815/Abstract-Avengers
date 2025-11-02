#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include <iostream>
#include <sstream>
#include <vector>
#include <functional>

// Include all necessary headers
#include "PlantFactory.h"
#include "FlowerFactory.h"
#include "SucculentFactory.h"
#include "TreeFactory.h"
#include "Flower.h"
#include "Rose.h"
#include "Lotus.h"
#include "Protea.h"
#include "Succulent.h"
#include "Cacti.h"
#include "Jade.h"
#include "Orchid.h"
#include "Tree.h"
#include "Apple.h"
#include "Pine.h"
#include "Jacaranda.h"
#include "FlowerGroup.h"
#include "SucculentGroup.h"
#include "TreeGroup.h"
#include "StockManager.h"
#include "InventoryObserver.h"
#include "StaffNotificationObserver.h"


std::string captureOutput(void (*func)()) {
    std::stringstream buffer;
    std::streambuf* old = std::cout.rdbuf(buffer.rdbuf());
    func();
    std::cout.rdbuf(old);
    return buffer.str();
}

void testOutputFunc() {
    std::cout << "Test output";
}

void testRoseWatering() {
    Rose rose("Test Rose", 25.99, "Hybrid Tea");
    rose.water(0.3);
}

void testCactusSunlight() {
    Cacti cactus("Test Cactus", 12.99, "Opuntia");
    cactus.provideSunlight(4, "direct");
}



TEST_SUITE("Factory Pattern Tests") {
    TEST_CASE("FlowerFactory creates different flowers") {
        FlowerFactory flowerFactory;
        
        FlowerProduct* rose = flowerFactory.createFlower("Red Beauty", 25.99, "Rose", 1);
        FlowerProduct* lotus = flowerFactory.createFlower("Sacred", 35.50, "Lotus", 1);
        FlowerProduct* protea = flowerFactory.createFlower("King", 45.75, "Protea", 1);
        FlowerProduct* generic = flowerFactory.createFlower("Generic", 15.00, "Unknown", 1);
        
        CHECK(rose->getPlantType() == "Rose");
        CHECK(lotus->getPlantType() == "Lotus");
        CHECK(protea->getPlantType() == "Protea");
        CHECK(generic->getPlantType() == "Flower");
        
        CHECK(rose->getTotalValue() == doctest::Approx(25.99));
        CHECK(lotus->getTotalValue() == doctest::Approx(35.50));
        
        delete rose;
        delete lotus;
        delete protea;
        delete generic;
    }
    
    TEST_CASE("SucculentFactory creates different succulents") {
        SucculentFactory succulentFactory;
        
        SucculentProduct* cactus = succulentFactory.createSucculent("Prickly", 12.99, "Cacti", 1);
        SucculentProduct* jade = succulentFactory.createSucculent("Green", 18.50, "Jade", 1);
        SucculentProduct* orchid = succulentFactory.createSucculent("Moth", 22.75, "Orchid", 1);
        SucculentProduct* generic = succulentFactory.createSucculent("Generic", 8.00, "Unknown", 1);
        
        CHECK(cactus->getPlantType() == "Cacti");
        CHECK(jade->getPlantType() == "Jade");
        CHECK(orchid->getPlantType() == "Orchid");
        CHECK(generic->getPlantType() == "Succulent");
        
        CHECK(cactus->getTotalValue() == doctest::Approx(12.99));
        CHECK(jade->getTotalValue() == doctest::Approx(18.50));
        
        delete cactus;
        delete jade;
        delete orchid;
        delete generic;
    }
    
    TEST_CASE("TreeFactory creates different trees") {
        TreeFactory treeFactory;
        
        TreeProduct* pine = treeFactory.createTree("Scotch", 89.99, "Pine", 1);
        TreeProduct* apple = treeFactory.createTree("Fuji", 120.50, "Apple", 1);
        TreeProduct* jacaranda = treeFactory.createTree("Blue", 150.75, "Jacaranda", 1);
        TreeProduct* generic = treeFactory.createTree("Generic", 45.00, "Unknown", 1);
        
        CHECK(pine->getPlantType() == "Pine");
        CHECK(apple->getPlantType() == "Apple");
        CHECK(jacaranda->getPlantType() == "Jacaranda");
        CHECK(generic->getPlantType() == "Tree");
        
        CHECK(pine->getTotalValue() == doctest::Approx(89.99));
        CHECK(apple->getTotalValue() == doctest::Approx(120.50));
        
        delete pine;
        delete apple;
        delete jacaranda;
        delete generic;
    }
}



TEST_SUITE("Composite Pattern Tests") {
    TEST_CASE("FlowerGroup composite operations") {
        FlowerProduct* rose = new Rose("Red Rose", 25.99, "Hybrid Tea");
        FlowerProduct* lotus = new Lotus("Sacred Lotus", 35.50, "Nelumbo nucifera");
        FlowerGroup* flowerGroup = new FlowerGroup("Spring Flowers");
        
        // Test empty group
        CHECK(flowerGroup->getCount() == 0);
        CHECK(flowerGroup->getTotalValue() == doctest::Approx(0.0));
        
        // Test adding plants
        flowerGroup->add(rose);
        flowerGroup->add(lotus);
        
        CHECK(flowerGroup->getCount() == 2);
        CHECK(flowerGroup->getTotalValue() == doctest::Approx(25.99 + 35.50));
        
        // Test removing plants
        flowerGroup->remove(rose);
        CHECK(flowerGroup->getCount() == 1);
        CHECK(flowerGroup->getTotalValue() == doctest::Approx(35.50));
        
        delete flowerGroup;
    }
    
    TEST_CASE("SucculentGroup composite operations") {
        SucculentProduct* cactus = new Cacti("Prickly Pear", 12.99, "Opuntia");
        SucculentProduct* jade = new Jade("Green Jade", 18.50, "Crassula ovata");
        SucculentGroup* succulentGroup = new SucculentGroup("Desert Collection");
        
        // Test empty group
        CHECK(succulentGroup->getCount() == 0);
        CHECK(succulentGroup->getTotalValue() == doctest::Approx(0.0));
        
        // Test adding plants
        succulentGroup->add(cactus);
        succulentGroup->add(jade);
        
        CHECK(succulentGroup->getCount() == 2);
        CHECK(succulentGroup->getTotalValue() == doctest::Approx(12.99 + 18.50));
        
        // Test removing plants
        succulentGroup->remove(cactus);
        CHECK(succulentGroup->getCount() == 1);
        CHECK(succulentGroup->getTotalValue() == doctest::Approx(18.50));
        
        delete succulentGroup;
    }
    
    TEST_CASE("TreeGroup composite operations") {
        TreeProduct* apple = new Apple("Fuji Apple", 120.50, "Malus domestica");
        TreeProduct* pine = new Pine("Scotch Pine", 89.99, "Pinus sylvestris");
        TreeGroup* treeGroup = new TreeGroup("Orchard Trees");
        
        // Test empty group
        CHECK(treeGroup->getCount() == 0);
        CHECK(treeGroup->getTotalValue() == doctest::Approx(0.0));
        
        // Test adding plants
        treeGroup->add(apple);
        treeGroup->add(pine);
        
        CHECK(treeGroup->getCount() == 2);
        CHECK(treeGroup->getTotalValue() == doctest::Approx(120.50 + 89.99));
        
        // Test removing plants
        treeGroup->remove(apple);
        CHECK(treeGroup->getCount() == 1);
        CHECK(treeGroup->getTotalValue() == doctest::Approx(89.99));
        
        delete treeGroup;
    }
}



TEST_SUITE("Plant Functionality Tests") {
    TEST_CASE("Plant care instructions") {
        Rose rose("Test Rose", 25.99, "Hybrid Tea");
        Cacti cactus("Test Cactus", 12.99, "Opuntia");
        Apple apple("Test Apple", 120.50, "Fuji");
        
        CHECK(rose.getCareInstructions().find("ROSE CARE") != std::string::npos);
        CHECK(cactus.getCareInstructions().find("CACTI CARE") != std::string::npos);
        CHECK(apple.getCareInstructions().find("APPLE TREE CARE") != std::string::npos);
    }
    
    TEST_CASE("Plant watering functionality") {
        std::string output = captureOutput(testRoseWatering);
        CHECK(output.find("ROSE CARE") != std::string::npos);
        CHECK(output.find("regular watering") != std::string::npos);
    }
    
    TEST_CASE("Plant sunlight functionality") {
        std::string output = captureOutput(testCactusSunlight);
        CHECK(output.find("CACTI CARE") != std::string::npos);
        CHECK(output.find("hours of sun") != std::string::npos);
    }
    
    TEST_CASE("Plant price and value") {
        /*Rose rose("Test Rose", 25.99, "Hybrid Tea");
        CHECK(rose.getTotalValue() == doctest::Approx(25.99));
        
        FlowerGroup group("Test Group");
        group.add(&rose);
        CHECK(group.getTotalValue() == doctest::Approx(25.99));*/

        FlowerProduct* rose = new Rose("Test Rose", 25.99, "Hybrid Tea");
        CHECK(rose->getTotalValue() == doctest::Approx(25.99));
    
        FlowerGroup group("Test Group");
        group.add(rose);  // Now group owns the rose and will delete it
        CHECK(group.getTotalValue() == doctest::Approx(25.99));
    }
}


TEST_SUITE("Stock Manager Tests") {
    TEST_CASE("Stock manager basic operations") {
        StockManager stockManager;
        
        FlowerProduct* rose = new Rose("Test Rose", 25.99, "Test");
        stockManager.addFlower(rose);
        
        CHECK(stockManager.getFlowerStockSize() == 1);
        CHECK(stockManager.getTotalStockCount() == 1);
        CHECK(stockManager.getTotalStockValue() == doctest::Approx(25.99));
        
        // Clean
      //  stockManager.clearAllStock();
    }
    
    TEST_CASE("Stock manager multiple plant types") {
        StockManager stockManager;
        
        FlowerProduct* rose = new Rose("Rose", 25.99, "Test");
        SucculentProduct* cactus = new Cacti("Cactus", 12.99, "Test");
        TreeProduct* apple = new Apple("Apple", 120.50, "Test");
        
        stockManager.addFlower(rose);
        stockManager.addSucculent(cactus);
        stockManager.addTree(apple);
        
        CHECK(stockManager.getFlowerStockSize() == 1);
        CHECK(stockManager.getSucculentStockSize() == 1);
        CHECK(stockManager.getTreeStockSize() == 1);
        CHECK(stockManager.getTotalStockCount() == 3);
        
        // Clean
    //    stockManager.clearAllStock();
    }
}



TEST_SUITE("Observer Pattern Tests") {
    TEST_CASE("InventoryObserver basic functionality") {
        InventoryObserver observer(2);
        
        // Test initial state
        CHECK(observer.getStockLevel("Rose") == 0);
        CHECK(observer.getTotalInventoryCount() == 0);
        
        // Test updating
        observer.update("Rose", 5, "added");
        CHECK(observer.getStockLevel("Rose") == 5);
        CHECK(observer.getTotalInventoryCount() == 5);
        
        observer.update("Rose", 2, "removed");
        CHECK(observer.getStockLevel("Rose") == 3);
    }
    
    TEST_CASE("StaffNotificationObserver basic functionality") {
        StaffNotificationObserver observer(false);
        
        //initial state
        CHECK(observer.getLogSize() == 0);
        
        //updating
        observer.update("Rose", 1, "added");
        CHECK(observer.getLogSize() == 1);
        
        observer.update("Cacti", 2, "added");
        CHECK(observer.getLogSize() == 2);
    }
}