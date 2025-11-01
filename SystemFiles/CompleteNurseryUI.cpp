#include"CompleteNurseryUI.h"
///Comment out functions that are not yours and they're giving you errors
//(dont forget to comment it out in the main menu as well!!!)
CompleteNurseryUI::CompleteNurseryUI() {
    inventory = new PlantInventory();
    currentCustomer = nullptr;
    stockManager = new StockManager();
    mediator = new NurseryInventoryMediator();
    observer = new StaffNotificationObserver();
    
    strategyContext = new StratContext(new DefaultRecomm(), new RegularPrice());
    invoker = new Invoker(nullptr);
    prototypeRegistry = new PrototypeRegistry();
    arrangementBuilder = new ConcreteArrangementBuilder();
    director = new Director();
    director->setBuilder(arrangementBuilder);
    salesContext = nullptr; 
    
    // Initialize systems
    initializeNursery();
    setupStaff();
    setupQueryChain();

    //Taskeen---->register plant prototypes(I dont know if this is still necessary,since we'll be using Greenhouse
    //{i took this form main.cpp so its probably not intergrated properly})
    prototypeRegistry->registerPrototype("Rose", 
        std::unique_ptr<Item>(new PlantItem("Rose", 45.99, true)));
    prototypeRegistry->registerPrototype("Cactus", 
        std::unique_ptr<Item>(new PlantItem("Cactus", 32.75, true)));
    prototypeRegistry->registerPrototype("Jade", 
        std::unique_ptr<Item>(new PlantItem("Jade", 28.50, true)));
    prototypeRegistry->registerPrototype("Fern", 
        std::unique_ptr<Item>(new PlantItem("Fern", 35.0, true)));
    
    //Attach observer to stock manager
    stockManager->attach(observer);
    
}

CompleteNurseryUI::~CompleteNurseryUI() {
    delete inventory;
    if (currentCustomer) delete currentCustomer;
    delete stockManager;
    delete mediator;
    delete observer;
    delete strategyContext;
    delete invoker;
    delete customerQueryChain;
    
    for (auto staff : nurseryStaff) delete staff;
    for (auto plant : growingPlants) delete plant;
    
    delete juniorGardener;
    delete seniorGardener;
    delete plantSpecialist;

    delete prototypeRegistry;
    delete arrangementBuilder;
    delete director;
    if (salesContext) delete salesContext;
}

void CompleteNurseryUI::initializeNursery() {
    // Stock initial plants
    Plant* rose = new Rose("Red Rose", 45.99);
    rose->setCareInstructions("High maintenance: Daily watering, weekly fertilizing");
    
    Plant* cactus = new Cacti("Golden Barrel Cactus", 32.75);
    cactus->setCareInstructions("Low maintenance: Monthly watering, strong sunlight");
    
    Plant* jade = new Jade("Jade Plant", 28.50);
    jade->setCareInstructions("Low maintenance: Occasional watering");
    
    Plant* fern = new Succulent("Boston Fern", 35.0, "Fern");
    fern->setCareInstructions("Medium maintenance: Weekly watering, indirect light");
    
    inventory->add(rose);
    inventory->add(cactus);
    inventory->add(jade);
    inventory->add(fern);
    
    // Add to stock manager
    stockManager->addFlower(new Rose("Stock Rose", 45.99, "Hybrid Tea"));
    stockManager->addSucculent(new Cacti("Stock Cactus", 32.75, "Barrel"));
    stockManager->addSucculent(new Jade("Stock Jade", 28.50, "Crassula"));
}

void CompleteNurseryUI::setupStaff() {
    //staff members using factories
    GardenerFactory gardenerFactory;
    SalesAssistantFactory salesFactory;
    ManagerFactory managerFactory;
    
    nurseryStaff.push_back(gardenerFactory.createStaff());
    nurseryStaff.push_back(salesFactory.createStaff());
    nurseryStaff.push_back(managerFactory.createStaff());
    
    // Set mediator for all staff
    for (auto staff : nurseryStaff) {
        staff->setInventoryCoordinator(mediator);
    }
    
    // Create plant issue chain
    juniorGardener = new JuniorGardener();
    seniorGardener = new SeniorGardener();
    plantSpecialist = new PlantSpecialist();
    
    juniorGardener->setNext(seniorGardener);
    seniorGardener->setNext(plantSpecialist);
}

void CompleteNurseryUI::setupQueryChain() {
    customerQueryChain = new JuniorStaff();
    CustomerQueryHandler* salesExpert = new SalesExpert();
    CustomerQueryHandler* plantExpert = new PlantExpert();
    
    customerQueryChain->setNext(salesExpert);
    salesExpert->setNext(plantExpert);
}

// UI Helper functions
void CompleteNurseryUI::clearScreen() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

void CompleteNurseryUI::pressEnter() {
    std::cout << "\n Press Enter to continue...";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cin.get();
}

//this function stops the user from entering the wrong input which would break our system
int CompleteNurseryUI::getValidatedInput(int min, int max) {
    int choice;
    while (true) {
        if (std::cin >> choice) {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            if (choice >= min && choice <= max) {
                return choice;
            }
        } else {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
        std::cout << " Invalid! Enter " << min << "-" << max << ": ";
    }
}

void CompleteNurseryUI::printHeader(const std::string& title) {
    std::cout << "\n";
    std::cout << "╔════════════════════════════════════════════════════════╗\n";
    std::cout << "║  " << std::left << std::setw(52) << title << "  ║\n";
    std::cout << "╚════════════════════════════════════════════════════════╝\n";
}

void CompleteNurseryUI::printSubHeader(const std::string& title) {
    std::cout << "\n┌────────────────────────────────────────┐\n";
    std::cout << "│  " << std::left << std::setw(36) << title << "  │\n";
    std::cout << "└────────────────────────────────────────┘\n";
}

void CompleteNurseryUI::printSuccess(const std::string& msg) {
    std::cout << "\n ✓ SUCCESS: " << msg << "\n";
}

void CompleteNurseryUI::printError(const std::string& msg) {
    std::cout << "\n ✗ ERROR: " << msg << "\n";
}

void CompleteNurseryUI::printBox(const std::string& content) {
    std::cout << "┌─────────────────────────────────────────┐\n";
    std::cout << "│ " << std::left << std::setw(40) << content << "│\n";
    std::cout << "└─────────────────────────────────────────┘\n";
}

// Main Menu
void CompleteNurseryUI::showMainMenu() {
    while (true) {
        clearScreen();
        printHeader("🌿 PLANT NURSERY MANAGEMENT SYSTEM 🌿");
        
        std::cout <<"\n┌─── MAIN MENU ───────────────────────────────────┐\n";
        std::cout << "│                                                   │\n";
        std::cout << "│  👤 1. Customer      (Browse & Shop)             │\n";
        std::cout << "│  👨‍🌾 2. Staff Area (Plant Care & Operations)      │\n";
        std::cout << "│  🏡 3. Greenhouse (Stock & Lifecycle)            │\n";
        std::cout << "│  🎯 4. Pattern Demonstrations                    │\n";
        std::cout << "│  📊 5. System Status                             │\n";
        std::cout << "|  💲 6. Payment                                   |\n";
        std::cout << "│  🚪 0. Exit System                               │\n";
        std::cout << "│                                                  │\n";
        std::cout << "└──────────────────────────────────────────────────┘\n";
        
        std::cout << "\n Enter choice: ";
        int choice = getValidatedInput(0, 5);
        
        if (choice == 0) {
            std::cout << "\n Thank you for using Abstract Avengers' Nursery System😊!\n";
            break;
        }
        
        switch (choice) {
            case 1: showCustomerMenu(); break;
            case 2: {
                //showStaffMenu()
                std::cout<<"StaffMenu still in progress\n";
                    break;
                }
            case 3: 
            {
                //showGreenhouseMenu();
                std::cout<<"GreenhouseMenu still in progress\n";
                break;}

            case 4: {
                //showPatternDemoMenu(); 
                std::cout<<"PatternDemo in progress (not really needed right now it'll come later, this would just make demonstrating our system easier)\n";
                break;
            }
            case 5: {
                clearScreen();
                printHeader("SYSTEM STATUS");
                std::cout << "\n Sales Floor Plants: " << inventory->size() << "\n";
                std::cout << " Stock - Flowers: " << stockManager->getFlowerStockSize() << "\n";
                std::cout << " Stock - Succulents: " << stockManager->getSucculentStockSize() << "\n";
                std::cout << " Stock - Trees: " << stockManager->getTreeStockSize() << "\n";
                std::cout << " Growing Plants: " << growingPlants.size() << "\n";
                std::cout << " Staff Members: " << nurseryStaff.size() << "\n";
                std::cout << " Notifications: " << observer->getLogSize() << "\n";
                pressEnter();
                break;
            }
            case 6:{
                //showPaymentMenu();
                std::cout <<"Still in progress!!\n";
                break;
            }
        }
    }
}

// Customer Menu
void CompleteNurseryUI::showCustomerMenu() {
    while (true) {
        clearScreen();
        printHeader("👤 CUSTOMER AREA");
        
        if (!currentCustomer) {
            std::cout << "\n Welcome! Please sign in:\n\n";
            std::cout << " 1. Sign in as Customer\n";
            std::cout << " 0. Back to Main Menu\n\n";
            std::cout << " Enter choice: ";
            int choice = getValidatedInput(0, 1);
            
            if (choice == 0) break;
            
            if (choice == 1) {
                std::string name;
                std::cout << "\n Enter your name: ";
                std::getline(std::cin, name);
                currentCustomer = new Customer(name);
                printSuccess("Welcome, " + name + "!");
                pressEnter();
                continue;
            }
        } else {
            std::cout << "\n Customer: " << currentCustomer->nameFunc() << "\n";
            
            printSubHeader("SHOPPING OPTIONS");
            //Sabira's part->backend for salesFloor
            std::cout << " 1. 🔍 Browse Plants \n";
            std::cout << " 2. 🛒 Shopping Cart \n";
            std::cout << " 3. 💡 Get Recommendations \n";
            std::cout << " 4. 💰 Check Prices \n";
            ///karishmas->staff pat
            std::cout << " 5. ❓ Ask for Help \n";
            std::cout << " 6. 👤 Change Customer\n";
            //
            std::cout << " 0. Back to Main Menu\n\n";
            
            std::cout << " Enter choice: ";
            int choice = getValidatedInput(0, 6);
            
            if (choice == 0) break;
            
            switch (choice) {
                case 1: showBrowsingMenu(); break;
                case 2: showCartMenu(); break;
                case 3: showRecommendationMenu(); break;
                case 4: showPricingMenu(); break;
                case 5: showHelpMenu(); break;
                case 6:
                    delete currentCustomer;
                    currentCustomer = nullptr;
                    printSuccess("Customer signed out");
                    pressEnter();
                    break;
            }
        }
    }
}

// Browsing Menu (Iterator Pattern)
void CompleteNurseryUI::showBrowsingMenu() {
    while (true) {
        clearScreen();
        printHeader("🔍 BROWSE PLANTS");
        
        std::cout << "\n 1. View All Plants\n";
        std::cout << " 2. Filter by Price Range\n";
        std::cout << " 3. Filter by Care Level\n";
        std::cout << " 4. View Decoration Options\n";
        std::cout << " 0. Back\n\n";
        
        std::cout << " Enter choice: ";
        int choice = getValidatedInput(0, 4);
        
        if (choice == 0) break;
        
        switch (choice) {
            case 1: {
                clearScreen();
                printSubHeader("ALL AVAILABLE PLANTS");
                PlantIterator it(inventory);
                int num = 1;
                std::cout << "\n";
                for (it.first(); !it.isDone(); it.next()) {
                    Plant* p = it.currentItem();
                    std::cout << " " << num++ << ". " << std::setw(20) << p->getName()
                             << " | R" << std::setw(6) << p->getPrice() << " | "
                             << p->getCareInstructions() << "\n";
                }
                pressEnter();
                break;
            }
            case 2: {
                double min, max;
                std::cout << "\n Min price (R): ";
                while (!(std::cin >> min)) {
                    std::cin.clear();
                    std::cin.ignore(10000, '\n');
                    std::cout << " Invalid! Min price: R";
                }
                std::cout << " Max price (R): ";
                while (!(std::cin >> max)) {
                    std::cin.clear();
                    std::cin.ignore(10000, '\n');
                    std::cout << " Invalid! Max price: R";
                }
                std::cin.ignore(10000, '\n');
                
                clearScreen();
                printSubHeader("PLANTS IN PRICE RANGE");
                PriceRangeIterator it(inventory, min, max);
                int num = 1;
                std::cout << "\n";
                for (it.first(); !it.isDone(); it.next()) {
                    Plant* p = it.currentItem();
                    std::cout << " " << num++ << ". " << p->getName()
                             << " - R" << p->getPrice() << "\n";
                }
                pressEnter();
                break;
            }
            case 3: {
                std::string level;
                std::cout << "\n Care level (low/medium/high): ";
                std::getline(std::cin, level);
                
                clearScreen();
                printSubHeader("PLANTS - " + level + " MAINTENANCE");
                CareIterator it(inventory, level);
                int num = 1;
                std::cout << "\n";
                for (it.first(); !it.isDone(); it.next()) {
                    Plant* p = it.currentItem();
                    std::cout << " " << num++ << ". " << p->getName()
                             << " - R" << p->getPrice() << "\n";
                }
                pressEnter();
                break;
            }
            case 4: {
                clearScreen();
                printSubHeader("DECORATION OPTIONS");
                inventory->displayAllOptions();
                pressEnter();
                break;
            }
        }
    }
}

// Cart Menu (Command Pattern)
void CompleteNurseryUI::showCartMenu() {
    while (true) {
        clearScreen();
        printHeader("🛒 SHOPPING CART");
        
        displayCart();
        
        std::cout << "\n 1. Add Plant to Cart\n";
        std::cout << " 2. Remove from Cart\n";
        std::cout << " 3. Checkout\n";
        std::cout << " 0. Back\n\n";
        
        std::cout << " Enter choice: ";
        int choice = getValidatedInput(0, 3);
        
        if (choice == 0) break;
        
        switch (choice) {
            case 1: {
                clearScreen();
                printSubHeader("SELECT PLANT TO ADD");
                
                PlantIterator it(inventory);
                std::vector<Plant*> plants;
                int num = 1;
                
                std::cout << "\n";
                for (it.first(); !it.isDone(); it.next()) {
                    plants.push_back(it.currentItem());
                    std::cout << " " << num++ << ". " << it.currentItem()->getName()
                             << " - R" << it.currentItem()->getPrice() << "\n";
                }
                
                if (plants.empty()) {
                    printError("No plants available!");
                    pressEnter();
                    break;
                }
                
                std::cout << "\n Select plant (0 to cancel): ";
                int sel = getValidatedInput(0, plants.size());
                
                if (sel > 0) {
                    CustomerCommand* cmd = new AddToCart();
                    invoker->setCommand(cmd);
                    cmd->execute(plants[sel - 1], currentCustomer->getCart());
                    printSuccess(plants[sel - 1]->getName() + " added to cart!");
                }
                pressEnter();
                break;
            }
            case 2: {
                CartIterator cartIt(currentCustomer->getCart());
                std::vector<Plant*> cartPlants;
                
                for (cartIt.first(); !cartIt.isDone(); cartIt.next()) {
                    cartPlants.push_back(cartIt.currentItem());
                }
                
                if (cartPlants.empty()) {
                    printError("Cart is empty!");
                    pressEnter();
                    break;
                }
                
                std::cout << "\n Select item to remove (0 to cancel): ";
                int sel = getValidatedInput(0, cartPlants.size());
                
                if (sel > 0) {
                    CustomerCommand* cmd = new RemoveFromCart();
                    invoker->setCommand(cmd);
                    cmd->execute(cartPlants[sel - 1], currentCustomer->getCart());
                    printSuccess("Item removed!");
                }
                pressEnter();
                break;
            }
            case 3: {
                CartIterator cartIt(currentCustomer->getCart());
                int count = 0;
                for (cartIt.first(); !cartIt.isDone(); cartIt.next()) count++;
                
                if (count == 0) {
                    printError("Cart is empty!");
                    pressEnter();
                    break;
                }
                
                double total = calculateCartTotal();
                
                std::cout << "\n╔═══ CHECKOUT ═══╗\n";
                std::cout << " Items: " << count << "\n";
                std::cout << " Total: R" << total << "\n";
                std::cout << "╚════════════════╝\n";
                
                std::cout << "\n Confirm purchase? (1=Yes, 0=No): ";
                int confirm = getValidatedInput(0, 1);
                
                if (confirm == 1) {
                    //currentCustomer->clearCart();
                    std::cout<<"///proceed to case 6->payments\n";
                    printSuccess("Purchase complete! Thank you!");
                } else {
                    std::cout << "\n Purchase cancelled.\n";
                }
                pressEnter();
                break;
            }
        }
    }
}

void CompleteNurseryUI::displayCart() {
    CartIterator cartIt(currentCustomer->getCart());
    bool isEmpty = true;
    double total = 0.0;
    int num = 1;
    
    std::cout << "\n┌─── YOUR CART ────────────────────────┐\n";
    for (cartIt.first(); !cartIt.isDone(); cartIt.next()) {
        isEmpty = false;
        Plant* p = cartIt.currentItem();
        std::cout << "│ " << num++ << ". " << std::setw(20) << p->getName()
                 << " R" << std::setw(6) << p->getPrice() << " │\n";
        total += p->getPrice();
    }
    
    if (isEmpty) {
        std::cout << "│  Cart is empty                       │\n";
    } else {
        std::cout << "├──────────────────────────────────────┤\n";
        std::cout << "│  Total: R" << std::setw(26) << total << " │\n";
    }
    std::cout << "└──────────────────────────────────────┘\n";
}

double CompleteNurseryUI::calculateCartTotal() {
    CartIterator cartIt(currentCustomer->getCart());
    double total = 0.0;
    for (cartIt.first(); !cartIt.isDone(); cartIt.next()) {
        total += cartIt.currentItem()->getPrice();
    }
    return total;
}

// Recommendation Menu (Strategy Pattern)
void CompleteNurseryUI::showRecommendationMenu() {
    clearScreen();
    printHeader("💡 PLANT RECOMMENDATIONS");
    
    std::cout << "\n 1. General Recommendations\n";
    std::cout << " 2. Low-Water Plants\n";
    std::cout << " 3. Sunlight-Loving Plants\n";
    std::cout << " 0. Back\n\n";
    
    std::cout << " Enter choice: ";
    int choice = getValidatedInput(0, 3);
    
    if (choice == 0) return;
    
    std::cout << "\n";
    switch (choice) {
        case 1:
            strategyContext->setRecommStrategy(new DefaultRecomm());
            strategyContext->executeRecommStrategy();
            break;
        case 2:
            strategyContext->setRecommStrategy(new WaterRecomm());
            strategyContext->executeRecommStrategy();
            break;
        case 3:
            strategyContext->setRecommStrategy(new SunlightRecomm());
            strategyContext->executeRecommStrategy();
            break;
    }
    pressEnter();
}

// Pricing Menu (Sabira's Strategy Pattern)
void CompleteNurseryUI::showPricingMenu() {
    clearScreen();
    printHeader("💰 PRICING OPTIONS");
    
    double basePrice = 25.0;
    
    std::cout << "\n 1. Regular Pricing\n";
    std::cout << " 2. Bulk Discount (10+ items)\n";
    std::cout << " 0. Back\n\n";
    
    std::cout << " Enter choice: ";
    int choice = getValidatedInput(0, 2);
    
    if (choice == 0) return;
    
    std::cout << "\n";
    switch (choice) {
        case 1:
            strategyContext->setPricingStrategy(new RegularPrice());
            std::cout << " Regular price: R" << strategyContext->executePricingStrategy(1, basePrice, "") << "\n";
            break;
        case 2:
            strategyContext->setPricingStrategy(new BulkDiscount());
            std::cout << " Bulk price (10 items): R" << strategyContext->executePricingStrategy(10, basePrice, "BULK10") << "\n";
            break;
    }
    pressEnter();
}

// Help Menu (Chain of Responsibility)
void CompleteNurseryUI::showHelpMenu() {
    clearScreen();
    printHeader("❓ CUSTOMER HELP");
    
    std::cout << "\n 1. General Question\n";
    std::cout << " 2. Pricing Question\n";
    std::cout << " 3. Plant Care Advice\n";
    std::cout << " 4. Special Request\n";
    std::cout << " 0. Back\n\n";
    
    std::cout << " Enter choice: ";
    int choice = getValidatedInput(0, 4);
    
    if (choice == 0) return;
    
    std::string question;
    std::cout << "\n Your question: ";
    std::getline(std::cin, question);
    
    CustomerQuery::Type type;
    switch (choice) {
        case 1: type = CustomerQuery::GENERAL; break;
        case 2: type = CustomerQuery::PRICING; break;
        case 3: type = CustomerQuery::CARE_ADVICE; break;
        case 4: type = CustomerQuery::SPECIAL_REQUEST; break;
        default: return;
    }
    
    std::cout << "\n";
    CustomerQuery query(type, question, currentCustomer);
    customerQueryChain->handleQuery(query);
    pressEnter();
}

// Staff Menu (Karishma's work)
void CompleteNurseryUI::showStaffMenu() {
    while (true) {
        clearScreen();
        printHeader("👨‍🌾 STAFF OPERATIONS");
        ///remeber to take out the brackets that show your pattern--> its just to guide you
        std::cout << "\n 1. 💧 Plant Care Tasks (Command)\n";
        std::cout << " 2. 📋 Manage Staff Tasks\n";
        std::cout << " 3. 📦 Inventory Coordination (Mediator)\n";
        std::cout << " 4. 🚨 Handle Plant Issues (Chain of Responsibility)\n";
        std::cout << " 5. 👥 View Staff List\n";
        std::cout << " 0. Back\n\n";
        
        std::cout << " Enter choice: ";
        int choice = getValidatedInput(0, 5);
        
        if (choice == 0) break;
        
        switch (choice) {
            case 1: showPlantCareMenu(); break;
            case 2: showStaffTasksMenu(); break;
            case 3: showInventoryMediatorMenu(); break;
            case 4: showPlantIssuesMenu(); break;
            case 5: {
                clearScreen();
                printSubHeader("NURSERY STAFF");
                std::cout << "\n";
                for (size_t i = 0; i < nurseryStaff.size(); i++) {
                    std::cout << " " << (i + 1) << ". " << nurseryStaff[i]->getName()
                             << " - " << nurseryStaff[i]->getRole() << "\n";
                }
                pressEnter();
                break;
            }
        }
    }
}




// // Plant Care Menu (Karishma's Command Pattern)
void CompleteNurseryUI::showPlantCareMenu() {
    clearScreen();
    printHeader("💧 PLANT CARE TASKS");
    
    // Get a plant from inventory
    PlantIterator it(inventory);
    std::vector<Plant*> plants;
    int num = 1;
    
    std::cout << "\n Select plant to care for:\n";
    for (it.first(); !it.isDone(); it.next()) {
        plants.push_back(it.currentItem());
        std::cout << " " << num++ << ". " << it.currentItem()->getName() << "\n";
    }
    
    if (plants.empty()) {
        printError("No plants available!");
        pressEnter();
        return;
    }
    
    std::cout << "\n Select plant (0 to cancel): ";
    int plantSel = getValidatedInput(0, plants.size());
    if (plantSel == 0) return;
    
    Plant* selectedPlant = plants[plantSel - 1];
    
    std::cout << "\n Care action:\n";
    std::cout << " 1. Water\n";
    std::cout << " 2. Fertilize\n";
    std::cout << " 3. Prune\n";
    std::cout << " 4. Adjust Sunlight\n";
    std::cout << " 0. Cancel\n\n";
    
    std::cout << " Enter choice: ";
    int action = getValidatedInput(0, 4);
    
    if (action == 0) return;
    
    std::cout << "\n";
    switch (action) {
        case 1: {
            double amount;
            std::cout << " Water amount (liters): ";
            std::cin >> amount;
            WaterCommand waterCmd(selectedPlant, amount);
            std::cout << "\n " << waterCmd.getDescription() << "\n";
            waterCmd.execute();
            printSuccess("Plant watered!");
            break;
        }
        case 2: {
            std::string type;
            std::cout << " Fertilizer type: ";
            std::cin.ignore();
            std::getline(std::cin, type);
            FertilizeCommand fertilizeCmd(selectedPlant, type);
            std::cout << "\n " << fertilizeCmd.getDescription() << "\n";
            fertilizeCmd.execute();
            printSuccess("Plant fertilized!");
            break;
        }
        case 3: {
            int branches;
            std::cout << " Number of branches to prune: ";
            std::cin >> branches;
            PruneCommand pruneCmd(selectedPlant, branches);
            std::cout << "\n " << pruneCmd.getDescription() << "\n";
            pruneCmd.execute();
            printSuccess("Plant pruned!");
            break;
        }
        case 4: {
            int hours;
            std::string intensity;
            std::cout << " Hours of sunlight: ";
            std::cin >> hours;
            std::cout << " Intensity (low/medium/high): ";
            std::cin >> intensity;
            SunlightCommand sunCmd(selectedPlant, hours, intensity);
            std::cout << "\n " << sunCmd.getDescription() << "\n";
            sunCmd.execute();
            printSuccess("Sunlight adjusted!");
            break;
        }
    }
    pressEnter();
}

// //Staff Tasks Menu
void CompleteNurseryUI::showStaffTasksMenu() {
    clearScreen();
    printHeader("📋 STAFF TASK MANAGEMENT");
    
    std::cout << "\n Select staff member:\n";
    for (size_t i = 0; i < nurseryStaff.size(); i++) {
        std::cout << " " << (i + 1) << ". " << nurseryStaff[i]->getName()
                 << " (" << nurseryStaff[i]->getRole() << ")\n";
    }
    std::cout << " 0. Cancel\n\n";
    
    std::cout << " Enter choice: ";
    int staffSel = getValidatedInput(0, nurseryStaff.size());
    if (staffSel == 0) return;
    
    Staff* selectedStaff = nurseryStaff[staffSel - 1];
    
    std::cout << "\n 1. Add Task\n";
    std::cout << " 2. Perform All Tasks\n";
    std::cout << " 3. Clear Tasks\n";
    std::cout << " 0. Back\n\n";
    
    std::cout << " Enter choice: ";
    int choice = getValidatedInput(0, 3);
    
    switch (choice) {
        case 1: {
            PlantIterator it(inventory);
            std::vector<Plant*> plants;
            int num = 1;
            
            std::cout << "\n Select plant for task:\n";
            for (it.first(); !it.isDone(); it.next()) {
                plants.push_back(it.currentItem());
                std::cout << " " << num++ << ". " << it.currentItem()->getName() << "\n";
            }
            
            if (plants.empty()) break;
            
            std::cout << "\n Plant: ";
            int plantSel = getValidatedInput(1, plants.size());
            Plant* plant = plants[plantSel - 1];
            
            std::cout << "\n Task type:\n";
            std::cout << " 1. Water\n 2. Fertilize\n 3. Prune\n";
            int taskType = getValidatedInput(1, 3);
            
            if (taskType == 1) {
                selectedStaff->addTask(new WaterCommand(plant, 1.5));
            } else if (taskType == 2) {
                selectedStaff->addTask(new FertilizeCommand(plant, "General"));
            } else {
                selectedStaff->addTask(new PruneCommand(plant, 1));
            }
            
            printSuccess("Task added to queue!");
            break;
        }
        case 2:
            std::cout << "\n";
            selectedStaff->performTasks();
            printSuccess("All tasks completed!");
            break;
        case 3:
            selectedStaff->clearTasks();
            printSuccess("All tasks cleared!");
            break;
    }
    pressEnter();
}

//Inventory Mediator Menu (Karishma's Mediator Pattern)
///PlantInventory(SalesFloor inventory for customers)
void CompleteNurseryUI::showInventoryMediatorMenu() {
    clearScreen();
    printHeader("📦 INVENTORY COORDINATION");
    
    PlantIterator it(inventory);
    std::vector<Plant*> plants;
    int num = 1;
    
    std::cout << "\n Select plant:\n";
    for (it.first(); !it.isDone(); it.next()) {
        plants.push_back(it.currentItem());
        std::cout << " " << num++ << ". " << it.currentItem()->getName() << "\n";
    }
    
    if (plants.empty()) {
        printError("No plants available!");
        pressEnter();
        return;
    }
    
    std::cout << "\n Select plant (0 to cancel): ";
    int plantSel = getValidatedInput(0, plants.size());
    if (plantSel == 0) return;
    
    Plant* plant = plants[plantSel - 1];
    
    std::cout << "\n Current Stock:\n";
    std::cout << " Greenhouse: " << mediator->getGreenhouseStock(plant) << "\n";
    std::cout << " Sales Floor: " << mediator->getSalesFloorStock(plant) << "\n\n";
    
    std::cout << " 1. Receive Shipment (to Greenhouse)\n";
    std::cout << " 2. Move to Sales Floor\n";
    std::cout << " 3. Record Sale\n";
    std::cout << " 4. Check Stock Status\n";
    std::cout << " 0. Back\n\n";
    
    std::cout << " Enter choice: ";
    int choice = getValidatedInput(0, 4);
    
    if (choice == 0) return;
    
    int quantity = 0;
    if (choice != 4) {
        std::cout << "\n Quantity: ";
        std::cin >> quantity;
        std::cin.ignore();
    }
    
    std::cout << "\n";
    switch (choice) {
        case 1:
            nurseryStaff[0]->notify("new shipment", plant, quantity);
            printSuccess("Shipment received!");
            break;
        case 2:
            nurseryStaff[0]->notify("plant moved to sales", plant, quantity);
            printSuccess("Plants moved to sales floor!");
            break;
        case 3:
            nurseryStaff[1]->notify("plant sold", plant, quantity);
            printSuccess("Sale recorded!");
            break;
        case 4:
            nurseryStaff[2]->notify("check stock", plant, 0);
            break;
    }
    
    std::cout << "\n Updated Stock:\n";
    std::cout << " Greenhouse: " << mediator->getGreenhouseStock(plant) << "\n";
    std::cout << " Sales Floor: " << mediator->getSalesFloorStock(plant) << "\n";
    
    pressEnter();
}

// // Plant Issues Menu (Karishma's Chain of Responsibility)
void CompleteNurseryUI::showPlantIssuesMenu() {
    clearScreen();
    printHeader("🚨 PLANT ISSUE HANDLING");
    
    PlantIterator it(inventory);
    std::vector<Plant*> plants;
    int num = 1;
    
    std::cout << "\n Select affected plant:\n";
    for (it.first(); !it.isDone(); it.next()) {
        plants.push_back(it.currentItem());
        std::cout << " " << num++ << ". " << it.currentItem()->getName() << "\n";
    }
    
    if (plants.empty()) {
        printError("No plants available!");
        pressEnter();
        return;
    }
    
    std::cout << "\n Select plant (0 to cancel): ";
    int plantSel = getValidatedInput(0, plants.size());
    if (plantSel == 0) return;
    
    Plant* plant = plants[plantSel - 1];
    
    std::cout << "\n Issue severity:\n";
    std::cout << " 1. LOW (Minor discoloration)\n";
    std::cout << " 2. MEDIUM (Pest infestation)\n";
    std::cout << " 3. HIGH (Fungal infection)\n";
    std::cout << " 4. CRITICAL (Near death)\n";
    std::cout << " 0. Cancel\n\n";
    
    std::cout << " Enter choice: ";
    int severity = getValidatedInput(0, 4);
    if (severity == 0) return;
    
    std::string description;
    std::cout << "\n Describe issue: ";
    std::getline(std::cin, description);
    
    PlantIssue::Severity sev;
    switch (severity) {
        case 1: sev = PlantIssue::LOW; break;
        case 2: sev = PlantIssue::MEDIUM; break;
        case 3: sev = PlantIssue::HIGH; break;
        case 4: sev = PlantIssue::CRITICAL; break;
        default: return;
    }
    
    std::cout << "\n";
    PlantIssue issue(sev, description, plant);
    juniorGardener->handleIssue(issue);
    
    pressEnter();
}

// Greenhouse Menu->Comment this out when you're done fixing your part of the gui
void CompleteNurseryUI::showGreenhouseMenu() {
    while (true) {
        clearScreen();
        printHeader("🏡 GREENHOUSE OPERATIONS");
        
        std::cout << "\n 1. 📦 Stock Management (Factory/Composite)\n";
        std::cout << " 2. 🌱 Plant Lifecycle (State Pattern)\n";
        std::cout << " 3. 🏭 Factory Production Demo\n";
        std::cout << " 4. 📊 Inventory Status\n";
        std::cout << " 5. 🔔 Notifications (Observer)\n";
        std::cout << " 0. Back\n\n";
        
        std::cout << " Enter choice: ";
        int choice = getValidatedInput(0, 5);
        
        if (choice == 0) break;
        
        switch (choice) {
            case 1: showStockManagementMenu(); break;
            case 2: showPlantLifecycleMenu(); break;
            case 3: showFactoryProductionMenu(); break;
            case 4: {
                clearScreen();
                printHeader("📊 INVENTORY STATUS");
                stockManager->displayAllStock();
                std::cout << "\n";
                stockManager->displayInventoryBreakdown();
                pressEnter();
                break;
            }
            case 5: {
                clearScreen();
                printHeader("🔔 NOTIFICATION LOG");
                observer->displayLog();
                std::cout << "\n Total notifications: " << observer->getLogSize() << "\n";
                pressEnter();
                break;
            }
        }
    }
}

// ///Stock Management Menu(Kiolin's Factory/Composite)
void CompleteNurseryUI::showStockManagementMenu() {
    clearScreen();
    printHeader("📦 STOCK MANAGEMENT");
    
    std::cout << "\n Current Stock:\n";
    std::cout << " Flowers: " << stockManager->getFlowerStockSize() << "\n";
    std::cout << " Succulents: " << stockManager->getSucculentStockSize() << "\n";
    std::cout << " Trees: " << stockManager->getTreeStockSize() << "\n\n";
    
    std::cout << " 1. Add Individual Plant\n";
    std::cout << " 2. Create Plant Group (Composite)\n";
    std::cout << " 3. View All Stock\n";
    std::cout << " 4. Remove from Stock\n";
    std::cout << " 0. Back\n\n";
    
    std::cout << " Enter choice: ";
    int choice = getValidatedInput(0, 4);
    
    switch (choice) {
        case 1: {
            std::cout << "\n Plant type:\n 1. Flower\n 2. Succulent\n 3. Tree\n";
            int type = getValidatedInput(1, 3);
            
            std::string name, species;
            double price;
            
            std::cout << " Name: ";
            std::getline(std::cin, name);
            std::cout << " Species: ";
            std::getline(std::cin, species);
            std::cout << " Price: R";
            std::cin >> price;
            std::cin.ignore();
            
            if (type == 1) {
                stockManager->addFlower(new Rose(name, price, species));
            } else if (type == 2) {
                stockManager->addSucculent(new Cacti(name, price, species));
            } else {
                //Pine has three params
                stockManager->addTree(new Pine(name, price, species));
            }
            
            printSuccess("Plant added to stock!");
            break;
        }
        case 2: {
            std::cout << "\n Group type:\n 1. Flower Bouquet\n 2. Succulent Arrangement\n 3. Tree Collection\n";
            int type = getValidatedInput(1, 3);
            
            std::string groupName;
            std::cout << " Group name: ";
            std::getline(std::cin, groupName);
            
            if (type == 1) {
                FlowerFactory factory;
                FlowerGroup* group = factory.createFlowerGroup(groupName);
                group->add(new Rose("Rose", 45.99, "Default"));
                group->add(new Lotus("Lotus", 65.50, "Default"));
                stockManager->addFlower(group);
                printSuccess("Bouquet created with " + std::to_string(group->getCount()) + " flowers!");
            } else if (type == 2) {
                SucculentFactory factory;
                SucculentGroup* group = factory.createSucculentGroup(groupName);
                group->add(new Cacti("Cacti", 32.75, "Default"));
                group->add(new Jade("Jade", 28.50, "Default"));
                stockManager->addSucculent(group);
                printSuccess("Arrangement created with " + std::to_string(group->getCount()) + " succulents!");
            } else {
                TreeFactory factory;
                TreeGroup* group = factory.createTreeGroup(groupName);
                group->add(new Pine("Pine", 120.00, "Default"));
                group->add(new Apple("Apple", 95.75, "Default"));
                stockManager->addTree(group);
                printSuccess("Collection created with " + std::to_string(group->getCount()) + " trees!");
            }
            break;
        }
        case 3:
            std::cout << "\n";
            stockManager->displayAllStock();
            break;
        case 4:
            std::cout << "\n Remove from:\n 1. Flowers\n 2. Succulents\n 3. Trees\n";
            int rtype = getValidatedInput(1, 3);
            std::cout << " Index: ";
            int idx = getValidatedInput(0, 100);
            
            if (rtype == 1 && idx < stockManager->getFlowerStockSize()) {
                stockManager->removeFlower(idx);
                printSuccess("Flower removed!");
            } else if (rtype == 2 && idx < stockManager->getSucculentStockSize()) {
                stockManager->removeSucculent(idx);
                printSuccess("Succulent removed!");
            } else if (rtype == 3 && idx < stockManager->getTreeStockSize()) {
                stockManager->removeTree(idx);
                printSuccess("Tree removed!");
            }
            break;
    }
    pressEnter();
}

void CompleteNurseryUI::showFactoryProductionMenu() {
    clearScreen();
    printHeader("🏭 FACTORY PRODUCTION");
    
    std::cout << "\n Demonstrating Factory Pattern...\n\n";
    std::cout << " How many of each type to produce? ";
    int count = getValidatedInput(1, 10);
    
    FlowerFactory flowerFactory;
    SucculentFactory succulentFactory;
    TreeFactory treeFactory;
    
    std::cout << "\n Creating plants using factories...\n";
    
    for (int i = 0; i < count; i++) {
        FlowerProduct* flower = flowerFactory.createFlower(
            "Factory Flower " + std::to_string(i), 
            25.0 + i, 
            "Rose", 
            1
        );
        
        SucculentProduct* succulent = succulentFactory.createSucculent(
            "Factory Succulent " + std::to_string(i), 
            15.0 + i, 
            "Jade", 
            1
        );
        
        TreeProduct* tree = treeFactory.createTree(
            "Factory Tree " + std::to_string(i), 
            80.0 + i, 
            "Oak", 
            1
        );
        
        stockManager->addFlower(flower);
        stockManager->addSucculent(succulent);
        stockManager->addTree(tree);
    }
    
    printSuccess("Produced " + std::to_string(count) + " of each plant type!");
    std::cout << " Total items added to stock: " << (count * 3) << "\n";
    std::cout << "\n Stock breakdown:\n";
    std::cout << " • Flowers: " << stockManager->getFlowerStockSize() << "\n";
    std::cout << " • Succulents: " << stockManager->getSucculentStockSize() << "\n";
    std::cout << " • Trees: " << stockManager->getTreeStockSize() << "\n";
    
    pressEnter();
}




// Plant Lifecycle Menu (Rene's State Pattern)
void CompleteNurseryUI::showPlantLifecycleMenu() {
    while (true) {
        clearScreen();
        printHeader("🌱 PLANT LIFECYCLE MANAGEMENT");
        
        if (!growingPlants.empty()) {
            std::cout << "\n Growing Plants:\n";
            for (size_t i = 0; i < growingPlants.size(); i++) {
                std::cout << " " << (i + 1) << ". " << growingPlants[i]->getPlant()->getName()
                         << " | Age: " << growingPlants[i]->getAge() << " days"
                         << " | " << growingPlants[i]->getCurrentStateName() << "\n";
            }
            std::cout << "\n";
        } else {
            std::cout << "\n No plants currently growing.\n\n";
        }
        
        std::cout << " 1. Start New Plant\n";
        std::cout << " 2. Age Plant\n";
        std::cout << " 3. Check Readiness\n";
        std::cout << " 4. Harvest Plant\n";
        std::cout << " 5. View Details\n";
        std::cout << " 0. Back\n\n";
        
        std::cout << " Enter choice: ";
        int choice = getValidatedInput(0, 5);
        
        if (choice == 0) break;
        
        switch (choice) {
            case 1: {
                std::cout << "\n Type:\n 1. Flower\n 2. Tree\n 3. Succulent\n";
                int type = getValidatedInput(1, 3);
                
                std::string typeStr = (type == 1) ? "Flower" : (type == 2) ? "Tree" : "Succulent";
                std::string name, species;
                double price;
                
                std::cout << " Name: ";
                std::getline(std::cin, name);
                std::cout << " Species: ";
                std::getline(std::cin, species);
                std::cout << " Price: R";
                std::cin >> price;
                std::cin.ignore();
                
                PlantContext* newPlant = new PlantContext(typeStr, name, price, species);
                growingPlants.push_back(newPlant);
                
                printSuccess("Plant started in SEEDLING state!");
                std::cout << " State: " << newPlant->getCurrentStateName() << "\n";
                break;
            }
            case 2: {
                if (growingPlants.empty()) {
                    printError("No plants to age!");
                    break;
                }
                
                std::cout << "\n Select plant: ";
                int sel = getValidatedInput(1, growingPlants.size());
                std::cout << " Age by days: ";
                int days = getValidatedInput(1, 100);
                
                growingPlants[sel - 1]->ageState(days);
                printSuccess("Plant aged " + std::to_string(days) + " days!");
                std::cout << " New age: " << growingPlants[sel - 1]->getAge() << " days\n";
                std::cout << " State: " << growingPlants[sel - 1]->getCurrentStateName() << "\n";
                break;
            }
            case 3: {
                if (growingPlants.empty()) {
                    printError("No plants to check!");
                    break;
                }
                
                std::cout << "\n Select plant: ";
                int sel = getValidatedInput(1, growingPlants.size());
                std::cout << "\n";
                growingPlants[sel - 1]->checkReadiness();
                break;
            }
            case 4: {
                if (growingPlants.empty()) {
                    printError("No plants to harvest!");
                    break;
                }
                
                std::cout << "\n Select plant: ";
                int sel = getValidatedInput(1, growingPlants.size());
                std::cout << "\n";
                growingPlants[sel - 1]->harvest();
                
                printSuccess("Plant harvested!");
                delete growingPlants[sel - 1];
                growingPlants.erase(growingPlants.begin() + (sel - 1));
                break;
            }
            case 5: {
                if (growingPlants.empty()) {
                    printError("No plants to view!");
                    break;
                }
                
                std::cout << "\n Select plant: ";
                int sel = getValidatedInput(1, growingPlants.size());
                
                PlantContext* p = growingPlants[sel - 1];
                std::cout << "\n╔══ PLANT DETAILS ══╗\n";
                std::cout << " Name: " << p->getPlant()->getName() << "\n";
                std::cout << " Type: " << p->getPlantType() << "\n";
                std::cout << " Species: " << p->getPlant()->getPlantType() << "\n";
                std::cout << " Price: R" << p->getPlant()->getPrice() << "\n";
                std::cout << " Age: " << p->getAge() << " days\n";
                std::cout << " State: " << p->getCurrentStateName() << "\n";
                std::cout << "╚═══════════════════╝\n";
                break;
            }
        }
        pressEnter();
    }
}


///Taskeens BUilder State and Prototype

// Personalization Menu (Builder + Decorator patterns)
void CompleteNurseryUI::personalizeSelectedPlant(Plant* plant) {
    clearScreen();
    printHeader("🎨 PERSONALIZE YOUR PLANT");
    
    std::cout << "\n Selected: " << plant->getName() << " (R" << plant->getPrice() << ")\n";
    printSubHeader("DECORATION OPTIONS");
    
    std::cout << " 1. Add Decorative Pot\n";
    std::cout << " 2. Add Gift Wrap\n";
    std::cout << " 3. Add Personal Note\n";
    std::cout << " 4. Create Custom Arrangement (Builder)\n";
    std::cout << " 5. View Available Options\n";
    std::cout << " 0. Done\n\n";
    
    while (true) {
        std::cout << " Enter choice (0 when done): ";
        int choice = getValidatedInput(0, 5);
        
        if (choice == 0) {
            printSuccess("Personalization complete!");
            break;
        }
        
        switch (choice) {
            case 1: {
                std::cout << "\n Available Pots:\n";
                const auto& pots = inventory->getPots();
                for (size_t i = 0; i < pots.size(); i++) {
                    std::cout << "  " << (i + 1) << ". " << pots[i] << "\n";
                }
                
                std::cout << "\n Select pot (0 to skip): ";
                int potChoice = getValidatedInput(0, pots.size());
                
                if (potChoice > 0) {
                    std::string color;
                    std::cout << " Pot color: ";
                    std::cin.ignore();
                    std::getline(std::cin, color);
                    
                    double potPrice = 25.0;
                    std::cout << "\n ✓ Added " << color << " decorative pot (+R" << potPrice << ")\n";
                    // Note: Actual decoration would be applied via Decorator pattern
                }
                break;
            }
            
            case 2: {
                std::cout << "\n Available Gift Wraps:\n";
                const auto& wraps = inventory->getGiftWraps();
                for (size_t i = 0; i < wraps.size(); i++) {
                    std::cout << "  " << (i + 1) << ". " << wraps[i] << "\n";
                }
                
                std::cout << "\n Select wrap (0 to skip): ";
                int wrapChoice = getValidatedInput(0, wraps.size());
                
                if (wrapChoice > 0) {
                    std::string message;
                    std::cout << " Gift message: ";
                    std::cin.ignore();
                    std::getline(std::cin, message);
                    
                    double wrapPrice = 15.0;
                    std::cout << "\n ✓ Added gift wrap with message (+R" << wrapPrice << ")\n";
                }
                break;
            }
            
            case 3: {
                std::cout << "\n Available Notes:\n";
                const auto& notes = inventory->getNotes();
                for (size_t i = 0; i < notes.size(); i++) {
                    std::cout << "  " << (i + 1) << ". " << notes[i] << "\n";
                }
                
                std::string noteText;
                std::cout << "\n Your note: ";
                std::cin.ignore();
                std::getline(std::cin, noteText);
                
                double notePrice = 5.0;
                std::cout << "\n ✓ Added personal note (+R" << notePrice << ")\n";
                break;
            }
            
            case 4: {
                clearScreen();
                printSubHeader("CUSTOM ARRANGEMENT BUILDER");
                
                std::cout << "\n Creating custom arrangement...\n";
                std::cout << " This demonstrates the Builder pattern!\n\n";
                
                // Clone prototype
                std::unique_ptr<Item> proto = prototypeRegistry->cloneOf(plant->getName());
                
                if (proto) {
                    // Use Director to build a gift arrangement
                    std::unique_ptr<Item> giftItem = director->buildGift(
                        *proto, 
                        25.0,  // pot price
                        "Custom", // pot color
                        15.0,  // wrap price
                        "Special gift!" // message
                    );
                    
                    std::cout << " Arrangement created: " << giftItem->describe() << "\n";
                    std::cout << " Total price: R" << giftItem->priceFunc() << "\n";
                    printSuccess("Custom arrangement built!");
                } else {
                    printError("Prototype not found for " + plant->getName());
                }
                break;
            }
            
            case 5: {
                clearScreen();
                printSubHeader("ALL DECORATION OPTIONS");
                inventory->displayAllOptions();
                pressEnter();
                break;
            }
        }
    }
}

//Payment Menu (State Pattern)
void CompleteNurseryUI::showPaymentMenu() {
    clearScreen();
    printHeader("💳 PAYMENT SYSTEM");
    
    if (!currentCustomer) {
        printError("Please sign in as a customer first!");
        pressEnter();
        return;
    }
    
    // Check if cart has items
    CartIterator cartIt(currentCustomer->getCart());
    int itemCount = 0;
    for (cartIt.first(); !cartIt.isDone(); cartIt.next()) itemCount++;
    
    if (itemCount == 0) {
        printError("Your cart is empty! Add items before payment.");
        pressEnter();
        return;
    }
    
    double total = calculateCartTotal();
    
    std::cout << "\n╔═══ ORDER SUMMARY ═══╗\n";
    std::cout << " Customer: " << currentCustomer->nameFunc() << "\n";
    std::cout << " Items: " << itemCount << "\n";
    std::cout << " Total: R" << total << "\n";
    std::cout << "╚════════════════════╝\n";
    
    printSubHeader("PAYMENT STATE FLOW");
    std::cout << " This demonstrates the State Pattern!\n\n";
    
    // Create sales context (State pattern)
    BrowsingState initialState;
    if (salesContext) delete salesContext;
    salesContext = new SalesContext(initialState, *currentCustomer);
    
    // Simulate in-stock scenario
    std::cout << " 1. Process Payment (Happy Path)\n";
    std::cout << " 2. Simulate Out-of-Stock Scenario\n";
    std::cout << " 3. Simulate Payment Failure\n";
    std::cout << " 0. Cancel\n\n";
    
    std::cout << " Enter choice: ";
    int choice = getValidatedInput(0, 3);
    
    switch (choice) {
        case 1: {
            // Happy path: Browse → Cart → Payment → Complete
            std::cout << "\n╔═══ PROCESSING PAYMENT ═══╗\n";
            
            // Put stock for items in cart
            cartIt.first();
            while (!cartIt.isDone()) {
                Plant* p = cartIt.currentItem();
                salesContext->putStock(p->getName(), 10);
                cartIt.next();
            }
            
            std::cout << " State: Browsing\n";
            
            // Select items (Browsing → CartOpen)
            cartIt.first();
            if (!cartIt.isDone()) {
                Plant* firstPlant = cartIt.currentItem();
                std::cout << " → Selecting " << firstPlant->getName() << "...\n";
                salesContext->eventSelect(firstPlant->getName(), 1);
                std::cout << " State changed to: CartOpen\n";
            }
            
            // Proceed to checkout (CartOpen → PendingPayment)
            std::cout << " → Proceeding to checkout...\n";
            salesContext->eventCheckout();
            std::cout << " State changed to: PendingPayment\n";
            
            // Authorize payment (PendingPayment → PaymentAuthorized)
            std::cout << " → Authorizing payment...\n";
            salesContext->eventAuthorize();
            std::cout << " State changed to: PaymentAuthorized\n";
            
            // Commit/Capture payment (PaymentAuthorized → Completed)
            std::cout << " → Completing transaction...\n";
            salesContext->eventCommit();
            std::cout << " State changed to: Completed\n";
            
            printSuccess("Payment processed successfully!");
            std::cout << "╚═════════════════════════╝\n";
            
            //Clear cart after successful payment
            //currentCustomer->getCart()->clear();
            break;
        }
        
        case 2: {
            // Out-of-stock path: Browsing → SeekingAssistance → AwaitingStock
            std::cout << "\n╔═══ OUT-OF-STOCK SCENARIO ═══╗\n";
            
            std::cout << " State: Browsing\n";
            
            // Try to select out-of-stock item
            cartIt.first();
            if (!cartIt.isDone()) {
                Plant* p = cartIt.currentItem();
                std::cout << " → Selecting " << p->getName() << " (out of stock)...\n";
                salesContext->eventSelect(p->getName(), 1);
                std::cout << " State changed to: SeekingAssistance\n";
            }
            
            // Assistance complete → AwaitingStock
            std::cout << " → Staff assists customer...\n";
            salesContext->eventAssistComplete();
            std::cout << " State changed to: AwaitingStock\n";
            
            // Simulate stock replenishment
            cartIt.first();
            if (!cartIt.isDone()) {
                Plant* p = cartIt.currentItem();
                std::cout << " → Greenhouse replenishes " << p->getName() << "...\n";
                salesContext->putStock(p->getName(), 5);
                salesContext->eventReplenished();
                std::cout << " State changed to: CartOpen\n";
            }
            
            printSuccess("Stock replenished! Can now proceed to payment.");
            std::cout << "╚═════════════════════════════╝\n";
            break;
        }
        
        case 3: {
            // Payment failure path
            std::cout << "\n╔═══ PAYMENT FAILURE SCENARIO ═══╗\n";
            
            // Setup stock
            cartIt.first();
            while (!cartIt.isDone()) {
                salesContext->putStock(cartIt.currentItem()->getName(), 10);
                cartIt.next();
            }
            
            // Go through to checkout
            cartIt.first();
            if (!cartIt.isDone()) {
                salesContext->eventSelect(cartIt.currentItem()->getName(), 1);
                salesContext->eventCheckout();
            }
            
            std::cout << " State: PendingPayment\n";
            std::cout << " → Payment authorization failed!\n";
            
            #ifdef SUPPORT_TEST_TOGGLES
            // If your State implementation supports test toggles
            salesContext->forceNextAuth(false);
            salesContext->eventAuthorize();
            std::cout << " State changed to: PaymentFailed\n";
            
            std::cout << " → Customer retries payment...\n";
            salesContext->forceNextAuth(true);
            salesContext->eventRetry();
            salesContext->eventAuthorize();
            salesContext->eventCommit();
            printSuccess("Payment succeeded on retry!");
            #else
            std::cout << " State: PaymentFailed\n";
            std::cout << " (Retry functionality requires SUPPORT_TEST_TOGGLES)\n";
            #endif
            
            std::cout << "╚════════════════════════════════╝\n";
            break;
        }
        
        case 0:
            std::cout << "\n Payment cancelled.\n";
            break;
    }
    
    pressEnter();
}