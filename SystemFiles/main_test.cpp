#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "SeedlingState.h"
#include "FloweringState.h"
#include "MatureState.h"
#include "ReadyForSaleState.h"
#include "SoldState.h"
#include "PlantContext.h"

// ---------------------
// State Transition Tests
// ---------------------
TEST_CASE("SeedlingState transitions to FloweringState") {
    PlantContext context("Flower", "Dummy", 10.0, "Sunflower");

    SeedlingState* seedState = dynamic_cast<SeedlingState*>(context.getState());
    REQUIRE(seedState != nullptr);

    seedState->setMinDaysInState(3);
    seedState->setHasReceivedProperCare(true);

    context.ageState(3);
    CHECK(context.getCurrentStateName() == "Flowering");
}

TEST_CASE("FloweringState transitions to MatureState") {
    PlantContext context("Flower", "Dummy", 10.0, "Rose");

    FloweringState* fState = new FloweringState();
    fState->setIsInSeason(true);
    fState->setRequestDays(5);
    context.transitionTo(fState);

    context.ageState(5);
    CHECK(context.getCurrentStateName() == "Mature");
}

TEST_CASE("MatureState becomes ReadyForSaleState after harvest") {
    PlantContext context("Flower", "Dummy", 10.0, "Lavender");

    MatureState* mState = new MatureState();
    mState->setIsInInSeason(true);
    mState->setIsPrimeForSale(true);
    context.transitionTo(mState);

    context.harvest();
    CHECK(context.getCurrentStateName() == "Ready for Sale");
}

TEST_CASE("ReadyForSaleState transitions to SoldState on harvest") {
    PlantContext context("Flower", "Dummy", 10.0, "Daisy");

    ReadyForSaleState* rState = new ReadyForSaleState();
    rState->setPrice(30.0);
    context.transitionTo(rState);

    context.harvest();
    CHECK(context.getCurrentStateName() == "Sold");
}

TEST_CASE("SoldState returns correct price") {
    SoldState sold;
    double price = sold.soldSequence(100.0, "2025-10-27", "Spring");
    CHECK(price == doctest::Approx(100.0));
}

TEST_CASE("Full lifecycle simulation") {
    PlantContext context("Flower", "Dummy", 12.0, "Sunflower");

    // Seedling -> Flowering
    SeedlingState* seedState = dynamic_cast<SeedlingState*>(context.getState());
    REQUIRE(seedState != nullptr);
    seedState->setMinDaysInState(2);
    seedState->setHasReceivedProperCare(true);
    context.ageState(2);
    CHECK(context.getCurrentStateName() == "Flowering");

    // Flowering -> Mature
    FloweringState* fState = dynamic_cast<FloweringState*>(context.getState());
    REQUIRE(fState != nullptr);
    fState->setIsInSeason(true);
    fState->setRequestDays(3);
    context.ageState(3);
    CHECK(context.getCurrentStateName() == "Mature");

    // Mature -> Ready for Sale
    MatureState* mState = dynamic_cast<MatureState*>(context.getState());
    REQUIRE(mState != nullptr);
    mState->setIsInInSeason(true);
    mState->setIsPrimeForSale(true);
    context.harvest();
    CHECK(context.getCurrentStateName() == "Ready for Sale");

    // Ready for Sale -> Sold
    context.harvest();
    CHECK(context.getCurrentStateName() == "Sold");
}
