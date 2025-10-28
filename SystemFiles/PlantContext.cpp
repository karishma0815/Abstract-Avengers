#include "PlantContext.h"
#include "PlantState.h"
#include "SeedlingState.h"
#include <iostream>

PlantContext::PlantContext(Plant* plantInstance, std::string type, 
                           std::string season, double price)
    : currentState(nullptr), fplantType(type), season(season),
      fstateAge(0.0), fstatPrice(price), plant(plantInstance) {
    
    currentState = new SeedlingState();
    currentState->setContext(this);
}

PlantContext::~PlantContext() {
    delete currentState;
    delete plant;
}

void PlantContext::transitionTo(PlantState* state) {
    if (currentState != nullptr) {
        std::cout << "Transitioning from " << currentState->getStateName() 
                  << " to " << state->getStateName() << std::endl;
        delete currentState;
    }
    currentState = state;
    currentState->setContext(this);
}

PlantState* PlantContext::getState() {
    return currentState;
}

void PlantContext::harvest() {
    if (currentState != nullptr) {
        currentState->harvest(this);
    }
}

void PlantContext::checkReadiness() {
    if (currentState != nullptr) {
        currentState->checkReadiness();
    }
}

void PlantContext::ingestPlantType(std::string type, PlantState* state) {
    fplantType = type;
    if (state != nullptr) {
        transitionTo(state);
    }
}

void PlantContext::ageState(int daysToAge) {
    fstateAge += daysToAge;
    if (currentState != nullptr) {
        for (int i = 0; i < daysToAge; i++) {
            currentState->grow(this);
        }
    }
}

int PlantContext::getAge() {
    return static_cast<int>(fstateAge);
}

double PlantContext::getStateAgePrice() {
    return fstatPrice;
}

std::string PlantContext::getPlantName() {
    return plant->getName();
}

std::string PlantContext::getPlantType() {
    return fplantType;
}

std::string PlantContext::getSeason() {
    return season;
}

std::string PlantContext::getCurrentStateName() {
    if (currentState != nullptr) {
        return currentState->getStateName();
    }
    return "No State";
}

bool PlantContext::isReadyForSale() {
    if (currentState != nullptr) {
        return currentState->getStateName() == "Ready for Sale";
    }
    return false;
}

Plant* PlantContext::getPlant() {
    return plant;
}

void PlantContext::setPlantType(const std::string& type) { fplantType = type; }
void PlantContext::setStateAge(double age) { fstateAge = age; }
void PlantContext::setSeason(const std::string& s) { season = s; }
void PlantContext::setStatePrice(double price) { fstatPrice = price; }