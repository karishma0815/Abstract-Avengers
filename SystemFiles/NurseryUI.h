#ifndef NURSERYUI_H
#define NURSERYUI_H

#include <iostream>
#include <string>
#include <limits>
#include "Plant.h"
#include"Rose.h"
#include"Cacti.h"
#include "PlantInventory.h"
#include "PlantIterator.h"
#include "PriceRangeIterator.h"
#include "CareIterator.h"
#include "Customer.h"
#include "Invoker.h"
#include "AddToCart.h"
#include "RemoveFromCart.h"
#include "StratContext.h"
#include "RegularPrice.h"
#include "BulkDiscount.h"
#include "DefaultRecomm.h"
#include "WaterRecomm.h"
#include "SunlightRecomm.h"
#include "CustomerQuery.h"
#include "CustomerQueryHandler.h"
#include "JuniorStaff.h"
#include "SalesExpert.h"
#include "PlantExpert.h"

class NurseryUI {
private:
    PlantInventory* inventory;
    Customer* currentCustomer;
    StratContext* strategyContext;
    Invoker* invoker;
    CustomerQueryHandler* queryChain;

    void clearScreen();
    void pressEnterToContinue();
    void initializeInventory();
    void setupQueryChain();

public:
    NurseryUI();
    ~NurseryUI();
    
    int getValidatedInput(int min, int max);
    void showMainMenu();
    void showBrowsingMenu();
    void showCartMenu();
    void showRecommendationMenu();
    void showPricingMenu();
    void showDecorationMenu();
    void showHelpMenu();
};

#endif