#include "NurseryUI.h"


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
        Plant* rose = new Plant("Rose", false, "P001", 6, 3, 25.0);
        rose->setCareInstructions("High maintenance: Daily watering, weekly fertilizing");
        
        Plant* cactus = new Plant("Cactus", false, "P002", 8, 1, 15.0);
        cactus->setCareInstructions("Low maintenance: Monthly watering, strong sunlight");
        
        Plant* fern = new Plant("Fern", true, "P003", 4, 4, 35.0);
        fern->setCareInstructions("Medium maintenance: Weekly watering, indirect light");
        
        inventory->add(rose);
        inventory->add(cactus);
        inventory->add(fern);
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
        delete inventory;
        delete currentCustomer;
        delete strategyContext;
        delete invoker;
        delete queryChain;
    }

    void NurseryUI::showMainMenu() {
        while (true) {
            clearScreen();
            std::cout << "=== Welcome to the Plant Nursery ===\n\n";
            
            if (!currentCustomer) {
                std::cout << "1. Enter as new customer\n";
            } else {
                std::cout << "Current Customer: " << currentCustomer->nameFunc() << "\n\n";
                std::cout << "1. Browse Plants (Iterator Pattern)\n";
                std::cout << "2. Shopping Cart (Command Pattern)\n";
                std::cout << "3. Get Plant Recommendations (Strategy Pattern)\n";
                std::cout << "4. Check Prices (Strategy Pattern)\n";
                std::cout << "5. Ask for Help (Chain of Responsibility Pattern)\n";
                std::cout << "6. Change Customer\n";
            }
            std::cout << "0. Exit\n\n";
            
            std::cout << "Enter your choice: ";
            int choice;
            std::cin >> choice;
            std::cin.ignore();

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
            }

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
                    PlantIterator it(inventory);
                    std::cout << "\nAll Plants:\n";
                    for (it.first(); !it.isDone(); it.next()) {
                        Plant* plant = it.currentItem();
                        std::cout << plant->getName() << " - R" << plant->getPrice() << "\n";
                        std::cout << "Care Instructions: " << plant->getCareInstructions() << "\n\n";
                    }
                    // Show available decoration options after listing plants
                    std::cout << "\nDecoration options available for purchases:" << std::endl;
                    inventory->displayAllOptions();
                    break;
                }
                case 2: {
                    double minPrice, maxPrice;
                    std::cout << "Enter minimum price: R";
                    std::cin >> minPrice;
                    std::cout << "Enter maximum price: R";
                    std::cin >> maxPrice;
                    
                    PriceRangeIterator it(inventory, minPrice, maxPrice);
                    std::cout << "\nPlants in price range R" << minPrice << " - R" << maxPrice << ":\n";
                    for (it.first(); !it.isDone(); it.next()) {
                        Plant* plant = it.currentItem();
                        std::cout << plant->getName() << " - R" << plant->getPrice() << "\n";
                    }
                    // Show decoration options so customer can choose when adding to cart
                    std::cout << "\nDecoration options available for purchases:" << std::endl;
                    inventory->displayAllOptions();
                    break;
                }
                case 3: {
                    std::string careLevel;
                    std::cout << "Enter care level (low/medium/high): ";
                    std::cin >> careLevel;
                    
                    CareIterator it(inventory, careLevel);
                    std::cout << "\nPlants with " << careLevel << " maintenance:\n";
                    for (it.first(); !it.isDone(); it.next()) {
                        Plant* plant = it.currentItem();
                        std::cout << plant->getName() << " - R" << plant->getPrice() << "\n";
                        std::cout << "Care Instructions: " << plant->getCareInstructions() << "\n\n";
                    }
                    // Show decoration options for the customer
                    std::cout << "\nDecoration options available for purchases:" << std::endl;
                    inventory->displayAllOptions();
                    break;
                }
                default:
                    std::cout << "\nInvalid choice!\n";
            }
            pressEnterToContinue();
        }
    }

    void NurseryUI::showCartMenu() {
        while (true) {
            clearScreen();
            std::cout << "=== Shopping Cart Menu ===\n\n";
            std::cout << "1. Add Plant to Cart\n";
            std::cout << "2. Remove Plant from Cart\n";
            std::cout << "3. View Cart\n";
            std::cout << "0. Back to Main Menu\n\n";
            
            std::cout << "Enter your choice: ";
            int choice;
            std::cin >> choice;

            if (choice == 0) break;

            switch (choice) {
                case 1: {
                    // Add to cart implementation
                    break;
                }
                // Add other cases as needed
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

