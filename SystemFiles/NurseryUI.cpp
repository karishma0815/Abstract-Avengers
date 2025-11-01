#include "NurseryUI.h"

int NurseryUI::getValidatedInput(int min, int max) {
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
        std::cout << "Invalid! Enter " << min << "-" << max << ": ";
    }
}
void NurseryUI::clearScreen() {
    std::cout << "\033[2J\033[1;1H"; // ANSI escape sequence to clear screen
}

    void NurseryUI::pressEnterToContinue() {
        std::cout << "\nPress Enter to continue...";
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

    void NurseryUI::initializeInventory() {
        inventory = new PlantInventory();
        
        // Add sample plants
        //
        Plant* rose = new Rose("Rose", 25.0, "Hybrid Tea");
        rose->setCareInstructions("High maintenance: Daily watering, weekly fertilizing");
        
        Plant* cactus = new Cacti("Cactus", 15.0, "Prickly Pear");
        cactus->setCareInstructions("Low maintenance: Monthly watering, strong sunlight");

        //Plant* fern = new Plant("Fern", true, "P003", 4, 4, 35.0);
        //fern->setCareInstructions("Medium maintenance: Weekly watering, indirect light");
        
        inventory->add(rose);
        inventory->add(cactus);
        //inventory->add(fern);
    }

    void NurseryUI::setupQueryChain() {
        // Set up the chain of responsibility for customer queries
        queryChain = new JuniorStaff();
        CustomerQueryHandler* salesExpert = new SalesExpert();
        CustomerQueryHandler* plantExpert = new PlantExpert();
        
        queryChain->setNext(salesExpert);
        salesExpert->setNext(plantExpert);
    }

    NurseryUI::NurseryUI() {
        initializeInventory();
        currentCustomer = nullptr;
        strategyContext = new StratContext(new DefaultRecomm(), new RegularPrice());
        invoker = new Invoker(nullptr);
        setupQueryChain();
    }

    NurseryUI::~NurseryUI() {
        if (inventory)
        {
           delete inventory;
        }
        if (currentCustomer)
        {
            delete currentCustomer;
        }
        if (strategyContext)
        {
            delete strategyContext;
        }
        
        if (invoker)
        {
            delete invoker;
        }

        if (queryChain)
        {
            delete queryChain;
        }  
    }

    void NurseryUI::showMainMenu() {
        while (true) {
            clearScreen();
            std::cout << "=== Welcome to the Plant Nursery ===\n\n";
            
            if (!currentCustomer) {
                std::cout << "1. Enter as new customer\n";
                std::cout << "0. Exit\n\n";
                std::cout << "Enter your choice: ";
                int choice = getValidatedInput(0, 1);
                
                if (choice == 0) break;
                
                if (choice == 1) {
                    std::cin.ignore(); 
                    std::string name;
                    std::cout << "Enter your name: ";
                    std::getline(std::cin, name);
                    currentCustomer = new Customer(name);
                    continue;
                }
        } else {
                ///this is for the customer--they'll be viewing the inventory available on sales
                ///floor!! If not there seekAssistance
                std::cout << "Current Customer: " << currentCustomer->nameFunc() << "\n\n";
                std::cout << "1. Browse Plants (Iterator Pattern)\n";
                std::cout << "2. Shopping Cart (Command Pattern)\n";
                std::cout << "3. Get Plant Recommendations (Strategy Pattern)\n";
                std::cout << "4. Check Prices (Strategy Pattern)\n";
                std::cout << "5. Ask for Help (Chain of Responsibility Pattern)\n";
                std::cout << "6. Change Customer\n";
                std::cout<< "0. Exit\n\n";
           /* }
            std::cout << "0. Exit\n\n";
            
            std::cout << "Enter your choice: ";
            int choice=getValidatedInput(0,5);

            if (choice == 0) break;

            if (!currentCustomer && choice == 1) {
                std::string name;
                std::cout << "Enter your name: ";
                std::getline(std::cin, name);
                currentCustomer = new Customer(name);
                continue;
            }

            if (!currentCustomer) {
                std::cout << "Please enter as a customer first!\n";
                pressEnterToContinue();
                continue;
            }*/
            std::cout << "Enter your choice: ";
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
                    break;
                }
            }
        }
    }
    
    void NurseryUI::showBrowsingMenu() {
        while (true) {
            clearScreen();
            std::cout << "=== Plant Browsing Menu ===\n\n";
            std::cout << "1. View All Plants\n";
            std::cout << "2. View by Price Range\n";
            std::cout << "3. View by Care Level\n";
            std::cout << "4. View Decoration Options\n";
            std::cout << "0. Back to Main Menu\n\n";
            
            std::cout << "Enter your choice: ";
            int choice;
            std::cin >> choice;

            if (choice == 0) break;

            switch (choice) {
                case 1: {
                    /*PlantIterator it(inventory);
                    std::cout << "\nAll Plants:\n";
                    for (it.first(); !it.isDone(); it.next()) {
                        Plant* plant = it.currentItem();
                        std::cout << plant->getName() << " - R" << plant->getPrice() << "\n";
                        std::cout << "Care Instructions: " << plant->getCareInstructions() << "\n\n";
                    }*/
                   PlantIterator it(inventory);
                    std::cout << "\nAll Plants:\n";
                    int num = 1;
                    for (it.first(); !it.isDone(); it.next()) {
                        Plant* plant = it.currentItem();
                        std::cout << num++ << ". " << plant->getName() << " - R" << plant->getPrice() << "\n";
                        std::cout << "   Care: " << plant->getCareInstructions() << "\n\n";
                }
                break;////check the num counter
                }
                case 2: {
                    double minPrice, maxPrice;
                    std::cout << "Enter minimum price: R";
                    while (!(std::cin >> minPrice)) {
                        std::cin.clear();
                        std::cin.ignore(10000, '\n');
                        std::cout << "Invalid! Enter minimum price: R";
                    }
                    std::cout << "Enter maximum price: R";
                    while (!(std::cin >> maxPrice)) {
                        std::cin.clear();
                        std::cin.ignore(10000, '\n');
                        std::cout << "Invalid! Enter maximum price: R";
                    }
                    std::cin.ignore(10000, '\n');
                    
                    /*PriceRangeIterator it(inventory, minPrice, maxPrice);
                    std::cout << "\nPlants in price range R" << minPrice << " - R" << maxPrice << ":\n";
                    for (it.first(); !it.isDone(); it.next()) {
                        Plant* plant = it.currentItem();
                        std::cout << plant->getName() << " - R" << plant->getPrice() << "\n";
                    }*/
                   PriceRangeIterator it(inventory, minPrice, maxPrice);
                    std::cout << "\nPlants in range R" << minPrice << " - R" << maxPrice << ":\n";
                    int num = 1;
                    for (it.first(); !it.isDone(); it.next()) {
                        Plant* plant = it.currentItem();
                        std::cout << num++ << ". " << plant->getName() << " - R" << plant->getPrice() << "\n";
                    }
                    break;
                }
                case 3: {
                    /*std::string careLevel;
                    std::cout << "Enter care level (low/medium/high): ";
                    std::cin >> careLevel;
                    
                    CareIterator it(inventory, careLevel);
                    std::cout << "\nPlants with " << careLevel << " maintenance:\n";
                    for (it.first(); !it.isDone(); it.next()) {
                        Plant* plant = it.currentItem();
                        std::cout << plant->getName() << " - R" << plant->getPrice() << "\n";
                        std::cout << "Care Instructions: " << plant->getCareInstructions() << "\n\n";
                    }*/
                   std::string careLevel;
                    std::cout << "Enter care level (low/medium/high): ";
                    std::getline(std::cin, careLevel);
                    
                    CareIterator it(inventory, careLevel);
                    std::cout << "\nPlants with " << careLevel << " maintenance:\n";
                    int num = 1;
                    for (it.first(); !it.isDone(); it.next()) {
                        Plant* plant = it.currentItem();
                        std::cout << num++ << ". " << plant->getName() 
                                << " - R" << plant->getPrice() << "\n";
                        std::cout << "   " << plant->getCareInstructions() << "\n\n";
                    }
                    break;
                }
                case 4:{
                    showDecorationMenu();
                    break;
                }
                default:
                    std::cout << "\nInvalid choice!\n";
            }
            pressEnterToContinue();
        }
    }


    //Comment this out till you figure it out!!!
    void NurseryUI::showCartMenu() {
        while (true) {
            clearScreen();
            std::cout << "=== Shopping Cart Menu ===\n\n";

            CartIterator cartIt(currentCustomer);
            bool isEmpty = true;
            double total = 0.0;
            int num = 1;
        
        // Check if cart has items
            for (cartIt.first(); !cartIt.isDone(); cartIt.next()) {
                isEmpty = false;
                Plant* plant = cartIt.currentItem();
                std::cout << num++ << ". " << plant->getName() 
                        << " - R" << plant->getPrice() << "\n";
                total += plant->getPrice();
            }
            
            if (isEmpty) {
                std::cout << "Your cart is empty.\n\n";
            } else {
                std::cout << "\nTotal: R" << total << "\n\n";
            }
            
        
        std::cout << "1. Add Plant to Cart\n";
        std::cout << "2. Remove Plant from Cart\n";
        std::cout << "3. View Cart\n";
        std::cout << "0. Back to Main Menu\n\n";
            
        std::cout << "Enter your choice: ";
            
        int choice = getValidatedInput(0, 3);

        if (choice == 0) break;

        switch (choice) {
            case 1: {
                // Show available plants
                PlantIterator it(inventory);
                std::vector<Plant*> plants;
                
                std::cout << "\nAvailable Plants:\n";
                int num = 1;
                for (it.first(); !it.isDone(); it.next()) {
                    plants.push_back(it.currentItem());
                    std::cout << num++ << ". " << it.currentItem()->getName() 
                             << " - R" << it.currentItem()->getPrice() << "\n";
                }
                
                if (plants.empty()) {
                    std::cout << "\nNo plants available!\n";
                    break;
                }
                
                std::cout << "\nSelect plant number (0 to cancel): ";
                int sel = getValidatedInput(0, plants.size());
                
                if (sel > 0) {
                    Plant* selected = plants[sel - 1];
                    
                    // USE COMMAND PATTERN
                    Command* cmd = new AddToCart(currentCustomer, selected);
                    invoker->setCommand(cmd);
                    invoker->executeCommand();
                    
                    std::cout << "\n" << selected->getName() << " added to cart!\n";
                }
                break;
            }
            case 2: {
                if (!currentCustomer || currentCustomer->getCart().empty()) {
                    std::cout << "\nCart is empty!\n";
                    break;
                }
                
                std::cout << "\nSelect item to remove (0 to cancel): ";
                int sel = getValidatedInput(0, currentCustomer->getCart().size());
                
                if (sel > 0) {
                    Plant* toRemove = currentCustomer->getCart()[sel - 1];
                    
                    // USE COMMAND PATTERN
                    Command* cmd = new RemoveFromCart(currentCustomer, toRemove);
                    invoker->setCommand(cmd);
                    invoker->executeCommand();
                    
                    std::cout << "\nItem removed!\n";
                }
                break;
            }
            case 3: {
                // Already shown at top
                std::cout << "\n(Cart displayed above)\n";
                break;
            }
        }
            pressEnterToContinue();
        }
    }

    void NurseryUI::showDecorationMenu() {
        while (true) {
            clearScreen();
            std::cout << "=== Decoration Options ===\n\n";
            std::cout << "1. View Gift Wraps\n";
            std::cout << "2. View Decorative Pots\n";
            std::cout << "3. View Notes\n";
            std::cout << "0. Back\n\n";

            std::cout << "Enter your choice: ";
            int choice;
            std::cin >> choice;

            if (choice == 0) break;

            switch (choice) {
                case 1: {
                    const auto& wraps = inventory->getGiftWraps();
                    std::cout << "\nAvailable Gift Wraps:\n";
                    for (size_t i = 0; i < wraps.size(); ++i) {
                        std::cout << "  " << (i + 1) << ". " << wraps[i] << "\n";
                    }
                    break;
                }
                case 2: {
                    const auto& pots = inventory->getPots();
                    std::cout << "\nAvailable Decorative Pots:\n";
                    for (size_t i = 0; i < pots.size(); ++i) {
                        std::cout << "  " << (i + 1) << ". " << pots[i] << "\n";
                    }
                    break;
                }
                case 3: {
                    const auto& notes = inventory->getNotes();
                    std::cout << "\nAvailable Notes:\n";
                    for (size_t i = 0; i < notes.size(); ++i) {
                        std::cout << "  " << (i + 1) << ". " << notes[i] << "\n";
                    }
                    break;
                }
                default:
                    std::cout << "Invalid choice\n";
            }

            pressEnterToContinue();
        }
    }

    void NurseryUI::showRecommendationMenu() {
        while (true) {
            clearScreen();
            std::cout << "=== Plant Recommendations Menu ===\n\n";
            std::cout << "1. Get General Recommendations\n";
            std::cout << "2. Get Water-based Recommendations\n";
            std::cout << "3. Get Sunlight-based Recommendations\n";
            std::cout << "0. Back to Main Menu\n\n";
            
            std::cout << "Enter your choice: ";
            int choice;
            std::cin >> choice;

            if (choice == 0) break;

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
            pressEnterToContinue();
        }
    }

    void NurseryUI::showPricingMenu() {
        while (true) {
            clearScreen();
            std::cout << "=== Pricing Menu ===\n\n";
            std::cout << "1. Check Regular Price\n";
            std::cout << "2. Check Bulk Price\n";
            std::cout << "0. Back to Main Menu\n\n";
            
            std::cout << "Enter your choice: ";
            int choice;
            std::cin >> choice;

            if (choice == 0) break;

            double basePrice = 25.0; // Example base price
            switch (choice) {
                case 1:
                    strategyContext->setPricingStrategy(new RegularPrice());
                    std::cout << "Regular price: R" << 
                        strategyContext->executePricingStrategy(1, basePrice, "") << std::endl;
                    break;
                case 2:
                    strategyContext->setPricingStrategy(new BulkDiscount());
                    std::cout << "Bulk price (10 items): R" << 
                        strategyContext->executePricingStrategy(10, basePrice, "BULK10") << std::endl;
                    break;
            }
            pressEnterToContinue();
        }
    }

    void NurseryUI::showHelpMenu() {
        while (true) {
            clearScreen();
            std::cout << "=== Help Menu ===\n\n";
            std::cout << "1. Ask about Pricing\n";
            std::cout << "2. Ask about Plant Care\n";
            std::cout << "3. General Query\n";
            std::cout << "0. Back to Main Menu\n\n";
            
            std::cout << "Enter your choice: ";
            int choice;
            std::cin >> choice;

            if (choice == 0) break;

            std::string question;
            std::cout << "Enter your question: ";
            std::cin.ignore();
            std::getline(std::cin, question);

            CustomerQuery::Type queryType;
            switch (choice) {
                case 1: queryType = CustomerQuery::PRICING; break;
                case 2: queryType = CustomerQuery::CARE_ADVICE; break;
                case 3: queryType = CustomerQuery::GENERAL; break;
                default: continue;
            }

            CustomerQuery query(queryType, question, currentCustomer);
            queryChain->handleQuery(query);
            pressEnterToContinue();
        }
    }

