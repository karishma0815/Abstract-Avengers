#include "SeedlingState.h"
#include "PlantContext.h"
#include "FloweringState.h"
#include <iostream>

SeedlingState::SeedlingState() 
    : daysinState(0), requestDays(0), hasReceivedProperCare(false),
      minDaysInState(0), fwaitContext(nullptr), fgrwContext(nullptr),
      fharvestContext(nullptr), fcheckReadiness(nullptr), fgetStateName("Seedling"),
      fisValid(true), fgetDaysinState(0), frequiredDaysInState(0) {}

SeedlingState::~SeedlingState() {}

void SeedlingState::checkReadiness() {
    if (daysinState >= minDaysInState && hasReceivedProperCare) {
        std::cout << "Seedling is ready to transition to flowering stage" << std::endl;
    } else {
        std::cout << "Seedling needs more time and care" << std::endl;
    }
}

bool SeedlingState::harvest(PlantContext*) {
     std::cout << "Cannot harvest a seedling - too early!\n";
    return false;
}

void SeedlingState::grow(PlantContext* ctx) {
    daysinState++;
    if (daysinState >= minDaysInState && hasReceivedProperCare) {
        ctx->transitionTo(new FloweringState());
    }
}

std::string SeedlingState::getStateName() {
    return "Seedling";
}

bool SeedlingState::isValid() {
    return daysinState >= 0 && minDaysInState > 0;
}

bool SeedlingState::ageDataValid() {
    return daysinState >= 0;
}

void SeedlingState::wait(PlantContext*) {
    std::cout << "Seedling is waiting and developing..." << std::endl;
}

int SeedlingState::getDaysinState() {
    return daysinState;
}

int SeedlingState::getRequiredDaysInState() {
    return minDaysInState;
}

void SeedlingState::setDaysinState(int days) { daysinState = days; }
void SeedlingState::setRequestDays(int days) { requestDays = days; }
void SeedlingState::setHasReceivedProperCare(bool care) { hasReceivedProperCare = care; }
void SeedlingState::setMinDaysInState(int days) { minDaysInState = days; }