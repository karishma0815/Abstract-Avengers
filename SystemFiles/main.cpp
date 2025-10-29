/*Abstract Avengers*/

/*
Demonstrates:
  Personalization: Builder, Decorator, Prototype
  Customer Browsing & Checkout: State (incl. assistance, OOS, failure/retry)
*/

/*#include <iostream>
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

static void printHeader(const std::string& title) {
  std::cout << "\n===\n" << title << "\n===\n";
}

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
      director.buildGift(*roseProto, *potExtra/25.0, "Red",
                                   *wrapExtra/15.0, "Happy Birthday!");

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

  std::cout << "\n All scenarios executed.\n";
  return 0;
}
*/



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

int main() {
    simulateCustomerBrowsing();
    simulateCommandPatternScenario();
    simulateStrategyPatternScenario();
    std::cout<<"Testing modifications made in the terminal\n";   
    return 0;
}
