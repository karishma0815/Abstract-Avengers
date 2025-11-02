#include "FloweringState.h"
#include "PlantContext.h"
#include "MatureState.h"
#include <iostream>

FloweringState::FloweringState()
    : daysinState(0), requestDays(0), isInSeason(false), currentSeason(""),
      floweringStrtSeason(""), fwaitContext(nullptr), fgrwContext(nullptr),
      fharvestContext(nullptr), fcheckReadiness(nullptr), fgetStateName("Flowering"),
      fisValid(true), fgetDaysinState(0), fisinSeason(false), fincreaseDay(0) {}

FloweringState::~FloweringState() {}

void FloweringState::checkReadiness() {
    if (isInSeason && daysinState >= requestDays) {
        std::cout << "Plant is ready to transition to mature stage" << std::endl;
    } else {
        std::cout << "Plant needs to continue flowering" << std::endl;
    }
}

bool FloweringState::harvest(PlantContext*) {
 std::cout << "Cannot harvest during flowering stage - too early!\n";
    return false;
}

void FloweringState::grow(PlantContext* ctx) {
    daysinState++;
    if (isInSeason && daysinState >= requestDays) {
        ctx->transitionTo(new MatureState());
    }
}

std::string FloweringState::getStateName() {
    return "Flowering";
}

bool FloweringState::isValid() {
    return daysinState >= 0 && requestDays > 0;
}

bool FloweringState::ageDataValid() {
    return daysinState >= 0;
}

void FloweringState::wait(PlantContext*) {
    std::cout << "Plant is flowering and developing..." << std::endl;
}

int FloweringState::getDaysinState() {
    return daysinState;
}

bool FloweringState::getIsInSeason() {
    return isInSeason;
}

void FloweringState::increaseDay() {
    daysinState++;
}

void FloweringState::setDaysinState(int days) { daysinState = days; }
void FloweringState::setRequestDays(int days) { requestDays = days; }
void FloweringState::setIsInSeason(bool season) { isInSeason = season; }
void FloweringState::setCurrentSeason(const std::string& season) { currentSeason = season; }
void FloweringState::setFloweringStrtSeason(const std::string& season) { floweringStrtSeason = season; }