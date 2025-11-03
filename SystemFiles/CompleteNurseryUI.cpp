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
   // prototypeRegistry = new PrototypeRegistry();
    arrangementBuilder = new ConcreteArrangementBuilder();
    director = new Director();
    director->setBuilder(arrangementBuilder);
    salesContext = nullptr; 
    
    // Initialize systems
    initializeNursery();
    setupStaff();
    setupQueryChain();

    //I dont think this is needed anymore
    //cause i changed the files to make arrangement clones only
    //not item clones - Taskeen

    /*prototypeRegistry->registerPrototype("Rose", 
        std::unique_ptr<Item>(new PlantItem("Rose", 45.99, true)));
    prototypeRegistry->registerPrototype("Cactus", 
        std::unique_ptr<Item>(new PlantItem("Cactus", 32.75, true)));
    prototypeRegistry->registerPrototype("Jade", 
        std::unique_ptr<Item>(new PlantItem("Jade", 28.50, true)));
    prototypeRegistry->registerPrototype("Fern", 
        std::unique_ptr<Item>(new PlantItem("Fern", 35.0, true)));*/
    
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

    //delete prototypeRegistry;
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

    //added new plants to the list
    Plant* lotus = new Lotus("Pink Lotus", 65.50);
    lotus->setCareInstructions("Aquatic plant: Keep in water, full sunlight");
    
    Plant* protea = new Protea("King Protea", 85.25);
    protea->setCareInstructions("Moderate maintenance: Well-drained soil, partial sun");
    
    Plant* orchid = new Orchid("Moth Orchid", 42.80);
    orchid->setCareInstructions("Moderate maintenance: Indirect light, weekly watering");
    
    Plant* apple = new Apple("Apple Tree", 95.75);
    apple->setCareInstructions("Seasonal care: Full sun, regular watering, winter pruning");
    
    Plant* jacaranda = new Jacaranda("Jacaranda Tree", 120.00);
    jacaranda->setCareInstructions("Moderate maintenance: Full sun, drought tolerant");
    
    Plant* pine = new Pine("Pine Tree", 75.25);
    pine->setCareInstructions("Low maintenance: Well-drained soil, full sun");
    
    inventory->add(rose);
    inventory->add(cactus);
    inventory->add(jade);
    inventory->add(fern);

    //adding it to the inventory
    inventory->add(lotus);
    inventory->add(protea);
    inventory->add(orchid);
    inventory->add(apple);
    inventory->add(jacaranda);
    inventory->add(pine);
    
    // Add to stock manager
    stockManager->addFlower(new Rose("Stock Rose", 45.99, "Hybrid Tea"));
    stockManager->addSucculent(new Cacti("Stock Cactus", 32.75, "Barrel"));
    stockManager->addSucculent(new Jade("Stock Jade", 28.50, "Crassula"));

    //adding these new plants to the stock manager
    stockManager->addFlower(new Lotus("Stock Lotus", 65.50, "Nelumbo"));
    stockManager->addFlower(new Protea("Stock Protea", 85.25, "King"));
    stockManager->addSucculent(new Orchid("Stock Orchid", 42.80, "Phalaenopsis"));
    stockManager->addTree(new Apple("Stock Apple", 95.75, "Malus"));
    stockManager->addTree(new Jacaranda("Stock Jacaranda", 120.00, "Mimosifolia"));
    stockManager->addTree(new Pine("Stock Pine", 75.25, "Pinus"));
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
    CustomerQueryHandler* manager = new Manager("John", 101, nullptr, "Customer Service");
    
    customerQueryChain->setNext(salesExpert);
    salesExpert->setNext(plantExpert);
    plantExpert->setNext(manager);
    //delete salesExpert;
    //delete plantExpert;
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
    std::string input;
    
    while (true) {
        std::getline(std::cin, input);
    
        if (input.empty()) {
            std::cout << " Invalid! Enter " << min << "-" << max << ": ";
            continue;
        }
    
        bool allDigits = true;
        for (char c : input) {
            if (!std::isdigit(static_cast<unsigned char>(c))) {
                allDigits = false;
                break;
            }
        }
        
        if (allDigits) {
            try {
                int choice = std::stoi(input);
                
                if (choice >= min && choice <= max) {
                    return choice;
                }
            } catch (const std::exception& e) {
                
            }
        }
        std::cout << " Invalid! Enter " << min << "-" << max << ": ";
    }
}

void CompleteNurseryUI::printHeader(const std::string& title) {
    std::cout << "\n";
    std::cout << "╔════════════════════════════════════════════════════════╗\n";
    std::cout << "║  " << std::left << std::setw(52) << title << "         ║\n";
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
        std::cout << "│  📊 4. System Status                             │\n";
        std::cout << "|  💲 5. Payment                                   |\n";
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
                showStaffMenu();
                //std::cout<<"StaffMenu still in progress\n";
                break;
                
            }
            case 3: 
            {
                showGreenhouseMenu();
               break;
            }

            case 4: {
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
            case 5:{
                showPaymentMenu();
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
        std::cout << " 3. View Decoration Options\n";
        std::cout << " 0. Back\n\n";
        
        std::cout << " Enter choice: ";
        int choice = getValidatedInput(0, 3);
        
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
                clearScreen();
                printSubHeader("DECORATION OPTIONS");
                inventory->displayAllOptions();
                pressEnter();
                break;
            }
        }
    }
}

//for arrangements
void CompleteNurseryUI::buildArrangementFlow() {
    clearScreen();
    printSubHeader("CUSTOM ARRANGEMENT");

    // Ask how many different plants (min 2)
    std::cout << "\n How many different plants do you want? (min 2): ";
    int qty = getValidatedInput(2, 50);

    // Snapshot and ensure enough distinct plants to choose from
    std::vector<Plant*> available = inventory->getPlants();
    std::sort(available.begin(), available.end());
    available.erase(std::unique(available.begin(), available.end()), available.end());

    if (static_cast<int>(available.size()) < qty) {
        printError("Not enough different plants on the sales floor.");
        pressEnter();
        return;
    }

    // Choose plants (each must be unique)
    std::vector<std::unique_ptr<Item>> items;
    items.reserve(static_cast<size_t>(qty));
    double itemsSubtotal = 0.0;

    for (int k = 0; k < qty; ++k) {
        clearScreen();
        std::cout << " Select base plant " << (k+1) << " of " << qty << ":\n\n";
        for (size_t i = 0; i < available.size(); ++i) {
            std::cout << "  " << (i+1) << ". " << available[i]->getName()
                      << " (R" << available[i]->getPrice() << ")\n";
        }
        std::cout << "\n Enter choice: ";
        int idx = getValidatedInput(1, static_cast<int>(available.size())) - 1;

        Plant* chosen = available[static_cast<size_t>(idx)];
        available.erase(available.begin() + idx);           // prevent duplicates

        // Wrap abstract Plant* as Item via adapter
        std::unique_ptr<Item> base(new PlantAsItemAdapter(chosen));
        itemsSubtotal += base->priceFunc();
        items.push_back(std::move(base));
    }

    // Ask ONE-TIME decoration for the whole arrangement (free)
    bool wantPot=false, wantWrap=false, wantNote=false;
    std::string potColor, noteText;

    // Pot
    std::cout << "\n Add decorative pot to the arrangement? (1 = yes, 0 = no): ";
    wantPot = (getValidatedInput(0,1) == 1);
    if (wantPot) {
        const auto& pots = inventory->getPots();
        if (!pots.empty()) {
            std::cout << " Available Pots:\n";
            for (size_t i=0;i<pots.size();++i) std::cout << "  " << (i+1) << ". " << pots[i] << "\n";
            std::cout << " Choose pot (1-" << pots.size() << "): ";
            int p = getValidatedInput(1, static_cast<int>(pots.size()));
            potColor = pots[static_cast<size_t>(p-1)];
        } else {
            potColor = "Standard";
        }
    }

    // Wrap (bouquet style) — no message
    std::cout << " Add bouquet-style gift wrap? (1 = yes, 0 = no): ";
    wantWrap = (getValidatedInput(0,1) == 1);

    // Note (with message)
    std::cout << " Add a note? (1 = yes, 0 = no): ";
    wantNote = (getValidatedInput(0,1) == 1);
    if (wantNote) {
        std::cout << " Note text: ";
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::getline(std::cin, noteText);
        if (noteText.empty()) wantNote = false;
    }

    // Apply the ONE decoration chain to the first item only (free)
    if (!items.empty() && (wantPot || wantWrap || wantNote)) {
        ConcreteArrangementBuilder builder;
        builder.reset();
        builder.buildBasePlant(std::move(items[0]));   // take ownership

        if (wantPot)  builder.buildPot (0.0, potColor);
        if (wantWrap) builder.buildWrap(0.0, "Bouquet Wrap");
        if (wantNote) builder.buildNote(0.0, noteText);

        items[0] = builder.getResult();               // decorated first item
    }

    // Preview & confirm
    clearScreen();
    printSubHeader("ARRANGEMENT PREVIEW (decorated once)");
    for (size_t i = 0; i < items.size(); ++i) {
        std::cout << "  - " << items[i]->describe()
                  << "  [R" << items[i]->priceFunc() << "]";
        if (i == 0 && (wantPot || wantWrap || wantNote)) std::cout << "  {decor}";
        std::cout << "\n";
    }
    std::cout << "Items subtotal: R" << itemsSubtotal << "\n";
    std::cout << "Arrangement surcharge: R0 (free)\n";
    std::cout << "Total price: R" << itemsSubtotal << "\n";

    std::cout << "\n Add arrangement to cart? (1 = yes, 0 = no): ";
    int addAll = getValidatedInput(0,1);
    if (addAll == 1) {
        for (auto& up : items) inventory->addArrangementToCart(std::move(up));
        printSuccess("Arrangement added to cart!");
    } else {
        printSuccess("Arrangement built (not added to cart).");
    }
    pressEnter();
}

//fixed cart menu with loop-> it works properly
void CompleteNurseryUI::showCartMenu() {
    struct Local {
        static int countPlants(PlantInventory* cart) {
            int n = 0; if (!cart) return 0;
            CartIterator it(cart);
            for (it.first(); !it.isDone(); it.next()) ++n;
            return n;
        }
        static std::string stateName(SalesContext* sc) {
            return sc ? sc->current().getStateName() : std::string();
        }
    };
    // -----------------------------------------------------------------------

    while (true) {
        clearScreen();
        printHeader("🛒 SHOPPING CART");

        displayCart();

        std::cout << "\n 1. Add Plant to Cart\n";
        std::cout << " 2. Remove from Cart\n";
        std::cout << " 3. Checkout (State machine)\n";
        std::cout << " 0. Back\n\n";

        std::cout << " Enter choice: ";
        int choice = getValidatedInput(0, 4);
        if (choice == 0) break;

        switch (choice) {
        case 1: {
            // Submenu: add single plant OR build a custom arrangement
            clearScreen();
            printSubHeader("ADD TO CART");
            std::cout << "\n 1. Add single plant\n";
            std::cout << " 2. Build custom arrangement\n";
            std::cout << " 0. Back\n\n";
            std::cout << " Enter choice: ";
            int sub = getValidatedInput(0, 2);

            if (sub == 2) {
                buildArrangementFlow(); 
                break;                  // back to cart menu
            }
            if (sub == 0) break;

            // ---- single plant add loop ----
            bool keepAdding = true;
            while (keepAdding) {
                clearScreen();
                printSubHeader("SELECT PLANT TO ADD");

                PlantIterator it(inventory);
                std::vector<Plant*> plants;
                int num = 1;

                std::cout << "\n Available Plants:\n";
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
                int sel = getValidatedInput(0, static_cast<int>(plants.size()));
                if (sel == 0) { keepAdding = false; break; }

                Plant* selectedPlant = plants[sel - 1];

                // Optional personalize
                std::cout << "\n Personalize this plant first? (1 = yes, 0 = no): ";
                int personalizeChoice = getValidatedInput(0, 1);
                if (personalizeChoice == 1) {
                    personalizeSelectedPlant(selectedPlant);
                }

                // Add to cart via Command (main inventory)
                PlantInventory* mainInventory = currentCustomer->getInven();
                CustomerCommand* cmd = new AddToCart();
                invoker->setCommand(cmd);
                invoker->execute(selectedPlant, mainInventory);
                delete cmd;

                printSuccess(selectedPlant->getName() + " added to cart!");

                std::cout << "\n Add another single plant? (1=Yes, 0=No): ";
                int addMore = getValidatedInput(0, 1);
                if (addMore == 0) keepAdding = false;
            }
            break;
        }

        case 2: { // Remove from cart
            PlantInventory* actualCart = currentCustomer->getCart();
            CartIterator cartIt(actualCart);
            std::vector<Plant*> cartPlants;

            for (cartIt.first(); !cartIt.isDone(); cartIt.next())
                cartPlants.push_back(cartIt.currentItem());

            if (cartPlants.empty()) {
                printError("Cart is empty!");
                pressEnter();
                break;
            }

            std::cout << "\n Select item to remove (0 to cancel): ";
            int sel = getValidatedInput(0, static_cast<int>(cartPlants.size()));
            if (sel > 0) {
                Plant* toRemove = cartPlants[sel - 1];
                PlantInventory* mainInventory = currentCustomer->getInven();

                CustomerCommand* cmd = new RemoveFromCart();
                invoker->setCommand(cmd);
                invoker->execute(toRemove, mainInventory);
                delete cmd;

                printSuccess("Item removed!");
            }
            pressEnter();
            break;
        }

        case 3: { // checkout — interactive state flow
            if (!currentCustomer) currentCustomer = new Customer("Guest");
            if (!salesContext)
                salesContext = new SalesContext(BrowsingState::instance(), *currentCustomer);

            PlantInventory* cart = currentCustomer->getCart();
            const int plantCount = Local::countPlants(cart);
            const int arrCount   = static_cast<int>(inventory->cartArrangementsSnapshot().size());
            const int count      = plantCount + arrCount;

            if (count == 0) {
                printError("Cart is empty!");
                pressEnter();
                break;
            }

            const double total = calculateCartTotal();

            clearScreen();
            printSubHeader("CHECKOUT");
            std::cout << " Items: " << count << "\n";
            std::cout << " Total: R" << total << "\n\n";

            std::cout << " Confirm purchase? (1=Yes, 0=No): ";
            int confirm = getValidatedInput(0, 1);
            if (!confirm) {
                std::cout << "\n Purchase cancelled.\n";
                pressEnter();
                break;
            }

            // Ensure we’re in CartOpen and move to PendingPayment
            salesContext->setState(CartOpenState::instance());
            salesContext->eventCheckout(); // CartOpen -> PendingPayment
            if (Local::stateName(salesContext) != "PendingPayment") {
                printError("Could not move to PendingPayment.");
                pressEnter();
                break;
            }

            bool finished = false;
            bool success  = false;

            while (!finished) {
                const std::string s = Local::stateName(salesContext);

                if (s == "PendingPayment") {
                    std::cout << "\n Authorize payment? (1=Yes, 0=No): ";
                    int authYes = getValidatedInput(0, 1);
#ifdef SUPPORT_TEST_TOGGLES
                    salesContext->forceNextAuth(authYes == 1);
#endif
                    salesContext->eventAuthorize();

                    const std::string afterAuth = Local::stateName(salesContext);
                    if (afterAuth == "PaymentFailed") {
                        std::cout << "\n Authorization failed. Retry? (1=Yes, 0=No): ";
                        int retry = getValidatedInput(0, 1);
                        if (retry == 1) {
                            salesContext->eventRetry(); // -> PendingPayment
                            continue;
                        } else {
                            finished = true;  // leave cart unchanged
                        }
                    }
                    // else either PaymentAuthorized or (in some implementations) Completed
                    continue;
                }

                if (s == "PaymentAuthorized") {
                    std::cout << "\n Capture & complete order now? (1=Yes, 0=No): ";
                    int cap = getValidatedInput(0, 1);
                    if (cap == 0) {
                        std::cout << " Cancel the order? (1=Yes, 0=No): ";
                        int cancel = getValidatedInput(0, 1);
                        if (cancel == 1) {
                            salesContext->eventCancel(); // -> Cancelled
                            finished = true;
                        }
                        else {
                            // stay authorized; user can decide again
                        }
                        continue;
                    }

#ifdef SUPPORT_TEST_TOGGLES
                    // Ask if user wants to simulate a capture failure
                    std::cout << " Simulate capture failure? (1=Yes, 0=No): ";
                    int failCap = getValidatedInput(0, 1);
                    salesContext->forceNextCapture(failCap == 0); // true = succeed
                    // if you prefer “true means succeed”, keep as above.
#endif
                    salesContext->eventCommit(); // -> Completed or PaymentFailed
                    continue;
                }

                if (s == "PaymentFailed") {
                    std::cout << "\n Payment failed. Retry full payment? (1=Yes, 0=No): ";
                    int retry = getValidatedInput(0, 1);
                    if (retry == 1) {
                        salesContext->eventRetry(); // -> PendingPayment
                        continue;
                    } else {
                        finished = true;
                        continue;
                    }
                }

                if (s == "Completed") {
                    success  = true;
                    finished = true;
                    continue;
                }

                if (s == "Cancelled") {
                    finished = true;
                    continue;
                }

                // Any other state: exit safety
                finished = true;
            }

            if (success) {
                // Clear cart (plants + arrangements)
                std::vector<Plant*> toRemove;
                { CartIterator it(cart); for (it.first(); !it.isDone(); it.next())
                        toRemove.push_back(it.currentItem()); }
                PlantInventory* mainInventory = currentCustomer->getInven();
                for (Plant* p : toRemove) {
                    CustomerCommand* removeCmd = new RemoveFromCart();
                    invoker->setCommand(removeCmd);
                    invoker->execute(p, mainInventory);
                    delete removeCmd;
                }
                inventory->clearCartArrangements();

                printSuccess("Purchase complete! Thank you!");
            } else {
                std::cout << "\n Payment was not completed. Your cart is unchanged.\n";
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
    int line = 1;

    std::cout << "\n┌─── YOUR CART ────────────────────────┐\n";

    // --- Plants ---
    int plantCount = 0;
    for (cartIt.first(); !cartIt.isDone(); cartIt.next()) {
        isEmpty = false;
        Plant* p = cartIt.currentItem();
        std::cout << "│ " << line++ << ". " << std::setw(20) << p->getName()
                  << " R" << std::setw(6) << p->getPrice() << " │\n";
        total += p->getPrice();
        ++plantCount;
    }

    // --- Arrangements (NEW) ---
    const auto arr = inventory->cartArrangementsSnapshot();
    for (std::size_t i = 0; i < arr.size(); ++i) {
        const Item* it = arr[i];
        if (!it) continue;
        isEmpty = false;
        std::cout << "│ " << line++ << ". " 
                  << std::setw(20) << it->describe()
                  << " R" << std::setw(6) << it->priceFunc()
                  << " │  [ARR]\n";
        total += it->priceFunc();
    }

    if (isEmpty) {
        std::cout << "│  Cart is empty                       │\n";
    } else {
        std::cout << "├──────────────────────────────────────┤\n";
        std::cout << "│  Total: R" << std::setw(26) << total << " │\n";
    }
    std::cout << "└──────────────────────────────────────┘\n";
}


// ============================================================================
// FIXED calculateCartTotal() - Replace in CompleteNurseryUI.cpp
// ============================================================================

double CompleteNurseryUI::calculateCartTotal() {
    double total = 0.0;

    // Plants
    CartIterator cartIt(currentCustomer->getCart());
    for (cartIt.first(); !cartIt.isDone(); cartIt.next()) {
        total += cartIt.currentItem()->getPrice();
    }

    // Arrangements
    const auto arr = inventory->cartArrangementsSnapshot();
    for (const Item* it : arr) {
        if (it) total += it->priceFunc();
    }
    return total;
}

// Recommendation Menu (Strategy Pattern)
void CompleteNurseryUI::showRecommendationMenu() {
    while(true){
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
            clearScreen();
            strategyContext->setRecommStrategy(new DefaultRecomm());
            strategyContext->executeRecommStrategy();
            pressEnter();
            break;
        case 2:
            clearScreen();
            strategyContext->setRecommStrategy(new WaterRecomm());
            strategyContext->executeRecommStrategy();
            pressEnter();
            break;
        case 3:
            clearScreen();
            strategyContext->setRecommStrategy(new SunlightRecomm());
            strategyContext->executeRecommStrategy();
            pressEnter();
            break;
    }
   // pressEnter();
}
}

// Pricing Menu (Strategy Pattern for pricing)
void CompleteNurseryUI::showPricingMenu() {
    while (true) {
        clearScreen();
        printHeader("💰 PRICING OPTIONS");

        if (!currentCustomer) {
            printError("Please sign in as a customer first!");
            pressEnter();
            return;
        }

        // Calculate cart count and total
        CartIterator cartIt(currentCustomer->getCart());
        int itemCount = 0;
        for (cartIt.first(); !cartIt.isDone(); cartIt.next()) itemCount++;
        double cartTotal = calculateCartTotal();

        std::cout << "\n Cart items: " << itemCount << "\n";
        std::cout << " Current total: R" << cartTotal << "\n";

        if (itemCount == 0) {
            printError("Your cart is empty! Add items before pricing.");
            pressEnter();
            return;
        }

        std::cout << "\n 1. Regular Pricing\n";
        std::cout << " 2. Bulk Discount (10+ items)\n";
        std::cout << " 3. Promotional (enter code)\n";
        std::cout << " 0. Back\n\n";

        std::cout << " Enter choice: ";
        int choice = getValidatedInput(0, 3);

        if (choice == 0) return;

        std::cout << "\n";
        switch (choice) {
            case 1: {
                // Regular pricing – no discounts; we treat cartTotal as the base
                strategyContext->setPricingStrategy(new RegularPrice());
                double total = strategyContext->executePricingStrategy(1, cartTotal, "");
                std::cout << " Regular total: R" << total << "\n";
                break;
            }
            case 2: {
                // Bulk: needs 10+ items
                if (itemCount >= 10) {
                    strategyContext->setPricingStrategy(new BulkDiscount());
                    double discounted = strategyContext->executePricingStrategy(itemCount, cartTotal, "");
                    std::cout << " Items: " << itemCount << "\n";
                    std::cout << " Discounted total: R" << discounted << "\n";
                    std::cout << " You save: R" << (cartTotal - discounted) << "\n";
                } else {
                    int needed = 10 - itemCount;
                    std::cout << " Bulk discount applies at 10+ items. Add " << needed
                              << " more item" << (needed == 1 ? "" : "s") << " to qualify." << "\n";
                }
                break;
            }
            case 3: {
                // Promotional – prompt for a code
                std::string code;
                std::cout << " Enter promo code: ";
                std::getline(std::cin, code);

                strategyContext->setPricingStrategy(new Promotional());
                double promoTotal = strategyContext->executePricingStrategy(itemCount, cartTotal, code);
                std::cout << " Total after promo: R" << promoTotal << "\n";
                std::cout << " You save: R" << (cartTotal - promoTotal) << "\n";
                break;
            }
        }
        pressEnter();
    }
}

// Help Menu (Chain of Responsibility)
void CompleteNurseryUI::showHelpMenu() {
    while(true){
    try {
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
        
        if (question.empty()) {
            printError("Question cannot be empty!");
            pressEnter();
            return;
        }
        
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
        
        if (customerQueryChain == nullptr) {
            printError("Customer service system is not initialized!");
            pressEnter();
            return;
        }
        
        customerQueryChain->handleQuery(query);
        pressEnter();
    } catch (const std::exception& e) {
        printError("An error occurred: " + std::string(e.what()));
        pressEnter();
    } catch (...) {
        printError("An unexpected error occurred");
        pressEnter();
    }
    }
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
                int staffChoice;
                do {
                    clearScreen();
                    printSubHeader("NURSERY STAFF MANAGEMENT");
                    std::cout << "\n1. View All Staff\n";
                    std::cout << "2. Add New Staff\n";
                    std::cout << "3. Remove Staff\n";
                    std::cout << "4. Back to Main Menu\n";
                    std::cout << "\nChoose option: ";
                    
                    staffChoice = getValidatedInput(1, 5);
                    
                    switch (staffChoice) {
                        case 1: {
                            clearScreen();
                            printSubHeader("ALL NURSERY STAFF");
                            std::cout << "\n";
                            if (nurseryStaff.empty()) {
                                std::cout << " No staff members found.\n";
                            } else {
                                for (size_t i = 0; i < nurseryStaff.size(); i++) {
                                    std::cout << " " << (i + 1) << ". " << nurseryStaff[i]->getName()
                                            << " - " << nurseryStaff[i]->getRole() 
                                            << " (ID: " << nurseryStaff[i]->getId() << ")\n";
                                }
                                std::cout << "\n Total staff: " << nurseryStaff.size() << "\n";
                            }
                            pressEnter();
                            break;
                        }
                        
                        case 2: {
                            clearScreen();
                            printSubHeader("ADD NEW STAFF MEMBER");
                            
                            std::cout << "\nSelect staff type:\n";
                            std::cout << "1. Gardener (ID: 1000+)\n";
                            std::cout << "2. Sales Assistant (ID: 2000+)\n";
                            std::cout << "3. Manager (ID: 3000+)\n";
                            std::cout << "4. Delivery Staff (ID: 4000+)\n";
                            std::cout << "5. Cancel\n";
                            std::cout << "\nChoose staff type: ";
                            
                            int staffType = getValidatedInput(1, 5);
                            if (staffType == 5) break;
                            
                            StaffFactory* factory = nullptr;
                            std::string roleName;
                            
                            switch (staffType) {
                                case 1: 
                                    factory = new GardenerFactory(); 
                                    roleName = "Gardener";
                                    break;
                                case 2: 
                                    factory = new SalesAssistantFactory(); 
                                    roleName = "Sales Assistant";
                                    break;
                                case 3: 
                                    factory = new ManagerFactory(); 
                                    roleName = "Manager";
                                    break;
                                case 4: 
                                    factory = new DeliveryStaffFactory(); 
                                    roleName = "Delivery Staff";
                                    break;
                            }
                            
                            if (factory) {
                                Staff* newStaff = factory->createStaff();
                                nurseryStaff.push_back(newStaff);
                                std::cout << "\n  Successfully added:\n";
                                std::cout << "    Name: " << newStaff->getName() << "\n";
                                std::cout << "    Role: " << roleName << "\n";
                                std::cout << "    ID: " << newStaff->getId() << "\n";
                                delete factory;
                            } else {
                                std::cout << "\n Failed to create staff member.\n";
                            }
                            
                            pressEnter();
                            break;
                        }
                        
                        case 3: {
                            clearScreen();
                            printSubHeader("REMOVE STAFF MEMBER");
                            
                            if (nurseryStaff.empty()) {
                                std::cout << " No staff members to remove.\n";
                                pressEnter();
                                break;
                            }
                            
                            std::cout << "\nSelect staff to remove:\n";
                            for (size_t i = 0; i < nurseryStaff.size(); i++) {
                                std::cout << " " << (i + 1) << ". " << nurseryStaff[i]->getName()
                                        << " - " << nurseryStaff[i]->getRole() 
                                        << " (ID: " << nurseryStaff[i]->getId() << ")\n";
                            }
                            std::cout << " " << (nurseryStaff.size() + 1) << ". Cancel\n";
                            std::cout << "\nChoose staff to remove: ";
                            
                            int removeChoice = getValidatedInput(1, static_cast<int>(nurseryStaff.size()) + 1);
                            
                            if (removeChoice == static_cast<int>(nurseryStaff.size()) + 1) {
                                break;
                            }
                            
                            size_t index = removeChoice - 1;
                            std::cout << "\nAre you sure you want to remove:\n";
                            std::cout << "  Name: " << nurseryStaff[index]->getName() << "\n";
                            std::cout << "  Role: " << nurseryStaff[index]->getRole() << "\n";
                            std::cout << "  ID: " << nurseryStaff[index]->getId() << "\n";
                            std::cout << "\nThis action cannot be undone! (y/n): ";
                            
                            char confirm;
                            std::cin >> confirm;
                            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                            
                            if (confirm == 'y' || confirm == 'Y') {
                                std::string removedName = nurseryStaff[index]->getName();
                                std::string removedRole = nurseryStaff[index]->getRole();
                                
                                delete nurseryStaff[index];
                                nurseryStaff.erase(nurseryStaff.begin() + index);
                                
                                std::cout << "\n Successfully removed " << removedName 
                                        << " (" << removedRole << ")\n";
                            } else {
                                std::cout << "\n Removal cancelled.\n";
                            }
                            
                            pressEnter();
                            break;
                        }
                        case 4:
                            break;
                    }
                } while (staffChoice != 4);
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
            std::cout << selectedPlant->getCareInstructions() << "\n\n";
            if (dynamic_cast<Rose*>(selectedPlant)) {
                Rose* plant = dynamic_cast<Rose*>(selectedPlant);
                std::cout << " Water range: " << plant->getMinWater() << "L - " << plant->getMaxWater() << "L (Optimal: " << plant->getOptimalWater() << "L)\n\n";
            }
            else if (dynamic_cast<Lotus*>(selectedPlant)) {
                Lotus* plant = dynamic_cast<Lotus*>(selectedPlant);
                std::cout << " Water range: " << plant->getMinWater() << "L - " << plant->getMaxWater() << "L (Optimal: " << plant->getOptimalWater() << "L)\n\n";
            }
            else if (dynamic_cast<Protea*>(selectedPlant)) {
                Protea* plant = dynamic_cast<Protea*>(selectedPlant);
                std::cout << " Water range: " << plant->getMinWater() << "L - " << plant->getMaxWater() << "L (Optimal: " << plant->getOptimalWater() << "L)\n\n";
            }
            else if (dynamic_cast<Cacti*>(selectedPlant)) {
                Cacti* plant = dynamic_cast<Cacti*>(selectedPlant);
                std::cout << " Water range: " << plant->getMinWater() << "L - " << plant->getMaxWater() << "L (Optimal: " << plant->getOptimalWater() << "L)\n\n";
            }
            else if (dynamic_cast<Jade*>(selectedPlant)) {
                Jade* plant = dynamic_cast<Jade*>(selectedPlant);
                std::cout << " Water range: " << plant->getMinWater() << "L - " << plant->getMaxWater() << "L (Optimal: " << plant->getOptimalWater() << "L)\n\n";
            }
            else if (dynamic_cast<Orchid*>(selectedPlant)) {
                Orchid* plant = dynamic_cast<Orchid*>(selectedPlant);
                std::cout << " Water range: " << plant->getMinWater() << "L - " << plant->getMaxWater() << "L (Optimal: " << plant->getOptimalWater() << "L)\n\n";
            }
            else if (dynamic_cast<Apple*>(selectedPlant)) {
                Apple* plant = dynamic_cast<Apple*>(selectedPlant);
                std::cout << " Water range: " << plant->getMinWater() << "L - " << plant->getMaxWater() << "L (Optimal: " << plant->getOptimalWater() << "L)\n\n";
            }
            else if (dynamic_cast<Jacaranda*>(selectedPlant)) {
                Jacaranda* plant = dynamic_cast<Jacaranda*>(selectedPlant);
                std::cout << " Water range: " << plant->getMinWater() << "L - " << plant->getMaxWater() << "L (Optimal: " << plant->getOptimalWater() << "L)\n\n";
            }
            else if (dynamic_cast<Pine*>(selectedPlant)) {
                Pine* plant = dynamic_cast<Pine*>(selectedPlant);
                std::cout << " Water range: " << plant->getMinWater() << "L - " << plant->getMaxWater() << "L (Optimal: " << plant->getOptimalWater() << "L)\n\n";
            }
            std::cout << " Water amount (liters): ";
            std::cin >> amount;
            WaterCommand waterCmd(selectedPlant, amount);
            //std::cout << "\n " << waterCmd.getDescription() << "\n";
            waterCmd.execute();
            printSuccess("Plant watered!");
            break;
        }
        case 2: {
            std::string type;
            std::cout << " " << selectedPlant->getCareInstructions() << "\n\n";
            std::cout << " Fertilizer type: ";
            //std::cin.ignore();
            std::getline(std::cin, type);
            FertilizeCommand fertilizeCmd(selectedPlant, type);
            //std::cout << "\n " << fertilizeCmd.getDescription() << "\n";
            fertilizeCmd.execute();
            printSuccess("Plant fertilized!");
            break;
        }
        case 3: {
            int branches;
            std::cout << " " << selectedPlant->getCareInstructions() << "\n\n";
            std::cout << " Intensity to prune: ";
            std::cin >> branches;
            PruneCommand pruneCmd(selectedPlant, branches);
            //std::cout << "\n " << pruneCmd.getDescription() << "\n";
            pruneCmd.execute();
            printSuccess("Plant pruned!");
            break;
        }
        case 4: {
            int hours;
            std::string intensity;
            std::cout << " " << selectedPlant->getCareInstructions() << "\n\n";
            std::cout << " Hours of sunlight: ";
            std::cin >> hours;
            std::cout << " Intensity (low/medium/high): ";
            std::cin >> intensity;
            SunlightCommand sunCmd(selectedPlant, hours, intensity);
            //std::cout << "\n " << sunCmd.getDescription() << "\n";
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
    std::cout << " 4. Clear Specific Task\n";
    std::cout << " 5. View Tasks\n";
    std::cout << " 0. Back\n\n";
    
    std::cout << " Enter choice: ";
    int choice = getValidatedInput(0, 5);
    
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
        case 4: {
            std::cout << "\n";
            selectedStaff->listTasks();
            
            int taskCount = selectedStaff->getTaskCount();
            
            if (taskCount == 0) {
                std::cout << "No tasks to delete.\n";
                break;
            }
            
            std::cout << "\n Enter task number to delete (0 to cancel): ";
            int taskNum = getValidatedInput(0, taskCount);
            
            if (taskNum == 0) {
                std::cout << "Cancelled.\n";
            } else {
                selectedStaff->clearTask(taskNum - 1);
            }
            break;
        }
        case 5:
            std::cout << "\n";
            selectedStaff->listTasks();
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

//Stock Management Menu(Kiolin's Factory/Composite)
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

    // Age the plant; transitions will be handled inside ageState
    growingPlants[sel - 1]->ageState(days);

    printSuccess("Plant aged " + std::to_string(days) + " days!");
    std::cout << " New age: " << growingPlants[sel - 1]->getAge() << " days\n";
    std::cout << " Current State: " << growingPlants[sel - 1]->getCurrentStateName() << "\n";

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
    PlantContext* p = growingPlants[sel - 1];

    // Attempt to harvest; states handle whether it can be harvested
    bool harvested = p->harvest();

    if (harvested) {
        printSuccess("Plant harvested successfully!");
    } else {
        printError("Plant is not ready for harvest yet.");
    }

    std::cout << " State: " << p->getCurrentStateName() << "\n";
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
                std::cout << " Type: " << p->getPlant()->getPlantType() << "\n";
                std::cout << " Species: " << p->getSpecies() << "\n";
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
///Taskeens Builder State and Decorator

// Personalization Menu (Builder + Decorator patterns) — all decorations FREE
void CompleteNurseryUI::personalizeSelectedPlant(Plant* plant) {
    clearScreen();
    printHeader("🎨 PERSONALIZE YOUR PLANT");

    std::cout << "\n Selected: " << plant->getName()
              << " (R" << plant->getPrice() << ")\n";
    printSubHeader("DECORATION OPTIONS");

    std::cout << " 1. Add Decorative Pot (choose color)\n";
    std::cout << " 2. Add Gift Wrap (bouquet style, choose color; no message)\n";
    std::cout << " 3. Add Personal Note (choose color + message)\n";
    std::cout << " 4. View Available Options\n";
    std::cout << " 0. Done\n\n";

    // current session selections (not flags)
    std::string potColor, wrapColor, noteColor, noteText;

    auto eat_pending_newline = [](){
        if (std::cin.peek() == '\n') std::cin.get();
    };

    while (true) {
        std::cout << " Enter choice (0 when done): ";
        int choice = getValidatedInput(0, 4);
        if (choice == 0) {
            printSuccess("Personalization complete!");
            // TODO: persist potColor / wrapColor / noteColor+noteText
            //       into your add-to-cart builder flow if you want them applied.
            break;
        }

        switch (choice) {
            case 1: { // Pot (FREE)
                const auto& pots = inventory->getPots();
                if (pots.empty()) { printError("No pot colors available."); break; }

                std::cout << "\n Available Pot Colors:\n";
                for (size_t i = 0; i < pots.size(); ++i)
                    std::cout << "  " << (i + 1) << ". " << pots[i] << "\n";

                std::cout << "\n Select pot color (0 to skip): ";
                int ix = getValidatedInput(0, static_cast<int>(pots.size()));
                if (ix == 0) {
                    potColor.clear();
                    std::cout << " Skipped pot.\n";
                } else {
                    potColor = pots[static_cast<size_t>(ix - 1)];
                    std::cout << " ✓ Decorative pot '" << potColor << "' selected (FREE)\n";
                }
                break;
            }

            case 2: { // Wrap (FREE, no message)
                const auto& wraps = inventory->getGiftWraps();
                if (wraps.empty()) { printError("No gift wrap colors available."); break; }

                std::cout << "\n Available Gift Wrap Colors:\n";
                for (size_t i = 0; i < wraps.size(); ++i)
                    std::cout << "  " << (i + 1) << ". " << wraps[i] << "\n";

                std::cout << "\n Select wrap color (0 to skip): ";
                int ix = getValidatedInput(0, static_cast<int>(wraps.size()));
                if (ix == 0) {
                    wrapColor.clear();
                    std::cout << " Skipped wrap.\n";
                } else {
                    wrapColor = wraps[static_cast<size_t>(ix - 1)];
                    std::cout << " ✓ Bouquet-style gift wrap '" << wrapColor << "' selected (FREE)\n";
                }
                break;
            }

            case 3: { // Note (FREE; color + message)
                const auto& notes = inventory->getNotes();
                if (notes.empty()) { printError("No note colors available."); break; }

                std::cout << "\n Available Note Colors:\n";
                for (size_t i = 0; i < notes.size(); ++i)
                    std::cout << "  " << (i + 1) << ". " << notes[i] << "\n";

                std::cout << "\n Select note color (0 to skip): ";
                int ix = getValidatedInput(0, static_cast<int>(notes.size()));
                if (ix == 0) {
                    noteColor.clear();
                    noteText.clear();
                    std::cout << " Skipped note.\n";
                    break;
                }

                noteColor = notes[static_cast<size_t>(ix - 1)];

                std::cout << "\n Enter note text (leave blank to skip): ";
                eat_pending_newline();
                std::getline(std::cin, noteText);
                if (!noteText.empty() && noteText.back() == '\r') noteText.pop_back();

                if (noteText.empty()) {
                    noteColor.clear();
                    std::cout << " Skipped note.\n";
                } else {
                    std::cout << " ✓ Note added (FREE)\n";
                }
                break;
            }

            case 4: { // View all options
                clearScreen();
                printSubHeader("Available Decoration Options");
                std::cout << "\n🎁 Gift Wrap Colors:\n";
                for (const auto& c : inventory->getGiftWraps()) std::cout << "  • " << c << "\n";
                std::cout << "\n🪴 Pot Colors:\n";
                for (const auto& c : inventory->getPots()) std::cout << "  • " << c << "\n";
                std::cout << "\n📝 Note Colors:\n";
                for (const auto& c : inventory->getNotes()) std::cout << "  • " << c << "\n";
                std::cout << "\n";
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