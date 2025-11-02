// CompleteNurseryUI.h
#ifndef COMPLETENURSERYUI_H
#define COMPLETENURSERYUI_H

#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <limits>

// All includes from all team members
#include "PlantInventory.h"
#include "Customer.h"
#include "Plant.h"
#include "Rose.h"
#include "Cacti.h"
#include "Jade.h"
#include "Succulent.h"
#include "Lotus.h"
#include "Protea.h"
#include "Orchid.h"
#include "Apple.h"
#include "Jacaranda.h"
#include "Pine.h"

// Iterator patterns (Sabira)
#include "PlantIterator.h"
#include "PriceRangeIterator.h"
#include "CareIterator.h"
#include "CartIterator.h"

// Command patterns (Sabira + Karishma)
#include "Invoker.h"
#include "AddToCart.h"
#include "RemoveFromCart.h"
#include "WaterCommand.h"
#include "FertilizeCommand.h"
#include "PruneCommand.h"
#include "SunlightCommand.h"

// Strategy patterns (Sabira)
#include "StratContext.h"
#include "RegularPrice.h"
#include "BulkDiscount.h"
#include "DefaultRecomm.h"
#include "WaterRecomm.h"
#include "SunlightRecomm.h"

// Chain of Responsibility (Sabira + Karishma)
#include "CustomerQuery.h"
#include "CustomerQueryHandler.h"
#include "JuniorStaff.h"
#include "SalesExpert.h"
#include "PlantExpert.h"
#include "PricingQueryHandler.h"
#include "PlantRecommendationHandler.h"

// Staff & Mediator (Karishma)
#include "Staff.h"
#include "Gardener.h"
#include "SalesAssistant.h"
#include "Manager.h"
#include "DeliveryStaff.h"
#include "NurseryInventoryMediator.h"
#include "PlantIssue.h"
#include "JuniorGardener.h"
#include "SeniorGardener.h"
#include "PlantSpecialist.h"

// Factory patterns (Karishma + Kiolin)
#include "StaffFactory.h"
#include "GardenerFactory.h"
#include "SalesAssistantFactory.h"
#include "ManagerFactory.h"
#include "DeliveryStaffFactory.h"
#include "StockManager.h"
#include "FlowerFactory.h"
#include "SucculentFactory.h"
#include "TreeFactory.h"

// Observer pattern (Kiolin)
#include "StaffNotificationObserver.h"

// State pattern (Rene)
#include "PlantContext.h"
#include "PlantState.h"

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

// Taskeen's Payment State includes
#include "SalesContext.h"
#include "BrowsingState.h"
#include "AwaitingStockState.h"

#include"Pine.h"
#include"Lotus.h"
#include"Apple.h"

class CompleteNurseryUI {
private:
    // Core systems
    PlantInventory* inventory;
    Customer* currentCustomer;
    StockManager* stockManager;
    NurseryInventoryMediator* mediator;
    StaffNotificationObserver* observer;
    
    // Pattern contexts
    StratContext* strategyContext;
    Invoker* invoker;
    CustomerQueryHandler* customerQueryChain;
    
    // Staff
    std::vector<Staff*> nurseryStaff;
    JuniorGardener* juniorGardener;
    SeniorGardener* seniorGardener;
    PlantSpecialist* plantSpecialist;
    
    // Growing plants
    std::vector<PlantContext*> growingPlants;

    PrototypeRegistry* prototypeRegistry;
    ConcreteArrangementBuilder* arrangementBuilder;
    Director* director;
    SalesContext* salesContext;
    
    // UI helpers
    void clearScreen();
    void pressEnter();
    //int getValidatedInput(int min, int max);
    void printHeader(const std::string& title);
    void printSubHeader(const std::string& title);
    void printSuccess(const std::string& msg);
    void printError(const std::string& msg);
    void printBox(const std::string& content);
    
    void initializeNursery();
    void setupStaff();
    void setupQueryChain();
    
public:
    CompleteNurseryUI();
    ~CompleteNurseryUI();
    
    //Main menus
    void showMainMenu();
    void showCustomerMenu();
    void showStaffMenu();
    void showGreenhouseMenu();
    void showPatternDemoMenu();
    
    //Customer menus(Sabira's work)
    void showBrowsingMenu();
    void showCartMenu();
    void showRecommendationMenu();
    void showPricingMenu();
    void showHelpMenu();
    
    //Staff menus(Karishma's work)
    void showPlantCareMenu();
    void showStaffTasksMenu();
    void showInventoryMediatorMenu();
    void showPlantIssuesMenu();
    
    //Greenouse menus(Kiolin + Rene's work from main[but modify it so it fits well with the UI])
    void showStockManagementMenu();
    void showPlantLifecycleMenu();
    void showFactoryProductionMenu();

    //Decoration + Customer Payment(Taskeen's menus)
    void showPersonalizationMenu();
    void showPaymentMenu();
    void personalizeSelectedPlant(Plant* plant);
    
    //Helper functions
    void displayCart();
    double calculateCartTotal();
    int getValidatedInput(int min, int max);

};

#endif