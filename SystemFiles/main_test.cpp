#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "PlantContext.h"
#include "SeedlingState.h"
#include "FloweringState.h"
#include "MatureState.h"
#include "ReadyForSaleState.h"
#include "SoldState.h"
#include "Plant.h"

// ---------------------
// Plant Tests
// ---------------------
TEST_CASE("Plant initializes correctly") {
    Plant plant("Rose", true, "R001", 8, 5);

    CHECK(plant.getName() == "Rose");
    CHECK(plant.isFertilized() == true);
    CHECK(plant.getPlantID() == "R001");
    CHECK(plant.getExposureSunlightHours() == 8);
    CHECK(plant.getLastWaterLevel() == 5);
}

TEST_CASE("Plant setters update correctly") {
    Plant plant("Tulip", false, "T001", 6, 3);

    plant.setExposureSunlightHours(9);
    plant.setLastWaterLevel(7);
    plant.setFertilized(true);

    CHECK(plant.getExposureSunlightHours() == 9);
    CHECK(plant.getLastWaterLevel() == 7);
    CHECK(plant.isFertilized() == true);
}

// ---------------------
// State Transition Tests
// ---------------------
TEST_CASE("SeedlingState transitions to FloweringState") {
    PlantContext context("Sunflower", "Spring", "dummy", 10.0);

    // Seedling requires proper care and min days to grow
    SeedlingState* seedState = dynamic_cast<SeedlingState*>(context.getState());
    if (seedState) {
        seedState->setMinDaysInState(3);
        seedState->setHasReceivedProperCare(true);
    }

    context.ageState(3); // age enough to trigger transition
    CHECK(context.getCurrentStateName() == "Flowering");
}

TEST_CASE("FloweringState transitions to MatureState") {
    PlantContext context("Rose", "Summer", "dummy", 15.0);

    FloweringState* fState = new FloweringState();
    fState->setIsInSeason(true);
    fState->setRequestDays(5);
    context.transitionTo(fState);

    context.ageState(5); // grow enough days
    CHECK(context.getCurrentStateName() == "Mature");
}

TEST_CASE("MatureState becomes ReadyForSaleState after harvest") {
    PlantContext context("Lavender", "Summer", "dummy", 20.0);

    MatureState* mState = new MatureState();
    mState->setIsInInSeason(true);
    mState->setIsPrimeForSale(true);
    context.transitionTo(mState);

    context.harvest(); // triggers ReadyForSale
    CHECK(context.getCurrentStateName() == "Ready for Sale");
}

TEST_CASE("ReadyForSaleState transitions to SoldState on harvest") {
    PlantContext context("Daisy", "Spring", "dummy", 25.0);

    ReadyForSaleState* rState = new ReadyForSaleState();
    rState->setPrice(30.0);
    context.transitionTo(rState);

    context.harvest(); // triggers Sold
    CHECK(context.getCurrentStateName() == "Sold");
}

TEST_CASE("SoldState returns correct price") {
    SoldState sold;
    double price = sold.soldSequence(100.0, "2025-10-27", "Spring");

    CHECK(price == doctest::Approx(100.0));
}

// ---------------------
// Full Transition Simulation
// ---------------------
TEST_CASE("PlantContext manages full lifecycle correctly") {
    PlantContext context("Sunflower", "Spring", "dummy", 12.0);

    SeedlingState* seedState = dynamic_cast<SeedlingState*>(context.getState());
    if (seedState) {
        seedState->setMinDaysInState(2);
        seedState->setHasReceivedProperCare(true);
    }

    context.ageState(2);
    CHECK(context.getCurrentStateName() == "Flowering");

    FloweringState* fState = dynamic_cast<FloweringState*>(context.getState());
    if (fState) {
        fState->setIsInSeason(true);
        fState->setRequestDays(3);
    }
    context.ageState(3);
    CHECK(context.getCurrentStateName() == "Mature");

    MatureState* mState = dynamic_cast<MatureState*>(context.getState());
    if (mState) {
        mState->setIsInInSeason(true);
        mState->setIsPrimeForSale(true);
    }
    context.harvest();
    CHECK(context.getCurrentStateName() == "Ready for Sale");

    context.harvest();
    CHECK(context.getCurrentStateName() == "Sold");
}
