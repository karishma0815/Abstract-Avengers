/*Abstract Avengers*/

/*
Demonstrates:
  Personalization: Builder, Decorator, Prototype
  Customer Browsing & Checkout: State (incl. assistance, OOS, failure/retry)
*/

#include <iostream>
#include <memory>
#include <string>

// Personalization
#include "PrototypeRegistry.h"
#include "Item.h"
#include "PlantItem.h"

#include "Arrangement.h"
#include "ArrangementBuilder.h"
#include "ConcreteArrangementBuilder.h"
#include "Director.h"
#include "DecorativePot.h"
#include "GiftWrap.h"
#include "Note.h"

#include "SalesContext.h"
#include "BrowsingState.h"
#include "AwaitingStockState.h"   //we drive via events
#include "Customer.h"

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
#include <iomanip>

#include <iostream>
#include "StockManager.h"
#include "FlowerFactory.h"
#include "SucculentFactory.h"
#include "TreeFactory.h"
#include "StaffNotificationObserver.h"
#include "Rose.h"
#include "Lotus.h"
#include "Protea.h"
#include "Cacti.h"
#include "Jade.h"
#include "Orchid.h"
#include "Pine.h"
#include "Apple.h"
#include "Jacaranda.h"

#include <iostream>
#include "Plant.h"
#include "WaterCommand.h"
#include "FertilizeCommand.h"
#include "PruneCommand.h"
#include "Gardener.h"
#include "SunlightCommand.h"

#include "PlantIssue.h"
#include "JuniorGardener.h"
#include "SeniorGardener.h"
#include "PlantSpecialist.h"

#include "NurseryInventoryMediator.h"
#include "SalesAssistant.h"
#include "Manager.h"
#include "DeliveryStaff.h"

#include "CustomerQuery.h"
#include "JuniorStaff.h"
#include "SalesExpert.h"
#include "PlantExpert.h"
#include "Manager.h"
#include "SalesAssistant.h"

#include "StaffFactory.h"
#include "GardenerFactory.h"
#include "SalesAssistantFactory.h"
#include "ManagerFactory.h"
#include "DeliveryStaffFactory.h"

///Customer_Sales/Iterator+cmd+strategy includes
#include <vector>
#include <memory>
#include <iostream>
#include <string>
#include <iomanip>
#include "Plant.h"
#include "PlantInventory.h"
#include "CareIterator.h"
#include "CartIterator.h"
#include "PlantIterator.h"
#include "PriceRangeIterator.h"
// Command-pattern demo includes
#include "Invoker.h"
#include "AddToCart.h"
#include "RemoveFromCart.h"
// Strategy-pattern demo includes
#include "StratContext.h"
#include "PricingStrategy.h"
#include "RegularPrice.h"
#include "BulkDiscount.h"
#include "RecommStrategy.h"
#include "DefaultRecomm.h"
#include "WaterRecomm.h"
#include "SunlightRecomm.h"


void printSeparator(const std::string& title = "");
void printPlantInfo(PlantContext* context);
//kiolin start

void testIndividualPlants(StockManager& stockManager) {
    std::cout << "\n TEST 1: INDIVIDUAL PLANT CREATION & STOCK MANAGEMENT\n";
    std::cout << "\n\n";
    
    // Create specific plant types directly
    Rose* redRose = new Rose("Red Rose", 45.99, "Hybrid Tea");
    Lotus* pinkLotus = new Lotus("Pink Lotus", 65.50, "Sacred Lotus");
    Protea* kingProtea = new Protea("King Protea", 89.99, "King Protea");
    
    Cacti* pricklyPear = new Cacti("Prickly Pear", 32.75, "Prickly Pear");
    Jade* luckyJade = new Jade("Lucky Jade", 28.50, "Crassula Ovata");
    Orchid* mothOrchid = new Orchid("Moth Orchid", 55.25, "Phalaenopsis");
    
    Pine* scotchPine = new Pine("Scotch Pine", 120.00, "Pinus Sylvestris");
    Apple* fujiApple = new Apple("Fuji Apple", 95.75, "Malus Domestica");
    Jacaranda* blueJacaranda = new Jacaranda("Blue Jacaranda", 150.00, "Jacaranda Mimosifolia");
    
    // Add to stock
    stockManager.addFlower(redRose);
    stockManager.addFlower(pinkLotus);
    stockManager.addFlower(kingProtea);
    
    stockManager.addSucculent(pricklyPear);
    stockManager.addSucculent(luckyJade);
    stockManager.addSucculent(mothOrchid);
    
    stockManager.addTree(scotchPine);
    stockManager.addTree(fujiApple);
    stockManager.addTree(blueJacaranda);
    
    std::cout << " Added 9 individual plants of specific types\n";
}

void testFactoryProduction(StockManager& stockManager) {
    std::cout << "\n TEST 2: FACTORY PATTERN PRODUCTION\n";
    std::cout << "\n\n";
    
    FlowerFactory flowerFactory;
    SucculentFactory succulentFactory;
    TreeFactory treeFactory;
    
    // Factory creates different plant types automatically
    for (int i = 0; i < 6; i++) {
        FlowerProduct* flower = flowerFactory.createFlower("Factory Flower " + std::to_string(i), 25.00 + i, 1);
        SucculentProduct* succulent = succulentFactory.createSucculent("Factory Succulent " + std::to_string(i), 15.00 + i, 1);
        TreeProduct* tree = treeFactory.createTree("Factory Tree " + std::to_string(i), 80.00 + i, 1);
        
        stockManager.addFlower(flower);
        stockManager.addSucculent(succulent);
        stockManager.addTree(tree);
    }
    
    std::cout << " Factories produced 6 plants each with automatic type variation\n";
}

void testCompositePattern(StockManager& stockManager) {
    std::cout << "\n TEST 3: COMPOSITE PATTERN - PLANT GROUPS\n";
    std::cout << "/n\n";
    
    FlowerFactory flowerFactory;
    SucculentFactory succulentFactory;
    TreeFactory treeFactory;
    
    // Create anniversary bouquet (FlowerGroup)
    FlowerGroup* anniversaryBouquet = flowerFactory.createFlowerGroup("30th Anniversary Bouquet");
    
    // Add specific flowers to the bouquet
    anniversaryBouquet->add(new Rose("Red Rose", 45.99, "Grandiflora"));
    anniversaryBouquet->add(new Lotus("White Lotus", 75.50, "Nelumbo Nucifera"));
    anniversaryBouquet->add(new Protea("Pink Protea", 92.00, "Queen Protea"));
    
    std::cout << " Created Anniversary Bouquet with " << anniversaryBouquet->getCount() 
              << " plants, Value: R" << anniversaryBouquet->getTotalValue() << "\n";
    
    // Create succulent arrangement
    SucculentGroup* succulentArrangement = succulentFactory.createSucculentGroup("Desktop Succulent Arrangement");
    succulentArrangement->add(new Cacti("Golden Barrel", 42.00, "Echinocactus"));
    succulentArrangement->add(new Jade("Money Plant", 35.75, "Crassula"));
    succulentArrangement->add(new Orchid("Dendrobium", 68.25, "Dendrobium"));
    
    std::cout << " Created Succulent Arrangement with " << succulentArrangement->getCount() 
              << " plants, Value: R" << succulentArrangement->getTotalValue() << "\n";
    
    // Create tree collection
    TreeGroup* treeCollection = treeFactory.createTreeGroup("Orchard Starter Pack");
    treeCollection->add(new Apple("Gala Apple", 88.00, "Malus Gala"));
    treeCollection->add(new Pine("Christmas Pine", 110.50, "Picea Abies"));
    treeCollection->add(new Jacaranda("Purple Jacaranda", 165.75, "Jacaranda Caucana"));
    
    std::cout << " Created Tree Collection with " << treeCollection->getCount() 
              << " plants, Value: R" << treeCollection->getTotalValue() << "\n";
    
    // Add groups to stock
    stockManager.addFlower(anniversaryBouquet);
    stockManager.addSucculent(succulentArrangement);
    stockManager.addTree(treeCollection);
    
    std::cout << " Added 3 composite groups to stock management\n";
}

void testStockOperations(StockManager& stockManager) {
    std::cout << "\n TEST 4: STOCK OPERATIONS & INVENTORY TRACKING\n";
    std::cout << "\n\n";
    
    // Display current stock
    stockManager.displayAllStock();
    
    // Display inventory breakdown
    stockManager.displayInventoryBreakdown();
    
    // Test removal
    if (stockManager.getFlowerStockSize() > 0) {
        std::cout << "\n Removing first flower from stock...\n";
        stockManager.removeFlower(0);
    }
    
    if (stockManager.getSucculentStockSize() > 0) {
        std::cout << " Removing first succulent from stock...\n";
        stockManager.removeSucculent(0);
    }
    
    // Display updated stock
    std::cout << "\n STOCK AFTER REMOVALS:\n";
    stockManager.displayAllStock();
    stockManager.displayInventoryBreakdown();
}

void testObserverPattern(StaffNotificationObserver& observer) {
    std::cout << "\n TEST 5: OBSERVER PATTERN - NOTIFICATION LOG\n";
    std::cout << "\n\n";
    
    observer.displayLog();
    std::cout << "Total notifications recorded: " << observer.getLogSize() << "\n";
    
    // Test notification toggle
    std::cout << "\n Testing notification toggle (disabling)...\n";
    observer.toggleNotifications(false);
    
    // Re-enable for future tests
    observer.toggleNotifications(true);
    std::cout << " Notifications re-enabled\n";
}

void testPlantTypeInheritance() {
    std::cout << "\n TEST 6: PLANT TYPE INHERITANCE HIERARCHY\n";
    std::cout << "\n\n";
    
    // Test specific plant types
    Rose testRose("Test Rose", 50.00, "Test Species");
    Cacti testCacti("Test Cacti", 30.00, "Test Species");
    Pine testPine("Test Pine", 100.00, "Test Species");
    
    std::cout << "Rose Plant Type: " << testRose.getPlantType() << "\n";
    std::cout << "Cacti Plant Type: " << testCacti.getPlantType() << "\n";
    std::cout << "Pine Plant Type: " << testPine.getPlantType() << "\n";
    
    std::cout << " Inheritance hierarchy working correctly\n";
}

//kiolin end

  //rene start
 void demonstratePlantClass() {
    printSeparator("PLANT CLASS DEMONSTRATION");

    std::cout << "\nCreating a Succulent plant..." << std::endl;
    Succulent succulent("Succulent", 50.0, "Aloe Vera", false, 8, 3); // concrete class

    std::cout << "\nPlant Information:" << std::endl;
    std::cout << "  Name: " << succulent.getName() << std::endl;
    std::cout << "  ID: " << succulent.getPlantID() << std::endl;
    std::cout << "  Fertilized: " << (succulent.isFertilized() ? "Yes" : "No") << std::endl;
    std::cout << "  Sunlight Hours: " << succulent.getExposureSunlightHours() << std::endl;
    std::cout << "  Water Level: " << succulent.getLastWaterLevel() << " (Low - succulents need less water)" << std::endl;

    std::cout << "\nUpdating plant care..." << std::endl;
    succulent.setFertilized(true);
    succulent.setExposureSunlightHours(10);
    succulent.setLastWaterLevel(5);

    std::cout << "After care update:" << std::endl;
    std::cout << "  Fertilized: " << (succulent.isFertilized() ? "Yes" : "No") << std::endl;
    std::cout << "  Sunlight Hours: " << succulent.getExposureSunlightHours() << std::endl;
    std::cout << "  Water Level: " << succulent.getLastWaterLevel() << std::endl;
}

void demonstrateStateMachine() {
    printSeparator("STATE MACHINE DEMONSTRATION");

    std::cout << "\nCreating a Flower plant in Spring season..." << std::endl;
    PlantContext* flower = new PlantContext("Rose", "Spring Rose", 15.50, "Hybrid Tea Rose"); // fixed constructor

    printPlantInfo(flower);

    // Seedling Phase
    std::cout << "\n>>> SEEDLING PHASE <<<" << std::endl;
    flower->checkReadiness();
    flower->ageState(7);
    printPlantInfo(flower);

    // Flowering Phase
    std::cout << "\n>>> FLOWERING PHASE <<<" << std::endl;
    flower->checkReadiness();
    flower->ageState(14);
    printPlantInfo(flower);

    // Mature Phase
    std::cout << "\n>>> MATURE PHASE <<<" << std::endl;
    flower->checkReadiness();
    flower->ageState(30);
    printPlantInfo(flower);

    // Ready for Sale & Sold
    std::cout << "\n>>> HARVESTING <<<" << std::endl;
    flower->harvest();
    printPlantInfo(flower);

    delete flower;
}

void demonstrateMultiplePlants() {
    printSeparator("MULTIPLE PLANTS DEMONSTRATION");

    std::cout << "\nCreating multiple plants with different characteristics..." << std::endl;

    PlantContext* flower = new PlantContext("Rose", "Summer Rose", 30.00, "Hybrid Tea Rose");
    PlantContext* tree = new PlantContext("Apple", "Winter Apple", 45.00, "Granny Smith");
    PlantContext* succulent = new PlantContext("Succulent", "Spring Aloe", 12.00, "Aloe Vera");

    std::cout << "\n--- Flower ---" << std::endl;
    printPlantInfo(flower);

    std::cout << "\n--- Tree ---" << std::endl;
    printPlantInfo(tree);

    std::cout << "\n--- Succulent ---" << std::endl;
    printPlantInfo(succulent);

    std::cout << "\nAging all plants by 5 days..." << std::endl;
    flower->ageState(5);
    tree->ageState(5);
    succulent->ageState(5);

    std::cout << "\nCurrent ages:" << std::endl;
    std::cout << "  Flower: " << flower->getAge() << " days" << std::endl;
    std::cout << "  Tree: " << tree->getAge() << " days" << std::endl;
    std::cout << "  Succulent: " << succulent->getAge() << " days" << std::endl;

    delete flower;
    delete tree;
    delete succulent;
}

void demonstrateEarlyHarvestAttempt() {
    printSeparator("EARLY HARVEST ATTEMPT DEMONSTRATION");

    std::cout << "\nCreating a Tree plant..." << std::endl;
    PlantContext* tree = new PlantContext("Apple", "Summer Apple", 18.50, "Granny Smith");

    printPlantInfo(tree);

    std::cout << "\n>>> Attempting to harvest too early <<<" << std::endl;
    tree->harvest();

    std::cout << "\nGrowing to flowering stage..." << std::endl;
    tree->ageState(5);

    std::cout << "\nTrying to harvest during flowering..." << std::endl;
    tree->harvest();

    delete tree;
}


 void interactiveMenu() {
    printSeparator("INTERACTIVE PLANT MANAGEMENT MENU");

    PlantContext* myPlant = nullptr;

    while (true) {
        std::cout << "\nSelect a plant type to create:" << std::endl;
        std::cout << "1. Flower" << std::endl;
        std::cout << "2. Tree" << std::endl;
        std::cout << "3. Succulent" << std::endl;
        std::cout << "4. Exit" << std::endl;
        std::cout << "Choice: ";
        int choice;
        std::cin >> choice;

        if (choice == 4) break;

        std::string type, name, species;
        double price;

        switch (choice) {
            case 1:
                type = "Flower";
                std::cout << "Enter name of the flower: ";
                std::cin >> name;
                std::cout << "Enter price: ";
                std::cin >> price;
                std::cout << "Enter species: ";
                std::cin >> species;
                myPlant = new PlantContext(type, name, price, species);
                break;

            case 2:
                type = "Tree";
                std::cout << "Enter name of the tree: ";
                std::cin >> name;
                std::cout << "Enter price: ";
                std::cin >> price;
                std::cout << "Enter species: ";
                std::cin >> species;
                myPlant = new PlantContext(type, name, price, species);
                break;

            case 3:
                type = "Succulent";
                std::cout << "Enter name of the succulent: ";
                std::cin >> name;
                std::cout << "Enter price: ";
                std::cin >> price;
                std::cout << "Enter species: ";
                std::cin >> species;
                myPlant = new PlantContext(type, name, price, species);
                break;

            default:
                std::cout << "Invalid choice. Try again." << std::endl;
                continue;
        }

        std::cout << "\n--- Plant Created ---" << std::endl;
        printPlantInfo(myPlant);

        std::cout << "\nWould you like to age the plant? (y/n): ";
        char resp;
        std::cin >> resp;
        if (resp == 'y' || resp == 'Y') {
            int days;
            std::cout << "Enter number of days to age: ";
            std::cin >> days;
            myPlant->ageState(days);
            std::cout << "Plant aged " << days << " days." << std::endl;
            printPlantInfo(myPlant);
        }

        std::cout << "\nWould you like to harvest the plant? (y/n): ";
        std::cin >> resp;
        if (resp == 'y' || resp == 'Y') {
            myPlant->harvest();
            printPlantInfo(myPlant);
        }

        delete myPlant;
        myPlant = nullptr;
    }

    printSeparator("EXITING INTERACTIVE MENU");
}

//rene end


//////////////////////////////////Customer_sales_Iterator+Cmd+Strategy(Sabira)\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\/

void printHeader(const std::string& title) {
    std::cout << "\n=== " << title << " ===" << std::endl;
}

void printPlantDetails(Plant* plant) {
    std::cout << std::left 
              << std::setw(15) << plant->getName()
              << "| Price: R" << std::setw(6) << plant->getPrice()
              << "| Care: " << plant->getCareInstructions() << std::endl;
}

// Simulates a customer browsing session using different iterators
void simulateCustomerBrowsing() {
    printHeader("Plant Nursery - Customer Browsing Simulation");
    
    // Create our concrete aggregate (the plant inventory)
    PlantInventory* nurseryInventory = new PlantInventory();
    
    // Stock the nursery with various plants
    Plant* rose = new Plant("Rose", false, "P001", 6, 3, 25.0);
    rose->setCareInstructions("High maintenance: Daily watering, weekly fertilizing");
    
    Plant* cactus = new Plant("Cactus", false, "P002", 8, 1, 15.0);
    cactus->setCareInstructions("Low maintenance: Monthly watering, strong sunlight");
    
    Plant* fern = new Plant("Fern", true, "P003", 4, 4, 35.0);
    fern->setCareInstructions("Medium maintenance: Weekly watering, indirect light");
    
    Plant* succulent = new Plant("Succulent", false, "P004", 6, 2, 18.0);
    succulent->setCareInstructions("Low maintenance: Occasional watering, good drainage");
    
    Plant* orchid = new Plant("Orchid", true, "P005", 5, 4, 45.0);
    orchid->setCareInstructions("High maintenance: Specific humidity and light needs");
    
    // Stock the nursery
    nurseryInventory->add(rose);
    nurseryInventory->add(cactus);
    nurseryInventory->add(fern);
    nurseryInventory->add(succulent);
    nurseryInventory->add(orchid);

    // Scenario 1: Customer browses all available plants
    printHeader("Scenario 1: Customer Views All Plants");
    std::cout << "Customer: 'Let me see what plants you have...'" << std::endl;
    
    PlantIterator browsePlants(nurseryInventory);
    std::cout << "\nShowing all available plants:" << std::endl;
    for (browsePlants.first(); !browsePlants.isDone(); browsePlants.next()) {
        printPlantDetails(browsePlants.currentItem());
    }
    
    // Scenario 2: Customer looks for low-maintenance plants
    printHeader("Scenario 2: Customer Searches for Low-Maintenance Plants");
    std::cout << "Customer: 'I'm looking for plants that are easy to care for...'" << std::endl;
    
    CareIterator easyCarePlants(nurseryInventory, "low");
    std::cout << "\nShowing low-maintenance plants:" << std::endl;
    for (easyCarePlants.first(); !easyCarePlants.isDone(); easyCarePlants.next()) {
        printPlantDetails(easyCarePlants.currentItem());
    }

    // Scenario 3: Customer has a specific budget
    printHeader("Scenario 3: Customer Browses by Price Range");
    std::cout << "Customer: 'What plants do you have between R15 and R25?'" << std::endl;
    
    PriceRangeIterator budgetPlants(nurseryInventory, 15.0, 25.0);
    std::cout << "\nShowing plants in price range R15-R25:" << std::endl;
    for (budgetPlants.first(); !budgetPlants.isDone(); budgetPlants.next()) {
        printPlantDetails(budgetPlants.currentItem());
    }

    // Scenario 4: Customer adds items to cart and reviews
    //this one is not working so well.
    printHeader("Scenario 4: Customer Shopping Cart");
    std::cout << "Customer: 'I'll take the cactus and the succulent...'" << std::endl;
    
    // Add items to cart using the main inventory's cart
    nurseryInventory->addToCart(cactus);    // Add cactus to cart
    nurseryInventory->addToCart(succulent); // Add succulent to cart
    
    CartIterator cartIterator(nurseryInventory->getCartInventory());
    std::cout << "\nReviewing shopping cart:" << std::endl;
    double total = 0.0;
    for (cartIterator.first(); !cartIterator.isDone(); cartIterator.next()) {
        Plant* plant = cartIterator.currentItem();
        printPlantDetails(plant);
        total += plant->getPrice();
    }
    std::cout << "\nCart Total: R" << total << std::endl;

    // Cleanup
    delete nurseryInventory;  // This will delete all plants in inventory
    //delete shoppingCart;      // This will delete cart contents
}

// A short, story-like scenario that demonstrates the Command pattern
// using AddToCart and RemoveFromCart via the Invoker.
void simulateCommandPatternScenario() {
    printHeader("Command Pattern Scenario: Quick Shopping Story");

    PlantInventory* nursery = new PlantInventory();

    // Create a few plants and stock the nursery
    Plant* aloe = new Plant("Aloe Vera", false, "C101", 6, 2, 20.0);
    aloe->setCareInstructions("Easy: sparse watering, bright indirect light");
    Plant* ivy = new Plant("English Ivy", false, "C102", 4, 3, 18.0);
    ivy->setCareInstructions("Medium: regular watering, indirect light");
    Plant* palm = new Plant("Parlor Palm", true, "C103", 5, 4, 40.0);
    palm->setCareInstructions("Medium: weekly watering, indirect light");

    nursery->add(aloe);
    nursery->add(ivy);
    nursery->add(palm);

    // Create commands
    AddToCart* addCmd = new AddToCart();
    RemoveFromCart* removeCmd = new RemoveFromCart();

    // Create an invoker (start with no active command)
    Invoker inv(nullptr);

    std::cout << "Narrator: A customer walks into the nursery..." << std::endl;

    // Customer decides to add Aloe Vera to cart
    std::cout << "Customer: 'I'll take that Aloe Vera.'" << std::endl;
    inv.setCommand(addCmd);
    inv.execute(aloe, nursery);

    // Customer then spots the Parlor Palm and adds it too
    std::cout << "Customer: 'And the Parlor Palm looks nice, add that too.'" << std::endl;
    inv.setCommand(addCmd);
    inv.execute(palm, nursery);

    // Show current cart contents
    std::cout << "\n-- Cart after additions --" << std::endl;
    CartIterator cartIt(nursery->getCartInventory());
    for (cartIt.first(); !cartIt.isDone(); cartIt.next()) {
        Plant* p = cartIt.currentItem();
        std::cout << " - " << p->getName() << " (R" << p->getPrice() << ")" << std::endl;
    }

    // Customer changes mind and removes the Aloe Vera
    std::cout << "\nCustomer: 'Actually, I don't need the Aloe Vera.'" << std::endl;
    inv.setCommand(removeCmd);
    inv.execute(aloe, nursery);

    // Final cart review
    std::cout << "\n-- Final cart --" << std::endl;
    CartIterator cartIt2(nursery->getCartInventory());
    double total = 0.0;
    for (cartIt2.first(); !cartIt2.isDone(); cartIt2.next()) {
        Plant* p = cartIt2.currentItem();
        std::cout << " - " << p->getName() << " (R" << p->getPrice() << ")" << std::endl;
        total += p->getPrice();
    }
    std::cout << "Cart total: R" << total << std::endl;

    // cleanup
    delete addCmd;
    delete removeCmd;
    delete nursery; // deletes owned plants
}

// Demonstrates both pricing strategies and recommendation strategies
void simulateStrategyPatternScenario() {
    printHeader("Strategy Pattern Scenario: Pricing and Recommendations");
    
    // Create strategies using unique_ptr for automatic cleanup
    std::unique_ptr<PricingStrategy> regularPrice(new RegularPrice());
    std::unique_ptr<PricingStrategy> bulkDiscount(new BulkDiscount());
    std::unique_ptr<RecommStrategy> defaultRecomm(new DefaultRecomm());
    std::unique_ptr<RecommStrategy> waterRecomm(new WaterRecomm());
    std::unique_ptr<RecommStrategy> sunlightRecomm(new SunlightRecomm());
    
    std::cout << "Welcome to our plant store! Let me help you with some recommendations and pricing options.\n" << std::endl;
    
    // Create strategy context with initial strategies (raw pointers, but owned by unique_ptr)
    StratContext context(defaultRecomm.get(), regularPrice.get());
    
    // Scenario 1: Regular price for single item
    std::cout << "\nScenario 1: Customer buying a single Rose" << std::endl;
    std::cout << "Staff: 'For a single Rose, we use our regular pricing.'" << std::endl;
    double regularPriceResult = context.executePricingStrategy(1, 25.0, "");
    std::cout << "Regular price for 1 Rose: R" << regularPriceResult << std::endl;
    
    // Scenario 2: Bulk discount for multiple items
    std::cout << "\nScenario 2: Customer buying multiple Roses (bulk)" << std::endl;
    std::cout << "Staff: 'For bulk purchases, we offer special discounts!'" << std::endl;
    context.setPricingStrategy(bulkDiscount.get());
    double bulkPriceResult = context.executePricingStrategy(10, 25.0, "BULK10");
    std::cout << "Bulk price for 10 Roses: R" << bulkPriceResult << std::endl;
    
    // Scenario 3: Get plant recommendations based on different criteria
    std::cout << "\nScenario 3: Customer seeking plant recommendations" << std::endl;
    std::cout << "Customer: 'Can you help me choose some plants?'" << std::endl;
    
    // Default recommendations
    std::cout << "\nStaff: 'Here are our general recommendations:'" << std::endl;
    context.executeRecommStrategy();
    
    // Water-based recommendations
    std::cout << "\nCustomer: 'I'm looking for low-maintenance plants that don't need much water.'" << std::endl;
    context.setRecommStrategy(waterRecomm.get());
    context.executeRecommStrategy();
    
    // Sunlight-based recommendations
    std::cout << "\nCustomer: 'What about plants that do well in shade?'" << std::endl;
    context.setRecommStrategy(sunlightRecomm.get());
    context.executeRecommStrategy();
    
    // No manual cleanup needed - unique_ptr will handle it
}
////////////////////////////////////////////Customer_sales_Iterator+cmd+strategy ends here\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\/

int main() {
  std::cout << "=== Abstract Avengers: Greenhouse Personalization & Sales ===\n";

  // 1) Prototypes (set once by the nursery at startup)
  printHeader("1) Register plant prototypes (Prototype pattern)");

  PrototypeRegistry registry;
  registry.registerPrototype("Rose",      std::unique_ptr<Item>(new PlantItem("Rose",      100.0, true)));
  registry.registerPrototype("Lily",      std::unique_ptr<Item>(new PlantItem("Lily",       80.0, true)));
  registry.registerPrototype("Succulent", std::unique_ptr<Item>(new PlantItem("Succulent",  60.0, true)));

  std::cout << "Registered prototypes: " << registry.size() << "\n";

  //2) Personalisation: build a few personalised items and one arrangement
  printHeader("2) Build personalised items (Builder + Decorator)");

  ConcreteArrangementBuilder builder;
  Director director;
  director.setBuilder(&builder);

  //a) Single "Gift Rose" — Pot + Wrap (Director recipe)
  std::unique_ptr<Item> roseProto = registry.cloneOf("Rose");
  std::unique_ptr<Item> giftRose =
      director.buildGift(*roseProto, /*potExtra*/25.0, "Red",
                                   /*wrapExtra*/15.0, "Happy Birthday!");

  std::cout << "Gift Rose: " << giftRose->describe()
            << " | Price: R" << giftRose->price() << "\n";

  //b) Single "Lily with Note" — build step-by-step (uses builder directly)
  std::unique_ptr<Item> lilyProto = registry.cloneOf("Lily");
  builder.reset();
  builder.buildBasePlant(*lilyProto);
  builder.buildPot(20.0, "White");
  builder.buildNote(5.0, "Get well soon!");
  std::unique_ptr<Item> lilyWithNote = builder.getResult();

  std::cout << "Lily w/ Note: " << lilyWithNote->describe()
            << " | Price: R" << lilyWithNote->price() << "\n";

  //c) Arrangement: two personalised succulents 
  printHeader("c) Build an Arrangement (bundle of decorated items)");

  //Component 1
  std::unique_ptr<Item> succ1 = registry.cloneOf("Succulent");
  builder.reset();
  builder.buildBasePlant(*succ1);
  builder.buildPot(10.0, "Teal");
  std::unique_ptr<Item> pottedSucc1 = builder.getResult();

  //Component 2
  std::unique_ptr<Item> succ2 = registry.cloneOf("Succulent");
  builder.reset();
  builder.buildBasePlant(*succ2);
  builder.buildPot(12.0, "Sand");
  builder.buildWrap(8.0, "Minimal wrap");  
  std::unique_ptr<Item> pottedSucc2 = builder.getResult();

  Arrangement giftSet;
  giftSet.add(std::move(pottedSucc1));
  giftSet.add(std::move(pottedSucc2));

  std::cout << "Arrangement description: " << giftSet.describe()
            << "\nArrangement total: R" << giftSet.totalPrice()
            << "  | Items: " << giftSet.count()
            << "  | Ready: " << (giftSet.readyForSale() ? "Yes" : "No")
            << "\n";

  //3) Sales flow scenarios (State pattern)
  //a) In-stock happy path: browse → cart → pay → complete
  printHeader("3.a) In-stock purchase success");

  Customer a("Rose");
  BrowsingState startBrowsing;
  SalesContext orderA(startBrowsing, a);

  // put stock for Rose/Lily
  orderA.putStock("Rose", 3);
  orderA.putStock("Lily", 2);

  std::cout << "Customer: " << a.nameFunc() << "\n";
  std::cout << "Action: selects an in-stock Rose (qty 1)\n";
  orderA.eventSelect("Rose", 1);       //Browsing -> CartOpen

  std::cout << "Action: proceeds to checkout\n";
  orderA.eventCheckout();              //CartOpen -> PendingPayment

  std::cout << "Action: payment authorize\n";
  orderA.eventAuthorize();             //PendingPayment -> PaymentAuthorized

  std::cout << "Action: commit/capture payment\n";
  orderA.eventCommit();                //PaymentAuthorized -> Completed

  std::cout << "Result: Order A complete\n";

  //b) Out-of-stock path:
  //browse → SeekingAssistance → AwaitingStock → replenished → CartOpen → assistance → back → checkout → auth → commit
  printHeader("3.b) Out-of-stock then replenished, with assistance (SeekingAssistance first)");

  Customer b("Bongani");
  SalesContext orderB(startBrowsing, b);

  std::cout << "Customer: " << b.nameFunc() << "\n";
  std::cout << "Action: selects Lily (out of stock -> SeekingAssistance)\n";
  //No stock added for Lily yet; selection should go to SeekingAssistance
  orderB.eventSelect("Lily", 1);        //Browsing -> SeekingAssistance (out-of-stock path)

  std::cout << "Action: assistance complete → AwaitingStock\n";
  orderB.eventAssistComplete();         //SeekingAssistance -> AwaitingStock

  std::cout << "Action: greenhouse replenishes stock\n";
  orderB.putStock("Lily", 5);

  std::cout << "Action: stock replenished event\n";
  orderB.eventReplenished();            //AwaitingStock -> CartOpen

  std::cout << "Action: customer requests assistance while in cart\n";
  orderB.eventAssist();                 //CartOpen -> SeekingAssistance 

  std::cout << "Action: assistance complete, back to cart\n";
  orderB.eventAssistComplete();         //SeekingAssistance -> CartOpen

  std::cout << "Action: checkout → authorize → commit\n";
  orderB.eventCheckout();               //PendingPayment
  orderB.eventAuthorize();              //PaymentAuthorized
  orderB.eventCommit();                 //Completed

  std::cout << "Result: Order B complete\n";

  //c) Cancellation while paying: browse → cart → checkout → cancel
  printHeader("3.c) Cancel during payment (user changes mind)");

  Customer c("Chandre");
  SalesContext orderC(startBrowsing, c);

  orderC.putStock("Rose", 1);
  std::cout << "Customer: " << c.nameFunc() << "\n";
  std::cout << "Action: selects an in-stock Rose (qty 1)\n";
  orderC.eventSelect("Rose", 1);        //Browsing -> CartOpen

  std::cout << "Action: proceeds to checkout\n";
  orderC.eventCheckout();               //PendingPayment

  std::cout << "Action: cancels before authorization\n";
  orderC.eventCancel();                 //Cancelled (terminal)
  std::cout << "Result: Order C cancelled\n";

  //d) Failure branches with toggles 
  //d1) Authorization failure → PaymentFailed → Retry → success → Commit
  printHeader("3.d.1) Authorization failure, then retry and succeed");

  Customer d1("Dineo");
  SalesContext orderD1(startBrowsing, d1);
  orderD1.putStock("Rose", 1);

  orderD1.eventSelect("Rose", 1);       //Browsing -> CartOpen
  orderD1.eventCheckout();              //PendingPayment

#ifdef SUPPORT_TEST_TOGGLES
  std::cout << "Action: force NEXT authorize to FAIL\n";
  orderD1.forceNextAuth(false);         
  orderD1.eventAuthorize();             //PendingPayment -> PaymentFailed

  std::cout << "Action: retry, force NEXT authorize to SUCCEED\n";
  orderD1.forceNextAuth(true);
  orderD1.eventRetry();                 //PaymentFailed -> PendingPayment
  orderD1.eventAuthorize();             //PaymentAuthorized

  std::cout << "Action: commit (default capture succeeds)\n";
  orderD1.eventCommit();                //Completed

  //d2) Capture failure → PaymentFailed → Retry → authorize + commit success
  printHeader("3.d.2) Capture failure, then retry and succeed");

  Customer d2("Dua");
  SalesContext orderD2(startBrowsing, d2);
  orderD2.putStock("Lily", 1);

  orderD2.eventSelect("Lily", 1);       //Browsing -> CartOpen
  orderD2.eventCheckout();              //PendingPayment

  std::cout << "Action: authorize succeeds\n";
  orderD2.forceNextAuth(true);
  orderD2.eventAuthorize();             //PaymentAuthorized

  std::cout << "Action: force NEXT capture to FAIL\n";
  orderD2.forceNextCapture(false);
  orderD2.eventCommit();                //PaymentAuthorized -> PaymentFailed

  std::cout << "Action: retry full payment (authorize + capture succeed)\n";
  orderD2.forceNextAuth(true);
  orderD2.forceNextCapture(true);
  orderD2.eventRetry();                 //PendingPayment
  orderD2.eventAuthorize();             //PaymentAuthorized
  orderD2.eventCommit();                //Completed

#endif


  //kiolin start
    std::cout<<"\n\n\n";
  std::cout << " PLANT NURSERY SYSTEM - COMPREHENSIVE TEST SUITE \n";
    
    try {
        // Create core system components
        StockManager stockManager;
        StaffNotificationObserver staffObserver(true);
        
        // Attach observer to stock manager
        stockManager.attach(&staffObserver);
        
        std::cout << " Initializing test sequence...\n\n";
        
        // Run comprehensive tests
        testPlantTypeInheritance();
        testIndividualPlants(stockManager);
        testFactoryProduction(stockManager);
        testCompositePattern(stockManager);
        testStockOperations(stockManager);
        testObserverPattern(staffObserver);
        
        // Final summary
        std::cout << "\n TEST SUMMARY\n";
        std::cout << "\n\n";
        std::cout << "✓ Plant Type Inheritance: Working\n";
        std::cout << "✓ Factory Pattern: Working\n";
        std::cout << "✓ Composite Pattern: Working\n";
        std::cout << "✓ Observer Pattern: Working\n";
        std::cout << "✓ Stock Management: Working\n";
        std::cout << "✓ Inventory Tracking: Working\n";
        
        std::cout << "\n FINAL TOTALS:\n";
        std::cout << "Total Stock Count: " << stockManager.getTotalStockCount() << " plants\n";
        std::cout << "Total Stock Value: R" << stockManager.getTotalStockValue() << "\n";
        std::cout << "Total Notifications: " << staffObserver.getLogSize() << "\n";
        
        std::cout << "\n ALL TESTS COMPLETED SUCCESSFULLY!\n";
        
    } catch (const std::exception& e) {
        std::cerr << " TEST FAILED: " << e.what() << std::endl;
        return 1;
    }

  //kiolin end



  //rene start

  std::cout << std::string(60, '=') << std::endl;
      std::cout << "       PLANT STATE MANAGEMENT SYSTEM - DEMO       " << std::endl;
      std::cout << std::string(60, '=') << std::endl;
      
      
      demonstratePlantClass();
      demonstrateStateMachine();
      demonstrateMultiplePlants();
      demonstrateEarlyHarvestAttempt();
      
      
      std::cout << "\n\nWould you like to enter interactive mode? (y/n): ";
      char response;
      std::cin >> response;
      
      if (response == 'y' || response == 'Y') {
          interactiveMenu();
      }
      
      printSeparator("DEMO COMPLETE");
      std::cout << "\nThank you for using the Plant State Management System!" << std::endl;
      std::cout << std::string(60, '=') << std::endl;
  //rene end

  //karishma start

  std::cout << "COMMAND DESIGN PATTERN (PLANT CARE):" << std::endl;

    //creating plants
    Plant rose("Rose", false, "P001", 6, 50, 0);
    Plant cactus("Cactus", true, "P002", 8, 20, 0);
    Plant fern("Fern", false, "P003", 3, 70, 0);

    std::cout << "Created plants:" << std::endl;
    std::cout << "- " << rose.getName() << " (ID: " << rose.getPlantID() << ")" << std::endl;
    std::cout << "- " << cactus.getName() << " (ID: " << cactus.getPlantID() << ")" << std::endl;
    std::cout << "- " << fern.getName() << " (ID: " << fern.getPlantID() << ")" << std::endl;
    std::cout << std::endl;

    //creating a gardener
    Gardener gardener("John Doe", 101, nullptr, "Ornamental Plants");

    std::cout << "Created staff(gardener): " << gardener.getName() << " (ID: " << gardener.getId() << ")" << std::endl;
    std::cout << std::endl;

    //testing the water, fertilize and prune command without queuing
    WaterCommand waterRose(&rose, 2.5);
    std::cout << "Command Description: " << waterRose.getDescription() << std::endl;
    waterRose.execute();
    std::cout << std::endl;

    FertilizeCommand fertilizeFern(&fern, "Organic");
    std::cout << "Command Description: " << fertilizeFern.getDescription() << std::endl;
    fertilizeFern.execute();
    std::cout << std::endl;

    PruneCommand pruneCactus(&cactus, 3);
    std::cout << "Command Description: " << pruneCactus.getDescription() << std::endl;
    pruneCactus.execute();
    std::cout << std::endl;

    SunlightCommand sunlightRose(&rose, 4, "direct");
    std::cout << "Command Description: " << sunlightRose.getDescription() << std::endl;
    sunlightRose.execute();
    std::cout << std::endl;

    //queuing tasks
    gardener.addTask(new WaterCommand(&rose, 1.5));
    gardener.addTask(new FertilizeCommand(&cactus, "Cactus Mix"));
    gardener.addTask(new PruneCommand(&fern, 2));
    gardener.addTask(new WaterCommand(&fern, 0.8));
    gardener.addTask(new SunlightCommand(&cactus, 6, "intense"));
    gardener.addTask(new SunlightCommand(&fern, 2, "filtered")); 

    gardener.performTasks();
    std::cout << std::endl;

    //testing if we can add tasks and clear them immediately without performing them
    gardener.addTask(new WaterCommand(&rose, 2.0));
    gardener.addTask(new FertilizeCommand(&rose, "Rose Food"));
    
    std::cout << "Tasks added to queue, now clearing..." << std::endl;
    gardener.clearTasks();
    std::cout << std::endl;

    //testing a queue with mixed tasks
    gardener.addTask(new WaterCommand(&rose, 1.0));
    gardener.addTask(new PruneCommand(&rose, 1));
    gardener.addTask(new FertilizeCommand(&rose, "All-Purpose"));
    gardener.addTask(new WaterCommand(&cactus, 0.3));
    gardener.addTask(new PruneCommand(&fern, 1));

    gardener.performTasks();
    std::cout << std::endl;

    //testing with null plant pointers
    WaterCommand waterNull(nullptr, 1.0);
    std::cout << "Testing null plant: " << waterNull.getDescription() << std::endl;
    waterNull.execute();
    std::cout << std::endl;

    //testing with 0 values
    WaterCommand waterZero(&rose, 0.0);
    std::cout << "Testing zero water: " << waterZero.getDescription() << std::endl;
    waterZero.execute();
    std::cout << std::endl;

    SunlightCommand sunlightNull(nullptr, 3, "direct");
    std::cout << "Testing null plant sunlight: " << sunlightNull.getDescription() << std::endl;
    sunlightNull.execute();
    std::cout << std::endl;

    //testinf with 0 hours
    SunlightCommand sunlightZero(&rose, 0, "direct");
    std::cout << "Testing zero hours: " << sunlightZero.getDescription() << std::endl;
    sunlightZero.execute();
    std::cout << std::endl;

    //testing with different intensity levels
    SunlightCommand sunlightLow(&cactus, 2, "low");
    SunlightCommand sunlightMedium(&fern, 4, "medium"); 
    SunlightCommand sunlightHigh(&rose, 8, "high");
    
    std::cout << "Testing different intensities:" << std::endl;
    sunlightLow.execute();
    sunlightMedium.execute();
    sunlightHigh.execute();
    std::cout << std::endl;

    std::cout << "===========================================================================================================" <<std::endl;
    std::cout << "===========================================================================================================" <<std::endl;

    std::cout << "CHAIN OF RESPONSIBILITY (PLANT LIFE CYCLES):" << std::endl;

    Plant testRose("Test Rose", false, "T001", 6, 50, 0);
    Plant testCactus("Test Cactus", true, "T002", 8, 20, 0);
    Plant testFern("Test Fern", false, "T003", 3, 70, 0);
    
    std::cout << "Created test plants for issue handling" << std::endl;
    std::cout << std::endl;

    //we create the chain of responsibility
    JuniorGardener junior;
    SeniorGardener senior;
    PlantSpecialist specialist;
    
    //we are setting up the chain
    junior.setNext(&senior);
    senior.setNext(&specialist);
    
    std::cout << "LOW Severity Issue (this should be handled by Junior)" << std::endl;
    PlantIssue lowIssue(PlantIssue::LOW, "Minor leaf discoloration", &testRose);
    junior.handleIssue(lowIssue);
    
    std::cout << "\nMEDIUM Severity Issue (this should be handled by Junior)" << std::endl;
    PlantIssue mediumIssue(PlantIssue::MEDIUM, "Moderate pest infestation", &testCactus);
    junior.handleIssue(mediumIssue);
    
    std::cout << "\nHIGH Severity Issue (this should escalate to Senior)" << std::endl;
    PlantIssue highIssue(PlantIssue::HIGH, "Severe fungal infection", &testFern);
    junior.handleIssue(highIssue);
    
    std::cout << "\nCRITICAL Severity Issue (this should escalate to Specialist)" << std::endl;
    PlantIssue criticalIssue(PlantIssue::CRITICAL, "Plant near death - emergency care needed", &testRose);
    junior.handleIssue(criticalIssue);
    
    std::cout << "\nDirect Senior Gardener Handling" << std::endl;
    PlantIssue directHighIssue(PlantIssue::HIGH, "Direct assignment to senior", &testFern);
    senior.handleIssue(directHighIssue);
    
    std::cout << "\nDirect Specialist Handling" << std::endl;
    PlantIssue directCriticalIssue(PlantIssue::CRITICAL, "Direct assignment to specialist", &testRose);
    specialist.handleIssue(directCriticalIssue);
    
    std::cout << "\nNull Plant Test" << std::endl;
    PlantIssue nullPlantIssue(PlantIssue::MEDIUM, "Issue with missing plant", nullptr);
    junior.handleIssue(nullPlantIssue);
    
    std::cout << "\nBroken Chain Test (there is no Senior Available)" << std::endl;
    //testing with an incomplete chain
    JuniorGardener juniorAlone;
    PlantIssue unhandledIssue(PlantIssue::HIGH, "No senior available - should show error", &testCactus);
    juniorAlone.handleIssue(unhandledIssue);
    
    std::cout << "\nMixed Severity Issues" << std::endl;
    
    PlantIssue mixedIssue1(PlantIssue::LOW, "Slight wilting", &testFern);
    PlantIssue mixedIssue2(PlantIssue::HIGH, "Root rot detected", &testCactus);
    PlantIssue mixedIssue3(PlantIssue::CRITICAL, "Complete system failure", &testRose);
    
    junior.handleIssue(mixedIssue1);
    junior.handleIssue(mixedIssue2);
    junior.handleIssue(mixedIssue3);
    
    std::cout << "===========================================================================================================" <<std::endl;
    std::cout << "===========================================================================================================" <<std::endl;

    std::cout << "MEDIATOR (INVENTORY):" << std::endl;

    NurseryInventoryMediator inventoryMediator;

    Gardener inventoryGardener("John Gardener", 201, &inventoryMediator, "Ornamental Plants");
    SalesAssistant salesPerson("Alice Sales", 202, &inventoryMediator, 0.05);
    Manager manager("Bob Manager", 203, &inventoryMediator, "Operations");
    DeliveryStaff deliveryPerson("Charlie Delivery", 204, &inventoryMediator, "Delivery Van");

    inventoryGardener.careForPlants();
    salesPerson.careForPlants(); 
    manager.careForPlants();
    deliveryPerson.careForPlants();

    std::cout << "\narge New Shipment Received (Gardener)" << std::endl;
    inventoryGardener.notify("new shipment", &rose, 500);
    std::cout << "Greenhouse stock after shipment: " << inventoryMediator.getGreenhouseStock(&rose) << std::endl;

    std::cout << "\nMove Plants to Sales Floor (Gardener)" << std::endl;
    inventoryGardener.notify("plant moved to sales", &rose, 300);
    std::cout << "After moving to sales - Greenhouse: " << inventoryMediator.getGreenhouseStock(&rose) << ", Sales Floor: " << inventoryMediator.getSalesFloorStock(&rose) << std::endl;

    std::cout << "\nPlant Sales to Walk-in Customers (Sales Assistant)" << std::endl;
    salesPerson.notify("plant sold", &rose, 150);
    std::cout << "After sales - Greenhouse: " << inventoryMediator.getGreenhouseStock(&rose) << ", Sales Floor: " << inventoryMediator.getSalesFloorStock(&rose) << std::endl;

    std::cout << "\nCustomer Delivery (Delivery Staff)" << std::endl;
    deliveryPerson.notify("customer delivery", &rose, 80);
    std::cout << "After delivery - Greenhouse: " << inventoryMediator.getGreenhouseStock(&rose) << ", Sales Floor: " << inventoryMediator.getSalesFloorStock(&rose) << std::endl;

    std::cout << "\nCheck Stock Levels (Manager)" << std::endl;
    manager.notify("check stock", &rose, 0);

    std::cout << "\nReturn Plants to Greenhouse (Sales Assistant)" << std::endl;
    salesPerson.notify("return to greenhouse", &rose, 20);
    std::cout << "After return - Greenhouse: " << inventoryMediator.getGreenhouseStock(&rose) << ", Sales Floor: " << inventoryMediator.getSalesFloorStock(&rose) << std::endl;

    std::cout << "\nLow Stock Alert" << std::endl;
    
    salesPerson.notify("plant sold", &rose, 60);
    std::cout << "After additional sales - Sales Floor: " << inventoryMediator.getSalesFloorStock(&rose) << std::endl;

    std::cout << "\nMultiple Plant Types" << std::endl;
    inventoryGardener.notify("new shipment", &cactus, 400);
    inventoryGardener.notify("plant moved to sales", &cactus, 250);
    salesPerson.notify("plant sold", &cactus, 120);
    deliveryPerson.notify("customer delivery", &cactus, 80);
    manager.notify("check stock", &cactus, 0);

    std::cout << "\nEdge Cases" << std::endl;
    std::cout << "Over-selling (Negative Stock Prevention)" << std::endl;
    salesPerson.notify("plant sold", &fern, 100);
    std::cout << "Fern sales floor stock after oversell attempt: " << inventoryMediator.getSalesFloorStock(&fern) << std::endl;

    std::cout << "\nMoving More Than Available" << std::endl;
    inventoryGardener.notify("plant moved to sales", &rose, 1000);
    std::cout << "Rose greenhouse stock after over-move attempt: " << inventoryMediator.getGreenhouseStock(&rose) << std::endl;

    std::cout << "\nOver-delivery" << std::endl;
    deliveryPerson.notify("customer delivery", &rose, 500);
    std::cout << "Rose sales floor stock after over-delivery attempt: " << inventoryMediator.getSalesFloorStock(&rose) << std::endl;

    std::cout << "\nNull Plant" << std::endl;
    inventoryGardener.notify("new shipment", nullptr, 50);

    std::cout << "\nUnknown Event Type" << std::endl;
    inventoryGardener.notify("unknown event", &rose, 50);

    std::cout << "\nStaff Without Mediator" << std::endl;
    Gardener loneGardener("Lone Gardener", 205, nullptr, "General Plants");
    loneGardener.notify("new shipment", &fern, 100);

    std::cout << "\nComplex Inventory Scenario" << std::endl;
    std::cout << "Simulating a complete business day:" << std::endl;

    inventoryGardener.notify("new shipment", &fern, 600);
    inventoryGardener.notify("plant moved to sales", &fern, 400);

    salesPerson.notify("plant sold", &fern, 150);
    deliveryPerson.notify("customer delivery", &fern, 100);
    salesPerson.notify("plant sold", &fern, 80);
    deliveryPerson.notify("customer delivery", &fern, 60);

    manager.notify("check stock", &fern, 0);
    salesPerson.notify("return to greenhouse", &fern, 30); // Returns from customers

    manager.notify("check stock", &fern, 0);

    std::cout << "\nGetter Methods Verification" << std::endl;
    std::cout << "Rose greenhouse stock: " << inventoryMediator.getGreenhouseStock(&rose) << std::endl;
    std::cout << "Rose sales floor stock: " << inventoryMediator.getSalesFloorStock(&rose) << std::endl;
    std::cout << "Cactus greenhouse stock: " << inventoryMediator.getGreenhouseStock(&cactus) << std::endl;
    std::cout << "Cactus sales floor stock: " << inventoryMediator.getSalesFloorStock(&cactus) << std::endl;
    std::cout << "Fern greenhouse stock: " << inventoryMediator.getGreenhouseStock(&fern) << std::endl;
    std::cout << "Fern sales floor stock: " << inventoryMediator.getSalesFloorStock(&fern) << std::endl;

    std::cout << "\nReal Customer Delivery Workflow" << std::endl;
    std::cout << "Scenario: Customer orders plants for home delivery" << std::endl;

    NurseryInventoryMediator deliveryMediator;

    Gardener deliveryGardener("Tom Gardener", 301, &deliveryMediator, "Delivery Prep");
    SalesAssistant orderProcessor("Sarah Orders", 302, &deliveryMediator, 0.03);
    DeliveryStaff homeDelivery("Mike Courier", 303, &deliveryMediator, "Refrigerated Truck");
    Manager deliveryManager("Lisa Supervisor", 304, &deliveryMediator, "Delivery Operations");

    std::cout << "\nReceiving plants in greenhouse" << std::endl;
    deliveryGardener.notify("new shipment", &rose, 1000);
    deliveryManager.notify("check stock", &rose, 0);

    std::cout << "\nCustomer places home delivery order (200 roses)" << std::endl;
    std::cout << "Order processed by sales assistant..." << std::endl;

    deliveryGardener.notify("plant moved to sales", &rose, 200);
    deliveryManager.notify("check stock", &rose, 0);

    std::cout << "\nDelivery staff picks up and delivers order" << std::endl;
    std::cout << "Mike Courier loading 200 roses into refrigerated truck..." << std::endl;
    
    homeDelivery.notify("customer delivery", &rose, 200);

    std::cout << "\nDelivery completed successfully!" << std::endl;
    std::cout << "200 roses delivered to customer's home address" << std::endl;
    std::cout << "Delivery confirmation sent to nursery" << std::endl;

    std::cout << "\nFinal inventory status" << std::endl;
    deliveryManager.notify("check stock", &rose, 0);

    std::cout << "\nMultiple Large Home Deliveries" << std::endl;
    std::cout << "Scenario: Multiple customers ordering for home delivery" << std::endl;

    std::cout << "\nCustomer 1: Office orders 300 plants for delivery" << std::endl;
    deliveryGardener.notify("plant moved to sales", &cactus, 300);
    homeDelivery.notify("customer delivery", &cactus, 300);
    std::cout << "300 cacti delivered to downtown office building" << std::endl;

    std::cout << "\nCustomer 2: Homeowner orders 150 plants" << std::endl;
    deliveryGardener.notify("plant moved to sales", &fern, 150);
    homeDelivery.notify("customer delivery", &fern, 150);
    std::cout << "150 ferns delivered to residential address" << std::endl;

    std::cout << "\nCustomer 3: Wedding planner orders 500 roses" << std::endl;
    deliveryGardener.notify("plant moved to sales", &rose, 500);
    homeDelivery.notify("customer delivery", &rose, 500);
    std::cout << "500 roses delivered to wedding venue" << std::endl;

    std::cout << "\nDelivery Operations Summary:" << std::endl;
    std::cout << "- Office delivery: 300 cacti" << std::endl;
    std::cout << "- Residential delivery: 150 ferns" << std::endl; 
    std::cout << "- Wedding delivery: 500 roses" << std::endl;
    std::cout << "- Total plants delivered: 950" << std::endl;
    std::cout << "- Delivery vehicles used: Refrigerated Truck" << std::endl;

    deliveryManager.notify("check stock", &rose, 0);
    deliveryManager.notify("check stock", &cactus, 0);
    deliveryManager.notify("check stock", &fern, 0);

    std::cout << "===========================================================================================================" <<std::endl;
    std::cout << "===========================================================================================================" <<std::endl;

    std::cout << "CHAIN OF RESPONSIBILITY (customer interaction):" << std::endl;

    JuniorStaff juniorStaff;
    SalesExpert salesExpert;
    PlantExpert plantExpert;
    Manager queryManager("Query Manager", 401, nullptr, "Customer Service");

    juniorStaff.setNext(&salesExpert);
    salesExpert.setNext(&plantExpert);
    plantExpert.setNext(&queryManager);

    std::cout << "\nGeneral Inquiry (Junior Staff should handle)" << std::endl;
    CustomerQuery generalQuery(CustomerQuery::GENERAL, "What are your opening hours?", nullptr);
    std::cout << "Customer: \"" << generalQuery.question << "\"" << std::endl;
    juniorStaff.handleQuery(generalQuery);

    std::cout << "\nBasic Pricing Question (Junior Staff should handle)" << std::endl;
    CustomerQuery pricingQuery(CustomerQuery::PRICING, "How much are your roses?", nullptr);
    std::cout << "Customer: \"" << pricingQuery.question << "\"" << std::endl;
    juniorStaff.handleQuery(pricingQuery);

    std::cout << "\nAdvanced Pricing Question (Should escalate to Sales Expert)" << std::endl;
    CustomerQuery advancedPricingQuery(CustomerQuery::PRICING, "Can I get a bulk discount for 100 plants?", nullptr);
    std::cout << "Customer: \"" << advancedPricingQuery.question << "\"" << std::endl;
    juniorStaff.handleQuery(advancedPricingQuery);

    std::cout << "\nSpecial Request (Should escalate to Sales Expert)" << std::endl;
    CustomerQuery specialRequestQuery(CustomerQuery::SPECIAL_REQUEST, "Can you deliver plants on Sunday?", nullptr);
    std::cout << "Customer: \"" << specialRequestQuery.question << "\"" << std::endl;
    juniorStaff.handleQuery(specialRequestQuery);

    std::cout << "\nPlant Care Advice (Should escalate to Plant Expert)" << std::endl;
    CustomerQuery careAdviceQuery(CustomerQuery::CARE_ADVICE, "How often should I water my cactus?", nullptr);
    std::cout << "Customer: \"" << careAdviceQuery.question << "\"" << std::endl;
    juniorStaff.handleQuery(careAdviceQuery);

    std::cout << "\nCustomer Complaint - Plant Death (Should be handled by Plant Expert)" << std::endl;
    CustomerQuery complaintQuery(CustomerQuery::COMPLAINT, "My plant died after one week", nullptr);
    std::cout << "Customer: \"" << complaintQuery.question << "\"" << std::endl;
    juniorStaff.handleQuery(complaintQuery);

    std::cout << "\nDirect Sales Expert Handling" << std::endl;
    CustomerQuery directSalesQuery(CustomerQuery::SPECIAL_REQUEST, "I need plants for a corporate event", nullptr);
    std::cout << "Customer: \"" << directSalesQuery.question << "\"" << std::endl;
    salesExpert.handleQuery(directSalesQuery);

    std::cout << "\nDirect Plant Expert Handling" << std::endl;
    CustomerQuery directPlantQuery(CustomerQuery::CARE_ADVICE, "My fern leaves are turning yellow, what should I do?", nullptr);
    std::cout << "Customer: \"" << directPlantQuery.question << "\"" << std::endl;
    plantExpert.handleQuery(directPlantQuery);

    std::cout << "\nDirect Manager Handling" << std::endl;
    CustomerQuery directManagerQuery(CustomerQuery::COMPLAINT, "I want to speak to the manager about a refund", nullptr);
    std::cout << "Customer: \"" << directManagerQuery.question << "\"" << std::endl;
    queryManager.handleQuery(directManagerQuery);

    std::cout << "\nComplex Query Chain" << std::endl;
    std::cout << "Testing multiple queries in sequence:" << std::endl;

    CustomerQuery query1(CustomerQuery::GENERAL, "What's your location?", nullptr);
    std::cout << "\nCustomer: \"" << query1.question << "\"" << std::endl;
    juniorStaff.handleQuery(query1);

    CustomerQuery query2(CustomerQuery::PRICING, "Do you offer student discount?", nullptr);
    std::cout << "\nCustomer: \"" << query2.question << "\"" << std::endl;
    juniorStaff.handleQuery(query2);

    CustomerQuery query3(CustomerQuery::CARE_ADVICE, "What soil should I use for my succulents?", nullptr);
    std::cout << "\nCustomer: \"" << query3.question << "\"" << std::endl;
    juniorStaff.handleQuery(query3);

    CustomerQuery query4(CustomerQuery::COMPLAINT, "The orchid I bought is dying", nullptr);
    std::cout << "\nCustomer: \"" << query4.question << "\"" << std::endl;
    juniorStaff.handleQuery(query4);

    std::cout << "\nBroken Chain (No Next Handler)" << std::endl;
    JuniorStaff isolatedJunior;
    CustomerQuery unhandledQuery(CustomerQuery::CARE_ADVICE, "How do I propagate my snake plant?", nullptr);
    std::cout << "Customer: \"" << unhandledQuery.question << "\"" << std::endl;
    isolatedJunior.handleQuery(unhandledQuery);

    std::cout << "\nMixed Query Types" << std::endl;
    std::cout << "Customer with multiple questions:" << std::endl;

    CustomerQuery mixed1(CustomerQuery::GENERAL, "Do you offer gift wrapping?", nullptr);
    std::cout << "\nCustomer: \"" << mixed1.question << "\"" << std::endl;
    juniorStaff.handleQuery(mixed1);

    CustomerQuery mixed2(CustomerQuery::PRICING, "How much are orchids?", nullptr);
    std::cout << "\nCustomer: \"" << mixed2.question << "\"" << std::endl;
    juniorStaff.handleQuery(mixed2);

    CustomerQuery mixed3(CustomerQuery::CARE_ADVICE, "Should I use fertilizer on my plants?", nullptr);
    std::cout << "\nCustomer: \"" << mixed3.question << "\"" << std::endl;
    juniorStaff.handleQuery(mixed3);

    std::cout << "===========================================================================================================" <<std::endl;
    std::cout << "===========================================================================================================" <<std::endl;

    std::cout << "FACTORY METHOD (for growing staff):" << std::endl;

    GardenerFactory gardenerFactory;
    SalesAssistantFactory salesAssistantFactory; 
    ManagerFactory managerFactory;
    DeliveryStaffFactory deliveryStaffFactory;

    Staff* factoryGardener = gardenerFactory.createStaff();
    Staff* factorySalesAsst = salesAssistantFactory.createStaff();
    Staff* factoryManager = managerFactory.createStaff();
    Staff* factoryDelivery = deliveryStaffFactory.createStaff();

    std::cout << "\nCreated staff using factories:" << std::endl;
    std::cout << "- " << factoryGardener->getRole() << ": " << factoryGardener->getName() << " (ID: " << factoryGardener->getId() << ")" << std::endl;
    std::cout << "- " << factorySalesAsst->getRole() << ": " << factorySalesAsst->getName() << " (ID: " << factorySalesAsst->getId() << ")" << std::endl;
    std::cout << "- " << factoryManager->getRole() << ": " << factoryManager->getName() << " (ID: " << factoryManager->getId() << ")" << std::endl;
    std::cout << "- " << factoryDelivery->getRole() << ": " << factoryDelivery->getName() << " (ID: " << factoryDelivery->getId() << ")" << std::endl;

    std::cout << "\nTesting careForPlants for each staff type" << std::endl;
    factoryGardener->careForPlants();
    factorySalesAsst->careForPlants();
    factoryManager->careForPlants();
    factoryDelivery->careForPlants();

    std::cout << "\nTesting Task Management System" << std::endl;

    Plant testPlant1("Test Plant 1", false, "TP001", 5, 60, 0);
    Plant testPlant2("Test Plant 2", true, "TP002", 7, 30, 0);

    std::cout << "\nAdding tasks to Factory Gardener:" << std::endl;
    factoryGardener->addTask(new WaterCommand(&testPlant1, 2.0));
    factoryGardener->addTask(new FertilizeCommand(&testPlant2, "Organic"));
    factoryGardener->addTask(new PruneCommand(&testPlant1, 2));

    std::cout << "\nAdding tasks to Factory Sales Assistant:" << std::endl;
    factorySalesAsst->addTask(new WaterCommand(&testPlant1, 1.5));
    factorySalesAsst->addTask(new FertilizeCommand(&testPlant1, "All-Purpose"));

    std::cout << "\nPerforming Factory Gardener Tasks" << std::endl;
    factoryGardener->performTasks();

    std::cout << "\nPerforming Factory Sales Assistant Tasks" << std::endl;
    factorySalesAsst->performTasks();

    std::cout << "\nTesting Task Clearing" << std::endl;
    factoryGardener->addTask(new WaterCommand(&testPlant2, 1.0));
    factoryGardener->addTask(new PruneCommand(&testPlant2, 1));
    std::cout << "Tasks added, now clearing without performing..." << std::endl;
    factoryGardener->clearTasks();

    std::cout << "\nTesting Sales Assistant Query Handling" << std::endl;
    SalesAssistant* salesAsstPtr = dynamic_cast<SalesAssistant*>(factorySalesAsst);
    if (salesAsstPtr) {
        CustomerQuery salesQuery1(CustomerQuery::PRICING, "What's the price of this plant?", nullptr);
        std::cout << "Customer: \"" << salesQuery1.question << "\"" << std::endl;
        salesAsstPtr->handleQuery(salesQuery1);
        
        CustomerQuery salesQuery2(CustomerQuery::GENERAL, "Where can I find potting soil?", nullptr);
        std::cout << "Customer: \"" << salesQuery2.question << "\"" << std::endl;
        salesAsstPtr->handleQuery(salesQuery2);
    }

    std::cout << "\nTesting Manager Query Handling" << std::endl;
    Manager* managerPtr = dynamic_cast<Manager*>(factoryManager);
    if (managerPtr) {
        CustomerQuery mgrQuery1(CustomerQuery::COMPLAINT, "I'm not happy with my purchase", nullptr);
        std::cout << "Customer: \"" << mgrQuery1.question << "\"" << std::endl;
        managerPtr->handleQuery(mgrQuery1);
        
        CustomerQuery mgrQuery2(CustomerQuery::SPECIAL_REQUEST, "I need a custom plant arrangement", nullptr);
        std::cout << "Customer: \"" << mgrQuery2.question << "\"" << std::endl;
        managerPtr->handleQuery(mgrQuery2);
    }

    std::cout << "\nTesting Inventory Mediator Integration" << std::endl;
    NurseryInventoryMediator testMediator;

    factoryGardener->setInventoryCoordinator(&testMediator);
    factorySalesAsst->setInventoryCoordinator(&testMediator);
    factoryManager->setInventoryCoordinator(&testMediator);
    factoryDelivery->setInventoryCoordinator(&testMediator);

    std::cout << "\nTesting staff notifications with mediator:" << std::endl;

    std::cout << "Receiving new shipment..." << std::endl;
    factoryGardener->notify("new shipment", &testPlant1, 100);
    std::cout << "   After shipment - Greenhouse: " << testMediator.getGreenhouseStock(&testPlant1) << ", Sales Floor: " << testMediator.getSalesFloorStock(&testPlant1) << std::endl;

    std::cout << "Moving plants to sales floor..." << std::endl;
    factoryGardener->notify("plant moved to sales", &testPlant1, 80);
    std::cout << "   After moving - Greenhouse: " << testMediator.getGreenhouseStock(&testPlant1) << ", Sales Floor: " << testMediator.getSalesFloorStock(&testPlant1) << std::endl;

    std::cout << "Selling plants to customers..." << std::endl;
    factorySalesAsst->notify("plant sold", &testPlant1, 50);
    std::cout << "   After sales - Greenhouse: " << testMediator.getGreenhouseStock(&testPlant1) << ", Sales Floor: " << testMediator.getSalesFloorStock(&testPlant1) << std::endl;

    std::cout << "Delivering plants to customers..." << std::endl;
    factoryDelivery->notify("customer delivery", &testPlant1, 25);
    std::cout << "   After delivery - Greenhouse: " << testMediator.getGreenhouseStock(&testPlant1) << ", Sales Floor: " << testMediator.getSalesFloorStock(&testPlant1) << std::endl;

    std::cout << "Manager checking final stock..." << std::endl;
    factoryManager->notify("check stock", &testPlant1, 0);

    std::cout << "\nTesting Factory Role Names" << std::endl;
    std::cout << "Gardener Factory produces: " << gardenerFactory.getRoleName() << std::endl;
    std::cout << "Sales Assistant Factory produces: " << salesAssistantFactory.getRoleName() << std::endl;
    std::cout << "Manager Factory produces: " << managerFactory.getRoleName() << std::endl;
    std::cout << "Delivery Staff Factory produces: " << deliveryStaffFactory.getRoleName() << std::endl;

    std::cout << "\nTesting Multiple Instances from Same Factory" << std::endl;
    Staff* factoryGardener2 = gardenerFactory.createStaff();
    Staff* factorySalesAsst2 = salesAssistantFactory.createStaff();

    std::cout << "Second Factory Gardener: " << factoryGardener2->getName() << " (ID: " << factoryGardener2->getId() << ")" << std::endl;
    std::cout << "Second Factory Sales Assistant: " << factorySalesAsst2->getName() << " (ID: " << factorySalesAsst2->getId() << ")" << std::endl;

    delete factoryGardener;
    delete factorySalesAsst;
    delete factoryManager;
    delete factoryDelivery;
    delete factoryGardener2;
    delete factorySalesAsst2;

  //karishma end

    std::cout<<"\n\n\n";
  std::cout<<"Testing Customer Browsing\n\n";
    simulateCustomerBrowsing();
    simulateCommandPatternScenario();
    simulateStrategyPatternScenario();
    return 0;
  }
