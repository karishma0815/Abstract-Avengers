#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include <sstream>
#include <iostream>

#include "CareCommand.h"
#include "WaterCommand.h"
#include "FertilizeCommand.h"
#include "PruneCommand.h"
#include "SunlightCommand.h"
#include "Plant.h"

#include "PlantIssue.h"
#include "PlantCareHandler.h"
#include "JuniorGardener.h"
#include "SeniorGardener.h"
#include "PlantSpecialist.h"

#include "InventoryMediator.h"
#include "NurseryInventoryMediator.h"
#include "Staff.h"
#include "Gardener.h"
#include "Manager.h"
#include "SalesAssistant.h"
#include "DeliveryStaff.h"

#include "CustomerQuery.h"
#include "CustomerQueryHandler.h"
#include "JuniorStaff.h"
#include "SalesExpert.h"
#include "PlantExpert.h"

#include "StaffFactory.h"
#include "GardenerFactory.h"
#include "SalesAssistantFactory.h"
#include "ManagerFactory.h"
#include "DeliveryStaffFactory.h"

#include "Rose.h"
#include "Jade.h"
#include "Jacaranda.h"
#include "Orchid.h"
#include "Apple.h"
#include "Pine.h"
#include "Cacti.h"
#include "Protea.h"
#include "Lotus.h"

/*COMMAND (plant care)
only tested the execute, constructors and logAction for water, fertilize, prune and sunlight*/

TEST_CASE("testing all of the constructors and their execution") {
    // Use the correct constructor for your concrete plant classes
    Rose testPlant("Test Plant", 0.0); // name, price only
    
    SUBCASE("all of the constructors work") {
        CHECK_NOTHROW(WaterCommand(&testPlant, 2.0));
        CHECK_NOTHROW(FertilizeCommand(&testPlant, "Organic"));
        CHECK_NOTHROW(PruneCommand(&testPlant, 2));
        CHECK_NOTHROW(SunlightCommand(&testPlant, 4, "direct"));
    }
    
    SUBCASE("all the execute methods work") {
        WaterCommand waterCmd(&testPlant, 2.0);
        FertilizeCommand fertilizeCmd(&testPlant, "Organic");
        PruneCommand pruneCmd(&testPlant, 2);
        SunlightCommand sunlightCmd(&testPlant, 4, "direct");
        
        CHECK_NOTHROW(waterCmd.execute());
        CHECK_NOTHROW(fertilizeCmd.execute());
        CHECK_NOTHROW(pruneCmd.execute());
        CHECK_NOTHROW(sunlightCmd.execute());
    }
    
    SUBCASE("executing with different parameters") {
        SUBCASE("testing WaterCommand with different amounts") {
            CHECK_NOTHROW(WaterCommand(&testPlant, 0.0).execute());
            CHECK_NOTHROW(WaterCommand(&testPlant, 1.5).execute());
            CHECK_NOTHROW(WaterCommand(&testPlant, 100.0).execute());
        }
        
        SUBCASE("testing FertilizeCommand with different types") {
            CHECK_NOTHROW(FertilizeCommand(&testPlant, "Organic").execute());
            CHECK_NOTHROW(FertilizeCommand(&testPlant, "Chemical").execute());
            CHECK_NOTHROW(FertilizeCommand(&testPlant, "").execute());
        }
        
        SUBCASE("testing PruneCommand with different intensities") {
            CHECK_NOTHROW(PruneCommand(&testPlant, 0).execute());
            CHECK_NOTHROW(PruneCommand(&testPlant, 3).execute());
            CHECK_NOTHROW(PruneCommand(&testPlant, 10).execute());
        }
        
        SUBCASE("testing SunlightCommand with different settings") {
            CHECK_NOTHROW(SunlightCommand(&testPlant, 1, "low").execute());
            CHECK_NOTHROW(SunlightCommand(&testPlant, 8, "direct").execute());
            CHECK_NOTHROW(SunlightCommand(&testPlant, 0, "").execute());
        }
    }
}

TEST_CASE("testing the logAction") {
    Orchid testPlant("Test Plant", 0.0); // name, price only
    
    SUBCASE("all the log actions work") {
        WaterCommand waterCmd(&testPlant, 2.0);
        FertilizeCommand fertilizeCmd(&testPlant, "Organic");
        PruneCommand pruneCmd(&testPlant, 2);
        SunlightCommand sunlightCmd(&testPlant, 4, "direct");
        
        CHECK_NOTHROW(waterCmd.logAction());
        CHECK_NOTHROW(fertilizeCmd.logAction());
        CHECK_NOTHROW(pruneCmd.logAction());
        CHECK_NOTHROW(sunlightCmd.logAction());
    }
}

TEST_CASE("command safety and edge cases") {
    SUBCASE("null plant safety") {
        CHECK_NOTHROW(WaterCommand(nullptr, 2.0).execute());
        CHECK_NOTHROW(FertilizeCommand(nullptr, "Organic").execute());
        CHECK_NOTHROW(PruneCommand(nullptr, 2).execute());
        CHECK_NOTHROW(SunlightCommand(nullptr, 4, "direct").execute());
        
        CHECK_NOTHROW(WaterCommand(nullptr, 2.0).logAction());
        CHECK_NOTHROW(FertilizeCommand(nullptr, "Organic").logAction());
    }
    
    SUBCASE("testing multiple executions") {
        Jade testPlant("Test Plant", 0.0); // name, price only
        WaterCommand waterCmd(&testPlant, 1.0);
        
        CHECK_NOTHROW(waterCmd.execute());
        CHECK_NOTHROW(waterCmd.execute());
        CHECK_NOTHROW(waterCmd.execute());
    }
    
    SUBCASE("testing command combinations") {
        Lotus testPlant("Test Plant", 0.0); // name, price only
        
        CHECK_NOTHROW(WaterCommand(&testPlant, 2.0).execute());
        CHECK_NOTHROW(FertilizeCommand(&testPlant, "Organic").execute());
        CHECK_NOTHROW(PruneCommand(&testPlant, 2).execute());
        CHECK_NOTHROW(SunlightCommand(&testPlant, 6, "direct").execute());
    }
}

/*CHAIN OF RESPONSIBILITY (plant life cycles)
only tested the constructor for plant issue, setNext for the plant care handler and handleQuery and canHandle for junior and senior gardener and plant specialist*/

TEST_CASE("testing the PlantIssue constructor") {
    SUBCASE("testing the constructor with valid parameters") {
        Rose testPlant("Test Plant", 0.0); // name, price only
        
        CHECK_NOTHROW(PlantIssue(PlantIssue::LOW, "Minor leaf spots", &testPlant));
        CHECK_NOTHROW(PlantIssue(PlantIssue::MEDIUM, "Moderate wilting", &testPlant));
        CHECK_NOTHROW(PlantIssue(PlantIssue::HIGH, "Severe infection", &testPlant));
        CHECK_NOTHROW(PlantIssue(PlantIssue::CRITICAL, "Plant near death", &testPlant));
    }
    
    SUBCASE("testing the constructor with null plant") {
        CHECK_NOTHROW(PlantIssue(PlantIssue::LOW, "General issue", nullptr));
        CHECK_NOTHROW(PlantIssue(PlantIssue::CRITICAL, "Critical issue", nullptr));
    }
    
    SUBCASE("testing the constructor with empty description") {
        Orchid testPlant("Test Plant", 0.0); // name, price only
        CHECK_NOTHROW(PlantIssue(PlantIssue::MEDIUM, "", &testPlant));
    }
}

TEST_CASE("setNext chain setup") {
    SUBCASE("testing a basic chain setup") {
        JuniorGardener junior;
        SeniorGardener senior;
        
        CHECK_NOTHROW(junior.setNext(&senior));
    }
    
    SUBCASE("testing multiple chain links") {
        JuniorGardener junior;
        SeniorGardener senior;
        PlantSpecialist specialist;
        
        CHECK_NOTHROW(junior.setNext(&senior));
        CHECK_NOTHROW(senior.setNext(&specialist));
    }
    
    SUBCASE("testing a null next handler") {
        JuniorGardener junior;
        CHECK_NOTHROW(junior.setNext(nullptr));
    }
    
    SUBCASE("testing a self reference") {
        JuniorGardener junior;
        CHECK_NOTHROW(junior.setNext(&junior));
    }
    
    SUBCASE("testing a circular reference") {
        JuniorGardener junior;
        SeniorGardener senior;
        
        junior.setNext(&senior);
        CHECK_NOTHROW(senior.setNext(&junior));
    }
}

TEST_CASE("testing JuniorGardener canHandle logic") {
    JuniorGardener junior;
    Jade testPlant("Test Plant", 0.0); // name, price only
    
    SUBCASE("testing handles with LOW severity") {
        PlantIssue lowIssue(PlantIssue::LOW, "Minor issue", &testPlant);
        CHECK(junior.canHandle(lowIssue) == true);
    }
    
    SUBCASE("testing handles with MEDIUM severity") {
        PlantIssue mediumIssue(PlantIssue::MEDIUM, "Moderate issue", &testPlant);
        CHECK(junior.canHandle(mediumIssue) == true);
    }
    
    SUBCASE("testing if it does not handle HIGH severity") {
        PlantIssue highIssue(PlantIssue::HIGH, "Severe issue", &testPlant);
        CHECK(junior.canHandle(highIssue) == false);
    }
    
    SUBCASE("testing if it does not handle CRITICAL severity") {
        PlantIssue criticalIssue(PlantIssue::CRITICAL, "Critical issue", &testPlant);
        CHECK(junior.canHandle(criticalIssue) == false);
    }
    
    SUBCASE("testing if it handles issues with null plant") {
        PlantIssue nullPlantIssue(PlantIssue::LOW, "Issue with no plant", nullptr);
        CHECK(junior.canHandle(nullPlantIssue) == true);
    }
}

TEST_CASE("testing the SeniorGardener canHandle logic") {
    SeniorGardener senior;
    Jacaranda testPlant("Test Plant", 0.0); // name, price only
    
    SUBCASE("testing if it does not handle LOW severity") {
        PlantIssue lowIssue(PlantIssue::LOW, "Minor issue", &testPlant);
        CHECK(senior.canHandle(lowIssue) == false);
    }
    
    SUBCASE("testing if it does not handle MEDIUM severity") {
        PlantIssue mediumIssue(PlantIssue::MEDIUM, "Moderate issue", &testPlant);
        CHECK(senior.canHandle(mediumIssue) == false);
    }
    
    SUBCASE("testing if it handles HIGH severity") {
        PlantIssue highIssue(PlantIssue::HIGH, "Severe issue", &testPlant);
        CHECK(senior.canHandle(highIssue) == true);
    }
    
    SUBCASE("testing if it does not handle CRITICAL severity") {
        PlantIssue criticalIssue(PlantIssue::CRITICAL, "Critical issue", &testPlant);
        CHECK(senior.canHandle(criticalIssue) == false);
    }
}

TEST_CASE("testing the PlantSpecialist canHandle logic") {
    PlantSpecialist specialist;
    Apple testPlant("Test Plant", 0.0); // name, price only
    
    SUBCASE("testing if it does not handle LOW severity") {
        PlantIssue lowIssue(PlantIssue::LOW, "Minor issue", &testPlant);
        CHECK(specialist.canHandle(lowIssue) == false);
    }
    
    SUBCASE("testing if it does not handle MEDIUM severity") {
        PlantIssue mediumIssue(PlantIssue::MEDIUM, "Moderate issue", &testPlant);
        CHECK(specialist.canHandle(mediumIssue) == false);
    }
    
    SUBCASE("testing if it does not handle HIGH severity") {
        PlantIssue highIssue(PlantIssue::HIGH, "Severe issue", &testPlant);
        CHECK(specialist.canHandle(highIssue) == false);
    }
    
    SUBCASE("testing if it handles CRITICAL severity") {
        PlantIssue criticalIssue(PlantIssue::CRITICAL, "Critical issue", &testPlant);
        CHECK(specialist.canHandle(criticalIssue) == true);
    }
}

TEST_CASE("testing the JuniorGardener handleIssue") {
    Lotus testPlant("Test Plant", 0.0); // name, price only
    
    SUBCASE("testing if it handles LOW severity issue") {
        JuniorGardener junior;
        PlantIssue lowIssue(PlantIssue::LOW, "Minor leaf spots", &testPlant);
        
        CHECK_NOTHROW(junior.handleIssue(lowIssue));
    }
    
    SUBCASE("testing if it handles MEDIUM severity issue") {
        JuniorGardener junior;
        PlantIssue mediumIssue(PlantIssue::MEDIUM, "Moderate wilting", &testPlant);
        
        CHECK_NOTHROW(junior.handleIssue(mediumIssue));
    }
    
    SUBCASE("testing if it escalates HIGH severity to next handler") {
        JuniorGardener junior;
        SeniorGardener senior;
        junior.setNext(&senior);
        
        PlantIssue highIssue(PlantIssue::HIGH, "Severe infection", &testPlant);
        
        CHECK_NOTHROW(junior.handleIssue(highIssue));
    }
    
    SUBCASE("testing if it escalates CRITICAL severity to next handler") {
        JuniorGardener junior;
        SeniorGardener senior;
        junior.setNext(&senior);
        
        PlantIssue criticalIssue(PlantIssue::CRITICAL, "Plant dying", &testPlant);
        
        CHECK_NOTHROW(junior.handleIssue(criticalIssue));
    }
    
    SUBCASE("testing if it handles issue when no next handler available") {
        JuniorGardener junior;
        PlantIssue highIssue(PlantIssue::HIGH, "Severe issue", &testPlant);
        
        CHECK_NOTHROW(junior.handleIssue(highIssue));
    }
    
    SUBCASE("testing if it handles issue with null plant") {
        JuniorGardener junior;
        PlantIssue nullIssue(PlantIssue::LOW, "General issue", nullptr);
        
        CHECK_NOTHROW(junior.handleIssue(nullIssue));
    }
}

TEST_CASE("testing the SeniorGardener handleIssue") {
    Protea testPlant("Test Plant", 0.0); // name, price only
    
    SUBCASE("testing if it handles HIGH severity issue") {
        SeniorGardener senior;
        PlantIssue highIssue(PlantIssue::HIGH, "Severe infection", &testPlant);
        
        CHECK_NOTHROW(senior.handleIssue(highIssue));
    }
    
    SUBCASE("testing if it escalates CRITICAL severity to next handler") {
        SeniorGardener senior;
        PlantSpecialist specialist;
        senior.setNext(&specialist);
        
        PlantIssue criticalIssue(PlantIssue::CRITICAL, "Plant near death", &testPlant);
        
        CHECK_NOTHROW(senior.handleIssue(criticalIssue));
    }
    
    SUBCASE("testing if it does not handle LOW severity") {
        SeniorGardener senior;
        JuniorGardener junior;
        senior.setNext(&junior);
        
        PlantIssue lowIssue(PlantIssue::LOW, "Minor issue", &testPlant);
        
        CHECK_NOTHROW(senior.handleIssue(lowIssue));
    }
    
    SUBCASE("testing if it handles issue when no next handler available") {
        SeniorGardener senior;
        PlantIssue criticalIssue(PlantIssue::CRITICAL, "Critical issue", &testPlant);
        
        CHECK_NOTHROW(senior.handleIssue(criticalIssue));
    }
}

TEST_CASE("testing the PlantSpecialist handleIssue") {
    Pine testPlant("Test Plant", 0.0); // name, price only
    
    SUBCASE("testing if it handles CRITICAL severity issue") {
        PlantSpecialist specialist;
        PlantIssue criticalIssue(PlantIssue::CRITICAL, "Plant emergency", &testPlant);
        
        CHECK_NOTHROW(specialist.handleIssue(criticalIssue));
    }
    
    SUBCASE("testing if it does not handle non-critical issues") {
        PlantSpecialist specialist;
        
        SUBCASE("testing the LOW severity") {
            PlantIssue lowIssue(PlantIssue::LOW, "Minor issue", &testPlant);
            CHECK_NOTHROW(specialist.handleIssue(lowIssue));
        }
        
        SUBCASE("testing the MEDIUM severity") {
            PlantIssue mediumIssue(PlantIssue::MEDIUM, "Moderate issue", &testPlant);
            CHECK_NOTHROW(specialist.handleIssue(mediumIssue));
        }
        
        SUBCASE("testing the HIGH severity") {
            PlantIssue highIssue(PlantIssue::HIGH, "Severe issue", &testPlant);
            CHECK_NOTHROW(specialist.handleIssue(highIssue));
        }
    }
    
    SUBCASE("testing if it handles issue with null plant") {
        PlantSpecialist specialist;
        PlantIssue criticalIssue(PlantIssue::CRITICAL, "Critical issue", nullptr);
        
        CHECK_NOTHROW(specialist.handleIssue(criticalIssue));
    }
}

TEST_CASE("testing the complete Chain of Responsibility") {
    Cacti testPlant("Test Plant", 0.0); // name, price only
    
    SUBCASE("testing the full escalation chain") {
        JuniorGardener junior;
        SeniorGardener senior;
        PlantSpecialist specialist;
        
        junior.setNext(&senior);
        senior.setNext(&specialist);
        
        SUBCASE("LOW severity - handled by Junior") {
            PlantIssue lowIssue(PlantIssue::LOW, "Minor spots", &testPlant);
            CHECK_NOTHROW(junior.handleIssue(lowIssue));
        }
        
        SUBCASE("MEDIUM severity - handled by Junior") {
            PlantIssue mediumIssue(PlantIssue::MEDIUM, "Moderate wilting", &testPlant);
            CHECK_NOTHROW(junior.handleIssue(mediumIssue));
        }
        
        SUBCASE("HIGH severity - escalated to Senior") {
            PlantIssue highIssue(PlantIssue::HIGH, "Severe infection", &testPlant);
            CHECK_NOTHROW(junior.handleIssue(highIssue));
        }
        
        SUBCASE("CRITICAL severity - escalated to Specialist") {
            PlantIssue criticalIssue(PlantIssue::CRITICAL, "Plant dying", &testPlant);
            CHECK_NOTHROW(junior.handleIssue(criticalIssue));
        }
    }
    
    SUBCASE("testing the broken chain - missing senior") {
        JuniorGardener junior;
        PlantSpecialist specialist;
        junior.setNext(&specialist);
        
        PlantIssue highIssue(PlantIssue::HIGH, "Severe issue", &testPlant);
        CHECK_NOTHROW(junior.handleIssue(highIssue));
    }
    
    SUBCASE("testing the broken chain - missing Specialist") {
        JuniorGardener junior;
        SeniorGardener senior;
        junior.setNext(&senior);
        // No specialist set
        
        PlantIssue criticalIssue(PlantIssue::CRITICAL, "Critical issue", &testPlant);
        CHECK_NOTHROW(junior.handleIssue(criticalIssue));
    }
}

TEST_CASE("testing the chain edge cases") {
    Rose testPlant("Test Plant", 0.0); // name, price only
    
    SUBCASE("testing empty descriptions") {
        JuniorGardener junior;
        
        PlantIssue emptyDescIssue(PlantIssue::LOW, "", &testPlant);
        CHECK_NOTHROW(junior.handleIssue(emptyDescIssue));
        CHECK(junior.canHandle(emptyDescIssue) == true);
    }
    
    SUBCASE("testing multiple sequential issues") {
        JuniorGardener junior;
        SeniorGardener senior;
        PlantSpecialist specialist;
        junior.setNext(&senior);
        senior.setNext(&specialist);
        
        CHECK_NOTHROW(junior.handleIssue(PlantIssue(PlantIssue::LOW, "Issue 1", &testPlant)));
        CHECK_NOTHROW(junior.handleIssue(PlantIssue(PlantIssue::MEDIUM, "Issue 2", &testPlant)));
        CHECK_NOTHROW(junior.handleIssue(PlantIssue(PlantIssue::HIGH, "Issue 3", &testPlant)));
        CHECK_NOTHROW(junior.handleIssue(PlantIssue(PlantIssue::CRITICAL, "Issue 4", &testPlant)));
    }
    
    SUBCASE("testing the same issue through different handlers") {
        PlantIssue sameIssue(PlantIssue::HIGH, "Same issue", &testPlant);
        
        JuniorGardener junior;
        SeniorGardener senior;
        
        CHECK(junior.canHandle(sameIssue) == false);
        CHECK(senior.canHandle(sameIssue) == true);
    }
}

/*MEDIATOR (inventory)
only tested the notify and updateInventory*/

TEST_CASE("testing the NurseryInventoryMediator constructor") {
    SUBCASE("testing the initial state") {
        NurseryInventoryMediator mediator;
        
        Rose testPlant("Test Plant", 5.0, "TP001");
        CHECK(mediator.getGreenhouseStock(&testPlant) == 1000000); // Greenhouse always has stock
        CHECK(mediator.getSalesFloorStock(&testPlant) == 0);
    }
}

TEST_CASE("testing the updateInventory function") {
    NurseryInventoryMediator mediator;
    Orchid testPlant("Test Plant", 5.0, "TP001");
    
    SUBCASE("testing basic inventory updates") {
        // Note: updateInventory only takes 2 arguments, not 3
        mediator.updateInventory(&testPlant, 50); // salesFloorQuantity only
        CHECK(mediator.getSalesFloorStock(&testPlant) == 50);
        // greenhouse stock remains 1000000 since we're only updating sales floor
        CHECK(mediator.getGreenhouseStock(&testPlant) == 1000000);
    }
    
    SUBCASE("testing negative prevention - sales floor") {
        mediator.updateInventory(&testPlant, 30);
        mediator.updateInventory(&testPlant, -50); // Should prevent negative
        
        CHECK(mediator.getSalesFloorStock(&testPlant) == 0);
        CHECK(mediator.getGreenhouseStock(&testPlant) == 1000000);
    }
    
    SUBCASE("testing multiple sequential updates") {
        mediator.updateInventory(&testPlant, 100);
        mediator.updateInventory(&testPlant, 30); // Add 30 more
        mediator.updateInventory(&testPlant, -10); // Remove 10
        
        CHECK(mediator.getSalesFloorStock(&testPlant) == 120);
        CHECK(mediator.getGreenhouseStock(&testPlant) == 1000000);
    }
    
    SUBCASE("testing null plant handling") {
        CHECK_NOTHROW(mediator.updateInventory(nullptr, 100));
        CHECK_NOTHROW(mediator.updateInventory(nullptr, -50));
    }
}

TEST_CASE("testing the notify function - event handling") {
    NurseryInventoryMediator mediator;
    Jade testPlant("Test Plant", 5.0, "TP001");
    Gardener testGardener("Test Gardener", 1001, &mediator, "General");
    
    SUBCASE("testing new shipment event") {
        mediator.notify(&testGardener, "new shipment", &testPlant, 200);
        
        CHECK(mediator.getGreenhouseStock(&testPlant) == 1000000); // Greenhouse always has stock
        CHECK(mediator.getSalesFloorStock(&testPlant) == 0);
    }
    
    SUBCASE("testing plant moved to sales") {
        mediator.notify(&testGardener, "new shipment", &testPlant, 150);
        mediator.notify(&testGardener, "plant moved to sales", &testPlant, 80);
        
        CHECK(mediator.getGreenhouseStock(&testPlant) == 1000000); // Greenhouse always has stock
        CHECK(mediator.getSalesFloorStock(&testPlant) == 80);
    }
    
    SUBCASE("testing plant sold") {
        mediator.notify(&testGardener, "new shipment", &testPlant, 100);
        mediator.notify(&testGardener, "plant moved to sales", &testPlant, 60);
        mediator.notify(&testGardener, "plant sold", &testPlant, 40);
        
        CHECK(mediator.getGreenhouseStock(&testPlant) == 1000000); // Greenhouse always has stock
        CHECK(mediator.getSalesFloorStock(&testPlant) == 20);
    }
    
    SUBCASE("testing customer delivery") {
        mediator.notify(&testGardener, "new shipment", &testPlant, 100);
        mediator.notify(&testGardener, "plant moved to sales", &testPlant, 70);
        mediator.notify(&testGardener, "customer delivery", &testPlant, 50);
        
        CHECK(mediator.getGreenhouseStock(&testPlant) == 1000000); // Greenhouse always has stock
        CHECK(mediator.getSalesFloorStock(&testPlant) == 20);
    }
    
    SUBCASE("testing the return to greenhouse") {
        mediator.notify(&testGardener, "new shipment", &testPlant, 100);
        mediator.notify(&testGardener, "plant moved to sales", &testPlant, 80);
        mediator.notify(&testGardener, "return to greenhouse", &testPlant, 20);
        
        CHECK(mediator.getGreenhouseStock(&testPlant) == 1000000); // Greenhouse always has stock
        CHECK(mediator.getSalesFloorStock(&testPlant) == 60);
    }
    
    SUBCASE("testing the check stock") {
        mediator.notify(&testGardener, "new shipment", &testPlant, 100);
        
        CHECK_NOTHROW(mediator.notify(&testGardener, "check stock", &testPlant, 0));
        CHECK(mediator.getGreenhouseStock(&testPlant) == 1000000); // Greenhouse always has stock
    }
    
    SUBCASE("testing the unknown") {
        CHECK_NOTHROW(mediator.notify(&testGardener, "unknown event", &testPlant, 50));
        
        CHECK(mediator.getGreenhouseStock(&testPlant) == 1000000); // Greenhouse always has stock
    }
}

TEST_CASE("testing the notify function - edge cases and safety") {
    NurseryInventoryMediator mediator;
    Jacaranda testPlant("Test Plant", 5.0, "TP001");
    Gardener testGardener("Test Gardener", 1001, &mediator, "General");
    
    SUBCASE("testing over moving from greenhouse") {
        mediator.notify(&testGardener, "new shipment", &testPlant, 50);
        mediator.notify(&testGardener, "plant moved to sales", &testPlant, 100);
        
        CHECK(mediator.getGreenhouseStock(&testPlant) == 1000000); // Greenhouse always has stock
        CHECK(mediator.getSalesFloorStock(&testPlant) == 100); // Can move up to requested amount
    }
    
    SUBCASE("testing over selling from sales floor") {
        mediator.notify(&testGardener, "new shipment", &testPlant, 100);
        mediator.notify(&testGardener, "plant moved to sales", &testPlant, 40);
        mediator.notify(&testGardener, "plant sold", &testPlant, 60);
        
        CHECK(mediator.getSalesFloorStock(&testPlant) == 0); // Sell what's available
        CHECK(mediator.getGreenhouseStock(&testPlant) == 1000000);
    }
    
    SUBCASE("testing over delivering from sales floor") {
        mediator.notify(&testGardener, "new shipment", &testPlant, 100);
        mediator.notify(&testGardener, "plant moved to sales", &testPlant, 30);
        mediator.notify(&testGardener, "customer delivery", &testPlant, 50);
        
        CHECK(mediator.getSalesFloorStock(&testPlant) == 0); // Deliver what's available
        CHECK(mediator.getGreenhouseStock(&testPlant) == 1000000);
    }
    
    SUBCASE("testing negative quantity handling") {
        CHECK_NOTHROW(mediator.notify(&testGardener, "new shipment", &testPlant, -50));
        CHECK(mediator.getGreenhouseStock(&testPlant) == 1000000); // Greenhouse always has stock
    }
    
    SUBCASE("testing zero quantity handling") {
        CHECK_NOTHROW(mediator.notify(&testGardener, "new shipment", &testPlant, 0));
        CHECK_NOTHROW(mediator.notify(&testGardener, "plant sold", &testPlant, 0));
        
        CHECK(mediator.getGreenhouseStock(&testPlant) == 1000000); // Greenhouse always has stock
        CHECK(mediator.getSalesFloorStock(&testPlant) == 0);
    }
    
    SUBCASE("testing null plant handling") {
        CHECK_NOTHROW(mediator.notify(&testGardener, "new shipment", nullptr, 100));
        CHECK_NOTHROW(mediator.notify(&testGardener, "plant sold", nullptr, 50));
        
        // For null plants, greenhouse stock check might behave differently
        // but for valid plants it should be 1000000
        CHECK(mediator.getGreenhouseStock(&testPlant) == 1000000);
        CHECK(mediator.getSalesFloorStock(&testPlant) == 0);
    }
    
    SUBCASE("testing null sender handling") {
        CHECK_NOTHROW(mediator.notify(nullptr, "new shipment", &testPlant, 100));
        CHECK_NOTHROW(mediator.notify(nullptr, "plant sold", &testPlant, 50));
        
        CHECK(mediator.getGreenhouseStock(&testPlant) == 1000000); // Greenhouse always has stock
    }
}

TEST_CASE("testing complete inventory workflow") {
    NurseryInventoryMediator mediator;
    Apple testPlant("Test Plant", 5.0, "TP001");
    Gardener gardener("Test Gardener", 1001, &mediator, "General");
    SalesAssistant salesAsst("Test Sales", 2001, &mediator, 0.05);
    
    SUBCASE("testing complete business day scenario") {
        mediator.notify(&gardener, "new shipment", &testPlant, 500);
        CHECK(mediator.getGreenhouseStock(&testPlant) == 1000000); // Greenhouse always has stock
        
        mediator.notify(&gardener, "plant moved to sales", &testPlant, 300);
        CHECK(mediator.getGreenhouseStock(&testPlant) == 1000000); // Greenhouse always has stock
        CHECK(mediator.getSalesFloorStock(&testPlant) == 300);
        
        mediator.notify(&salesAsst, "plant sold", &testPlant, 100);
        mediator.notify(&salesAsst, "plant sold", &testPlant, 80);
        CHECK(mediator.getSalesFloorStock(&testPlant) == 120);
        
        mediator.notify(&salesAsst, "customer delivery", &testPlant, 60);
        CHECK(mediator.getSalesFloorStock(&testPlant) == 60);
        
        mediator.notify(&salesAsst, "return to greenhouse", &testPlant, 20);
        CHECK(mediator.getGreenhouseStock(&testPlant) == 1000000); // Greenhouse always has stock
        CHECK(mediator.getSalesFloorStock(&testPlant) == 40);
        
        CHECK_NOTHROW(mediator.notify(&salesAsst, "check stock", &testPlant, 0));
    }
    
    SUBCASE("testing multiple plant types") {
        Rose rose("Rose", 6.0, "R001");
        Cacti cactus("Cactus", 8.0, "C001");
        
        mediator.notify(&gardener, "new shipment", &rose, 200);
        mediator.notify(&gardener, "new shipment", &cactus, 100);
        
        CHECK(mediator.getGreenhouseStock(&rose) == 1000000); // Greenhouse always has stock
        CHECK(mediator.getGreenhouseStock(&cactus) == 1000000); // Greenhouse always has stock
        
        mediator.notify(&gardener, "plant moved to sales", &rose, 80);
        mediator.notify(&gardener, "plant moved to sales", &cactus, 40);
        
        CHECK(mediator.getSalesFloorStock(&rose) == 80);
        CHECK(mediator.getSalesFloorStock(&cactus) == 40);
        
        mediator.notify(&salesAsst, "plant sold", &rose, 50);
        mediator.notify(&salesAsst, "plant sold", &cactus, 30);
        
        CHECK(mediator.getSalesFloorStock(&rose) == 30);
        CHECK(mediator.getSalesFloorStock(&cactus) == 10);
    }
}

TEST_CASE("testing inventory integrity") {
    NurseryInventoryMediator mediator;
    Lotus testPlant("Test Plant", 5.0, "TP001");
    Gardener testGardener("Test Gardener", 1001, &mediator, "General");
    
    SUBCASE("testing stock never goes negative") {
        mediator.notify(&testGardener, "plant sold", &testPlant, 100);
        CHECK(mediator.getSalesFloorStock(&testPlant) == 0);
        
        mediator.notify(&testGardener, "customer delivery", &testPlant, 50);
        CHECK(mediator.getSalesFloorStock(&testPlant) == 0);
        
        mediator.notify(&testGardener, "plant moved to sales", &testPlant, 80);
        CHECK(mediator.getGreenhouseStock(&testPlant) == 1000000); // Greenhouse always has stock
        CHECK(mediator.getSalesFloorStock(&testPlant) == 80); // Can move plants to sales floor
    }
    
    SUBCASE("testing large quantity handling") {
        CHECK_NOTHROW(mediator.notify(&testGardener, "new shipment", &testPlant, 10000));
        CHECK_NOTHROW(mediator.notify(&testGardener, "plant moved to sales", &testPlant, 5000));
        CHECK_NOTHROW(mediator.notify(&testGardener, "plant sold", &testPlant, 3000));
        
        CHECK(mediator.getGreenhouseStock(&testPlant) == 1000000); // Greenhouse always has stock
        CHECK(mediator.getSalesFloorStock(&testPlant) == 2000);
    }
}

/*CHAIN OF RESPONSIBILITY (customer interaction)
only tested the handleQuery, canHandle and setNext*/

TEST_SUITE("testing the customer query handling system") {

    TEST_CASE("testing the CustomerQuery class") {
        SUBCASE("testing the constructor") {
            CustomerQuery query(CustomerQuery::PRICING, "How much are roses?", nullptr);
            
            CHECK(query.type == CustomerQuery::PRICING);
            CHECK(query.question == "How much are roses?");
            CHECK(query.customer == nullptr);
        }
        
        SUBCASE("testing the query type enum values - in the correct order") {
            CHECK(CustomerQuery::GENERAL == 0);
            CHECK(CustomerQuery::CARE_ADVICE == 1);
            CHECK(CustomerQuery::PRICING == 2);
            CHECK(CustomerQuery::COMPLAINT == 3);
            CHECK(CustomerQuery::SPECIAL_REQUEST == 4);
        }
    }

    TEST_CASE("testing the JuniorStaff - canHandle()") {
        JuniorStaff junior;
        
        SUBCASE("testing the general queries - should handle") {
            CHECK(junior.canHandle(CustomerQuery(CustomerQuery::GENERAL, "What are your opening hours?", nullptr)) == true);
            CHECK(junior.canHandle(CustomerQuery(CustomerQuery::GENERAL, "Where is your location?", nullptr)) == true);
            CHECK(junior.canHandle(CustomerQuery(CustomerQuery::GENERAL, "Do you offer gift wrapping?", nullptr)) == true);
        }
        
        SUBCASE("testing the pricing queries - should handle") {
            CHECK(junior.canHandle(CustomerQuery(CustomerQuery::PRICING, "How much for roses?", nullptr)) == true);
            CHECK(junior.canHandle(CustomerQuery(CustomerQuery::PRICING, "What's the price of orchids?", nullptr)) == true);
            CHECK(junior.canHandle(CustomerQuery(CustomerQuery::PRICING, "Do you have student discount?", nullptr)) == true);
        }
        
        SUBCASE("testing the should not handle") {
            CHECK(junior.canHandle(CustomerQuery(CustomerQuery::CARE_ADVICE, "My plant is dying", nullptr)) == false);
            CHECK(junior.canHandle(CustomerQuery(CustomerQuery::COMPLAINT, "I want to complain", nullptr)) == false);
            CHECK(junior.canHandle(CustomerQuery(CustomerQuery::SPECIAL_REQUEST, "Can you deliver on Sunday?", nullptr)) == false);
            CHECK(junior.canHandle(CustomerQuery(CustomerQuery::GENERAL, "Random question", nullptr)) == false);
        }
    }

    TEST_CASE("testing the JuniorStaff - handleQuery()") {
        JuniorStaff junior;
        
        SUBCASE("testing the handle general queries") {
            CHECK_NOTHROW(junior.handleQuery(CustomerQuery(CustomerQuery::GENERAL, "opening hours", nullptr)));
            CHECK_NOTHROW(junior.handleQuery(CustomerQuery(CustomerQuery::GENERAL, "location", nullptr)));
            CHECK_NOTHROW(junior.handleQuery(CustomerQuery(CustomerQuery::GENERAL, "gift wrapping", nullptr)));
        }
        
        SUBCASE("testing the handle pricing queries") {
            CHECK_NOTHROW(junior.handleQuery(CustomerQuery(CustomerQuery::PRICING, "rose prices", nullptr)));
            CHECK_NOTHROW(junior.handleQuery(CustomerQuery(CustomerQuery::PRICING, "orchid cost", nullptr)));
            CHECK_NOTHROW(junior.handleQuery(CustomerQuery(CustomerQuery::PRICING, "student discount", nullptr)));
        }
        
        SUBCASE("escalate unhandled queries - no next handler") {
            CHECK_NOTHROW(junior.handleQuery(CustomerQuery(CustomerQuery::COMPLAINT, "My plant died", nullptr)));
        }
        
        SUBCASE("escalate to next handler") {
            SalesExpert sales;
            junior.setNext(&sales);
            
            CHECK_NOTHROW(junior.handleQuery(CustomerQuery(CustomerQuery::SPECIAL_REQUEST, "bulk order", nullptr)));
        }
    }

    TEST_CASE("testing the SalesExpert - canHandle()") {
        SalesExpert expert;
        
        SUBCASE("testing the should handle ONLY pricing queries") {
            CHECK(expert.canHandle(CustomerQuery(CustomerQuery::PRICING, "bulk discount", nullptr)) == true);
            CHECK(expert.canHandle(CustomerQuery(CustomerQuery::PRICING, "corporate rates", nullptr)) == true);
            // CHANGED: SalesExpert should NOT handle SPECIAL_REQUEST - only PRICING
            CHECK(expert.canHandle(CustomerQuery(CustomerQuery::SPECIAL_REQUEST, "Sunday delivery", nullptr)) == false);
            CHECK(expert.canHandle(CustomerQuery(CustomerQuery::SPECIAL_REQUEST, "installation", nullptr)) == false);
        }
        
        SUBCASE("testing the should not handle") {
            CHECK(expert.canHandle(CustomerQuery(CustomerQuery::GENERAL, "opening hours", nullptr)) == false);
            CHECK(expert.canHandle(CustomerQuery(CustomerQuery::CARE_ADVICE, "plant care", nullptr)) == false);
            CHECK(expert.canHandle(CustomerQuery(CustomerQuery::COMPLAINT, "complaint", nullptr)) == false);
            // Also should not handle SPECIAL_REQUEST
            CHECK(expert.canHandle(CustomerQuery(CustomerQuery::SPECIAL_REQUEST, "special delivery", nullptr)) == false);
        }
    }

    TEST_CASE("testing the SalesExpert - handleQuery()") {
        SalesExpert expert;
        
        SUBCASE("testing the handle bulk discount queries") {
            CHECK_NOTHROW(expert.handleQuery(CustomerQuery(CustomerQuery::PRICING, "bulk discount for 100 plants", nullptr)));
        }
        
        SUBCASE("testing the handle corporate pricing") {
            CHECK_NOTHROW(expert.handleQuery(CustomerQuery(CustomerQuery::PRICING, "corporate account", nullptr)));
        }
        
        SUBCASE("testing the escalate special delivery requests") {
            // CHANGED: SalesExpert should escalate SPECIAL_REQUEST since it only handles PRICING
            PlantExpert plant;
            expert.setNext(&plant);
            
            CHECK_NOTHROW(expert.handleQuery(CustomerQuery(CustomerQuery::SPECIAL_REQUEST, "deliver on Sunday", nullptr)));
        }
        
        SUBCASE("testing the escalate installation requests") {
            // CHANGED: SalesExpert should escalate SPECIAL_REQUEST since it only handles PRICING
            PlantExpert plant;
            expert.setNext(&plant);
            
            CHECK_NOTHROW(expert.handleQuery(CustomerQuery(CustomerQuery::SPECIAL_REQUEST, "install plants", nullptr)));
        }
        
        SUBCASE("testing the escalate to next handler") {
            PlantExpert plant;
            expert.setNext(&plant);
            
            CHECK_NOTHROW(expert.handleQuery(CustomerQuery(CustomerQuery::CARE_ADVICE, "plant care", nullptr)));
        }
    }

    // ... REST OF THE TEST CODE REMAINS THE SAME (PlantExpert, Manager, etc.)

    TEST_CASE("testing the integration tests") {
        SUBCASE("testing the customer with simple pricing question") {
            JuniorStaff junior;
            SalesExpert sales;
            PlantExpert plant;
            Manager manager("Store Manager", 1, nullptr, "Retail");
            
            junior.setNext(&sales);
            sales.setNext(&plant);
            plant.setNext(&manager);
            
            CHECK_NOTHROW(junior.handleQuery(CustomerQuery(CustomerQuery::PRICING, "How much are roses?", nullptr)));
        }
        
        SUBCASE("testing the customer with complex plant care issue") {
            JuniorStaff junior;
            SalesExpert sales;
            PlantExpert plant;
            
            junior.setNext(&sales);
            sales.setNext(&plant);
            
            CHECK_NOTHROW(junior.handleQuery(CustomerQuery(CustomerQuery::CARE_ADVICE, "My fern is dying, leaves turning yellow", nullptr)));
        }
        
        SUBCASE("testing the customer complaint escalation") {
            JuniorStaff junior;
            SalesExpert sales;
            PlantExpert plant;
            Manager manager("Complaint Manager", 1, nullptr, "Customer Service");
            
            junior.setNext(&sales);
            sales.setNext(&plant);
            plant.setNext(&manager);
            
            CHECK_NOTHROW(junior.handleQuery(CustomerQuery(CustomerQuery::COMPLAINT, "My expensive orchid died after one week!", nullptr)));
        }
        
        SUBCASE("testing the special request authorization") {
            JuniorStaff junior;
            SalesExpert sales;
            Manager manager("Authorization Manager", 1, nullptr, "Operations");
            
            junior.setNext(&sales);
            sales.setNext(&manager);
            
            CHECK_NOTHROW(junior.handleQuery(CustomerQuery(CustomerQuery::SPECIAL_REQUEST, "Need special delivery arrangements", nullptr)));
        }
    }

    // ... REST OF THE TEST CODE REMAINS THE SAME
}

TEST_SUITE("testing the query response content validation") {
    TEST_CASE("testing the response accuracy - basic scenarios") {
        SUBCASE("testing the junior staff provides correct opening hours") {
            JuniorStaff junior;
            CHECK_NOTHROW(junior.handleQuery(CustomerQuery(CustomerQuery::GENERAL, "opening hours", nullptr)));
        }
        
        SUBCASE("testing the plant expert provides correct cactus advice") {
            PlantExpert expert;
            CHECK_NOTHROW(expert.handleQuery(CustomerQuery(CustomerQuery::CARE_ADVICE, "water my cactus", nullptr)));
        }
        
        SUBCASE("testing the sales expert provides bulk discount info") {
            SalesExpert expert;
            CHECK_NOTHROW(expert.handleQuery(CustomerQuery(CustomerQuery::PRICING, "bulk discount", nullptr)));
        }
        
        SUBCASE("testing the manager handles complaints appropriately") {
            Manager manager("Test Manager", 1, nullptr, "Customer Service");
            CHECK_NOTHROW(manager.handleQuery(CustomerQuery(CustomerQuery::COMPLAINT, "complaint", nullptr)));
        }
    }
}

/*FACTORY METHOD (for growing staff)
only tested the createStaff, careForPlants, notify, create staff, add task and setInventoryCoordinator*/

TEST_SUITE("testing the staff core functions testing") {

    TEST_CASE("testing the factory createStaff() function") {
        SUBCASE("testing the GardenerFactory creates unique gardeners") {
            GardenerFactory factory;
            
            Staff* gardener1 = factory.createStaff();
            Staff* gardener2 = factory.createStaff();
            
            CHECK(gardener1 != nullptr);
            CHECK(gardener2 != nullptr);
            CHECK(gardener1 != gardener2);
            
            CHECK(gardener1->getName() != gardener2->getName());
            CHECK(gardener1->getId() != gardener2->getId());
            
            Gardener* g1 = dynamic_cast<Gardener*>(gardener1);
            Gardener* g2 = dynamic_cast<Gardener*>(gardener2);
            CHECK(g1 != nullptr);
            CHECK(g2 != nullptr);
            
            delete gardener1;
            delete gardener2;
        }
        
        SUBCASE("testing the SalesAssistantFactory creates unique SalesAssistants") {
            SalesAssistantFactory factory;
            
            Staff* sales1 = factory.createStaff();
            Staff* sales2 = factory.createStaff();
            
            CHECK(sales1 != nullptr);
            CHECK(sales2 != nullptr);
            CHECK(sales1->getId() >= 2000);
            CHECK(sales2->getId() >= 2000);
            
            SalesAssistant* s1 = dynamic_cast<SalesAssistant*>(sales1);
            CHECK(s1 != nullptr);
            
            delete sales1;
            delete sales2;
        }
        
        SUBCASE("testing the ManagerFactory creates unique Managers") {
            ManagerFactory factory;
            
            Staff* manager1 = factory.createStaff();
            Staff* manager2 = factory.createStaff();
            
            CHECK(manager1 != nullptr);
            CHECK(manager2 != nullptr);
            CHECK(manager1->getId() >= 3000);
            CHECK(manager2->getId() >= 3000);
            
            Manager* m1 = dynamic_cast<Manager*>(manager1);
            CHECK(m1 != nullptr);
            
            delete manager1;
            delete manager2;
        }
        
        SUBCASE("testing the DeliveryStaffFactory creates unique DeliveryStaff") {
            DeliveryStaffFactory factory;
            
            Staff* delivery1 = factory.createStaff();
            Staff* delivery2 = factory.createStaff();
            
            CHECK(delivery1 != nullptr);
            CHECK(delivery2 != nullptr);
            CHECK(delivery1->getId() >= 4000);
            
            DeliveryStaff* d1 = dynamic_cast<DeliveryStaff*>(delivery1);
            CHECK(d1 != nullptr);
            
            delete delivery1;
            delete delivery2;
        }
        
        SUBCASE("testing the factory id auto increment") {
            GardenerFactory factory;
            
            Staff* gardener1 = factory.createStaff();
            int id1 = gardener1->getId();
            
            Staff* gardener2 = factory.createStaff();
            int id2 = gardener2->getId();
            
            CHECK(id2 == id1 + 1);
            
            delete gardener1;
            delete gardener2;
        }
    }

    TEST_CASE("testing the careForPlants() function") {
        SUBCASE("testing the gardener careForPlants shows expertise") {
            Gardener gardener("Expert Gardener", 1001, nullptr, "Ornamental Plants");
            CHECK_NOTHROW(gardener.careForPlants());
        }
        
        SUBCASE("testing the SalesAssistant careForPlants shows customer focus") {
            SalesAssistant sales("Friendly Sales", 2001, nullptr, 0.05);
            CHECK_NOTHROW(sales.careForPlants());
        }
        
        SUBCASE("testing the manager careForPlants shows department") {
            Manager manager("Store Manager", 3001, nullptr, "Retail Operations");
            CHECK_NOTHROW(manager.careForPlants());
        }
        
        SUBCASE("testing the DeliveryStaff careForPlants shows vehicle") {
            DeliveryStaff delivery("Fast Delivery", 4001, nullptr, "Refrigerated Truck");
            CHECK_NOTHROW(delivery.careForPlants());
        }
        
        SUBCASE("testing all staff types implement careForPlants without crashing") {
            Gardener gardener("Test Gardener", 1002, nullptr, "General");
            SalesAssistant sales("Test Sales", 2002, nullptr, 0.03);
            Manager manager("Test Manager", 3002, nullptr, "Test Dept");
            DeliveryStaff delivery("Test Delivery", 4002, nullptr, "Van");
            
            CHECK_NOTHROW(gardener.careForPlants());
            CHECK_NOTHROW(sales.careForPlants());
            CHECK_NOTHROW(manager.careForPlants());
            CHECK_NOTHROW(delivery.careForPlants());
        }
    }

    TEST_CASE("testing the notify() function") {
        SUBCASE("testing the staff with mediator can notify events") {
            NurseryInventoryMediator mediator;
            Gardener gardener("Notifying Gardener", 1003, &mediator, "General");
            
            Rose testPlant("Test Plant", 10.0, "TP001");
            
            CHECK_NOTHROW(gardener.notify("new shipment", &testPlant, 100));
            CHECK_NOTHROW(gardener.notify("plant moved to sales", &testPlant, 50));
        }
        
        SUBCASE("testing the staff without mediator shows error") {
            Gardener gardener("Lone Gardener", 1004, nullptr, "General");
            Orchid testPlant("Test Plant", 10.0, "TP002");
            
            CHECK_NOTHROW(gardener.notify("new shipment", &testPlant, 100));
        }
        
        SUBCASE("testing the different event types work correctly") {
            NurseryInventoryMediator mediator;
            SalesAssistant sales("Test Sales", 2003, &mediator, 0.05);
            Jade testPlant("Rose Plant", 15.0, "R001");
            
            CHECK_NOTHROW(sales.notify("plant sold", &testPlant, 10));
            CHECK_NOTHROW(sales.notify("check stock", &testPlant, 0));
        }
        
        SUBCASE("testing the null plant handling in notify") {
            NurseryInventoryMediator mediator;
            Manager manager("Test Manager", 3003, &mediator, "Operations");
            
            CHECK_NOTHROW(manager.notify("new shipment", nullptr, 50));
            CHECK_NOTHROW(manager.notify("check stock", nullptr, 0));
        }
        
        SUBCASE("testing the all staff types can use notify") {
            NurseryInventoryMediator mediator;
            
            Gardener gardener("G", 1005, &mediator, "General");
            SalesAssistant sales("S", 2004, &mediator, 0.05);
            Manager manager("M", 3004, &mediator, "Ops");
            DeliveryStaff delivery("D", 4003, &mediator, "Truck");
            
            Jacaranda testPlant("Test Plant", 10.0, "T001");
            
            CHECK_NOTHROW(gardener.notify("new shipment", &testPlant, 100));
            CHECK_NOTHROW(sales.notify("plant sold", &testPlant, 20));
            CHECK_NOTHROW(manager.notify("check stock", &testPlant, 0));
            CHECK_NOTHROW(delivery.notify("customer delivery", &testPlant, 15));
        }
    }

    TEST_CASE("testing the setInventoryCoordinator() function") {
        SUBCASE("testing the set coordinator for staff without one") {
            Gardener gardener("Coord Gardener", 1009, nullptr, "General");
            NurseryInventoryMediator mediator;
            
            CHECK_NOTHROW(gardener.setInventoryCoordinator(&mediator));
            
            Apple testPlant("Test Plant", 10.0, "T002");
            CHECK_NOTHROW(gardener.notify("new shipment", &testPlant, 100));
        }
        
        SUBCASE("testing the change existing coordinator") {
            NurseryInventoryMediator mediator1;
            NurseryInventoryMediator mediator2;
            SalesAssistant sales("Change Sales", 2007, &mediator1, 0.05);
            
            CHECK_NOTHROW(sales.setInventoryCoordinator(&mediator2));
            
            Lotus testPlant("Test Plant", 10.0, "T003");
            CHECK_NOTHROW(sales.notify("plant sold", &testPlant, 5));
        }
        
        SUBCASE("testing the set coordinator to nullptr") {
            NurseryInventoryMediator mediator;
            Manager manager("Null Manager", 3007, &mediator, "Operations");
            
            CHECK_NOTHROW(manager.setInventoryCoordinator(nullptr));
            
            Protea testPlant("Test Plant", 10.0, "T004");
            CHECK_NOTHROW(manager.notify("check stock", &testPlant, 0));
        }
        
        SUBCASE("testing the all staff types can set coordinator") {
            NurseryInventoryMediator mediator;
            
            Gardener gardener("G", 1010, nullptr, "General");
            SalesAssistant sales("S", 2008, nullptr, 0.05);
            Manager manager("M", 3008, nullptr, "Ops");
            DeliveryStaff delivery("D", 4005, nullptr, "Truck");
            
            CHECK_NOTHROW(gardener.setInventoryCoordinator(&mediator));
            CHECK_NOTHROW(sales.setInventoryCoordinator(&mediator));
            CHECK_NOTHROW(manager.setInventoryCoordinator(&mediator));
            CHECK_NOTHROW(delivery.setInventoryCoordinator(&mediator));
        }
        
        SUBCASE("testing the coordinator enables inventory integration") {
            NurseryInventoryMediator mediator;
            Gardener gardener("Integrate Gardener", 1011, nullptr, "General");
            
            Pine testPlant("Rose Plant", 15.0, "R002");
            
            CHECK_NOTHROW(gardener.setInventoryCoordinator(&mediator));
            CHECK_NOTHROW(gardener.notify("new shipment", &testPlant, 200));
        }
    }

    TEST_CASE("testing the integration: staff workflow without tasks") {
        SUBCASE("testing the create staff, set coordinator, and use notify") {
            GardenerFactory factory;
            Staff* staff = factory.createStaff();
            
            NurseryInventoryMediator mediator;
            staff->setInventoryCoordinator(&mediator);
            
            Cacti testPlant("Integration Plant", 12.0, "IP001");
            CHECK_NOTHROW(staff->notify("new shipment", &testPlant, 150));
            
            CHECK_NOTHROW(staff->careForPlants());
            
            delete staff;
        }
        
        SUBCASE("testing multiple staff types working together") {
            NurseryInventoryMediator mediator;
            
            Gardener gardener("Team Gardener", 1012, &mediator, "General");
            SalesAssistant sales("Team Sales", 2009, &mediator, 0.05);
            
            Rose rose("Rose", 15.0, "R003");
            gardener.notify("new shipment", &rose, 200);
            sales.notify("plant sold", &rose, 50);
            
            CHECK_NOTHROW(gardener.careForPlants());
            CHECK_NOTHROW(sales.careForPlants());
        }
    }

    TEST_CASE("testing the edge cases and error conditions") {
        SUBCASE("Factory creates staff with valid state") {
            GardenerFactory factory;
            Staff* staff = factory.createStaff();
            
            CHECK(staff != nullptr);
            CHECK_FALSE(staff->getName().empty());
            CHECK(staff->getId() > 0);
            
            delete staff;
        }
        
        SUBCASE("testing the staff operations with null mediator") {
            Gardener gardener("Null Mediator Gardener", 1013, nullptr, "General");
            
            CHECK_NOTHROW(gardener.careForPlants());
            
            Orchid testPlant("Test Plant", 10.0, "T005");
            CHECK_NOTHROW(gardener.notify("test event", &testPlant, 0));
        }
        
        SUBCASE("testing the coordinator switching mid operation") {
            NurseryInventoryMediator mediator1;
            NurseryInventoryMediator mediator2;
            DeliveryStaff delivery("Switch Delivery", 4006, &mediator1, "Truck");
            
            Jade testPlant("Switch Plant", 10.0, "SP001");
            
            CHECK_NOTHROW(delivery.notify("customer delivery", &testPlant, 10));
            CHECK_NOTHROW(delivery.setInventoryCoordinator(&mediator2));
            CHECK_NOTHROW(delivery.notify("customer delivery", &testPlant, 5));
        }
    }
}