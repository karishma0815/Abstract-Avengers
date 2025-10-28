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
  //rene start
  void printSeparator(const std::string& title = "") {
        std::cout << "\n" << std::string(60, '=') << std::endl;
        if (!title.empty()) {
            std::cout << "  " << title << std::endl;
            std::cout << std::string(60, '=') << std::endl;
        }
    }

  void printPlantInfo(PlantContext* context) {
      std::cout << "\n--- Plant Information ---" << std::endl;
      std::cout << "Plant Type: " << context->getPlantType() << std::endl;
      std::cout << "Plant Name: " << context->getPlantName() << std::endl;
      std::cout << "Current State: " << context->getCurrentStateName() << std::endl;
      std::cout << "Age (days): " << context->getAge() << std::endl;
      std::cout << "Season: " << context->getSeason() << std::endl;
      std::cout << "Ready for Sale: " << (context->isReadyForSale() ? "Yes" : "No") << std::endl;
      
      Plant* plant = context->getPlant();
      std::cout << "\nPlant Details:" << std::endl;
      std::cout << "  - Plant ID: " << plant->getPlantID() << std::endl;
      std::cout << "  - Fertilized: " << (plant->isFertilized() ? "Yes" : "No") << std::endl;
      std::cout << "  - Sunlight Hours: " << plant->getExposureSunlightHours() << std::endl;
      std::cout << "  - Water Level: " << plant->getLastWaterLevel() << std::endl;
      std::cout << std::string(25, '-') << std::endl;
  }

  void demonstratePlantClass() {
      printSeparator("PLANT CLASS DEMONSTRATION");
      
      std::cout << "\nCreating a Succulent plant..." << std::endl;
      Plant succulent("Succulent", false, "SUCC001", 8, 3,50);
      
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
      PlantContext* flower = new PlantContext("Flower", "Spring", "", 15.50);
      
      printPlantInfo(flower);
      
      // Seedling State
      std::cout << "\n>>> SEEDLING PHASE <<<" << std::endl;
      std::cout << "Checking readiness..." << std::endl;
      flower->checkReadiness();
      
      std::cout << "\nSetting up seedling for growth..." << std::endl;
      SeedlingState* seedling = dynamic_cast<SeedlingState*>(flower->getState());
      if (seedling) {
          seedling->setMinDaysInState(7);
          seedling->setHasReceivedProperCare(true);
          std::cout << "Required days in seedling state: " << seedling->getRequiredDaysInState() << std::endl;
      }
      
      std::cout << "\nGrowing for 7 days..." << std::endl;
      flower->ageState(7);
      printPlantInfo(flower);
      
      // Flowering State
      std::cout << "\n>>> FLOWERING PHASE <<<" << std::endl;
      flower->checkReadiness();
      
      FloweringState* flowering = dynamic_cast<FloweringState*>(flower->getState());
      if (flowering) {
          flowering->setRequestDays(14);
          flowering->setIsInSeason(true);
          flowering->setFloweringStrtSeason("Spring");
          std::cout << "Plant is flowering, in season: " << (flowering->getIsInSeason() ? "Yes" : "No") << std::endl;
      }
      
      std::cout << "\nGrowing for 14 days..." << std::endl;
      flower->ageState(14);
      printPlantInfo(flower);
      
      // Mature State
      std::cout << "\n>>> MATURE PHASE <<<" << std::endl;
      flower->checkReadiness();
      
      MatureState* mature = dynamic_cast<MatureState*>(flower->getState());
      if (mature) {
          mature->setIsInInSeason(true);
          mature->setMaturedStateSeason("Spring");
      }
      
      std::cout << "\nGrowing for 30 days to reach prime for sale..." << std::endl;
      flower->ageState(30);
      
      if (mature) {
          std::cout << "Prime for sale: " << (mature->getIsPrimeForSale() ? "Yes" : "No") << std::endl;
          std::cout << "Sale readiness: " << mature->evaluateSaleReadiness(30) << std::endl;
      }
      
      printPlantInfo(flower);
      
      // Ready for Sale State
      std::cout << "\n>>> HARVESTING <<<" << std::endl;
      std::cout << "Attempting to harvest..." << std::endl;
      flower->harvest();
      printPlantInfo(flower);
      
      ReadyForSaleState* ready = dynamic_cast<ReadyForSaleState*>(flower->getState());
      if (ready) {
          ready->setPrice(25.99);
          ready->setSeason("Spring");
          std::cout << "\nPreparing for sale..." << std::endl;
          std::string saleInfo = ready->prepareSaleForSale(25.99, "Spring");
          std::cout << saleInfo << std::endl;
          std::cout << "Current price: R" << ready->getPrice() << std::endl;
      }
      
      // Sold State
      std::cout << "\n>>> SELLING PLANT <<<" << std::endl;
      std::cout << "Selling the plant..." << std::endl;
      flower->harvest();
      printPlantInfo(flower);
      
      SoldState* sold = dynamic_cast<SoldState*>(flower->getState());
      if (sold) {
          sold->soldSequence(25.99, "2025-10-25", "Spring");
          std::cout << "\nSale details: " << sold->getData() << std::endl;
      }
      
      delete flower;
  }

  void demonstrateMultiplePlants() {
      printSeparator("MULTIPLE PLANTS DEMONSTRATION");
      
      std::cout << "\nCreating multiple plants with different characteristics..." << std::endl;
      
      PlantContext* flower = new PlantContext("Flower", "Summer", "", 30.00);
      PlantContext* tree = new PlantContext("Tree", "Winter", "", 45.00);
      PlantContext* succulent = new PlantContext("Succulent", "Spring", "", 12.00);
      
      std::cout << "\n--- Flower ---" << std::endl;
      std::cout << "Type: " << flower->getPlantType() << ", Season: " << flower->getSeason() 
                << ", State: " << flower->getCurrentStateName() << std::endl;
      
      std::cout << "\n--- Tree ---" << std::endl;
      std::cout << "Type: " << tree->getPlantType() << ", Season: " << tree->getSeason() 
                << ", State: " << tree->getCurrentStateName() << std::endl;
      
      std::cout << "\n--- Succulent ---" << std::endl;
      std::cout << "Type: " << succulent->getPlantType() << ", Season: " << succulent->getSeason() 
                << ", State: " << succulent->getCurrentStateName() << std::endl;
      
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
      PlantContext* tree = new PlantContext("Tree", "Summer", "", 18.50);
      
      printPlantInfo(tree);
      
      std::cout << "\n>>> Attempting to harvest too early <<<" << std::endl;
      std::cout << "Trying to harvest a seedling..." << std::endl;
      tree->harvest();
      
      std::cout << "\nGrowing to flowering stage..." << std::endl;
      SeedlingState* seedling = dynamic_cast<SeedlingState*>(tree->getState());
      if (seedling) {
          seedling->setMinDaysInState(5);
          seedling->setHasReceivedProperCare(true);
      }
      tree->ageState(5);
      
      std::cout << "\nTrying to harvest during flowering..." << std::endl;
      tree->harvest();
      
      delete tree;
  }

  void interactiveMenu() {
      printSeparator("INTERACTIVE PLANT MANAGER");
      
      PlantContext* myPlant = nullptr;
      int choice;
      
      do {
          std::cout << "\n--- Plant Management Menu ---" << std::endl;
          std::cout << "1. Create a new plant" << std::endl;
          std::cout << "2. View plant information" << std::endl;
          std::cout << "3. Age plant (grow)" << std::endl;
          std::cout << "4. Check readiness" << std::endl;
          std::cout << "5. Harvest plant" << std::endl;
          std::cout << "6. Setup state parameters" << std::endl;
          std::cout << "0. Exit interactive mode" << std::endl;
          std::cout << "\nEnter choice: ";
          std::cin >> choice;
          
          switch (choice) {
              case 1: {
                  if (myPlant != nullptr) {
                      delete myPlant;
                  }
                  
                  std::string type, season;
                  double price;
                  
                  std::cout << "\nEnter plant type (Flower/Tree/Succulent): ";
                  std::cin >> type;
                  std::cout << "Enter season (Spring/Summer/Fall/Winter): ";
                  std::cin >> season;
                  std::cout << "Enter price: R";
                  std::cin >> price;
                  
                  myPlant = new PlantContext(type, season, "", price);
                  std::cout << "\n Plant created successfully!" << std::endl;
                  break;
              }
              
              case 2:
                  if (myPlant != nullptr) {
                      printPlantInfo(myPlant);
                  } else {
                      std::cout << "\n No plant created yet!" << std::endl;
                  }
                  break;
              
              case 3: {
                  if (myPlant != nullptr) {
                      int days;
                      std::cout << "\nEnter number of days to grow: ";
                      std::cin >> days;
                      myPlant->ageState(days);
                      std::cout << " Plant aged by " << days << " days" << std::endl;
                  } else {
                      std::cout << "\n No plant created yet!" << std::endl;
                  }
                  break;
              }
              
              case 4:
                  if (myPlant != nullptr) {
                      std::cout << std::endl;
                      myPlant->checkReadiness();
                  } else {
                      std::cout << "\n No plant created yet!" << std::endl;
                  }
                  break;
              
              case 5:
                  if (myPlant != nullptr) {
                      std::cout << std::endl;
                      myPlant->harvest();
                  } else {
                      std::cout << "\n No plant created yet!" << std::endl;
                  }
                  break;
              
              case 6:
                  if (myPlant != nullptr) {
                      std::string state = myPlant->getCurrentStateName();
                      std::cout << "\nCurrent state: " << state << std::endl;
                      
                      if (state == "Seedling") {
                          SeedlingState* s = dynamic_cast<SeedlingState*>(myPlant->getState());
                          if (s) {
                              int minDays;
                              char care;
                              std::cout << "Set minimum days in state: ";
                              std::cin >> minDays;
                              std::cout << "Has received proper care? (y/n): ";
                              std::cin >> care;
                              s->setMinDaysInState(minDays);
                              s->setHasReceivedProperCare(care == 'y' || care == 'Y');
                              std::cout << " Parameters set!" << std::endl;
                          }
                      } else if (state == "Flowering") {
                          FloweringState* f = dynamic_cast<FloweringState*>(myPlant->getState());
                          if (f) {
                              int reqDays;
                              char season;
                              std::cout << "Set required days: ";
                              std::cin >> reqDays;
                              std::cout << "Is in season? (y/n): ";
                              std::cin >> season;
                              f->setRequestDays(reqDays);
                              f->setIsInSeason(season == 'y' || season == 'Y');
                              std::cout << " Parameters set!" << std::endl;
                          }
                      } else if (state == "Mature") {
                          MatureState* m = dynamic_cast<MatureState*>(myPlant->getState());
                          if (m) {
                              char season;
                              std::cout << "Is in season? (y/n): ";
                              std::cin >> season;
                              m->setIsInInSeason(season == 'y' || season == 'Y');
                              std::cout << " Parameters set!" << std::endl;
                          }
                      } else if (state == "Ready for Sale") {
                          ReadyForSaleState* r = dynamic_cast<ReadyForSaleState*>(myPlant->getState());
                          if (r) {
                              double price;
                              std::cout << "Set sale price: $";
                              std::cin >> price;
                              r->setPrice(price);
                              std::cout << " Price set!" << std::endl;
                          }
                      }
                  } else {
                      std::cout << "\n No plant created yet!" << std::endl;
                  }
                  break;
              
              case 0:
                  std::cout << "\nExiting interactive mode..." << std::endl;
                  break;
              
              default:
                  std::cout << "\n Invalid choice!" << std::endl;
          }
          
      } while (choice != 0);
      
      if (myPlant != nullptr) {
          delete myPlant;
      }
  }
//rene end

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
    return 0;
  }
