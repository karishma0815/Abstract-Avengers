
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
    Plant succulent("Succulent", false, "SUCC001", 8, 3);
    
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

int main() {
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
    
    return 0;
}