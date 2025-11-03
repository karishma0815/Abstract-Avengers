#include "PlantContext.h"
#include "PlantState.h"
#include "SeedlingState.h"
#include <iostream>

#include "PlantContext.h"
#include "Rose.h"
#include "Lotus.h"
#include "Protea.h"
#include "Apple.h"
#include "Jacaranda.h"
#include "Pine.h"
#include "Cacti.h"
#include "Jade.h"
#include "Orchid.h"
#include <iostream>

PlantContext::PlantContext(const std::string& type, const std::string& name, double price, const std::string& species)
    : fstateAge(0), fspecies(species) 
{
    if (type == "Rose") plant = new Rose(name, price, species);
    else if (type == "Lotus") plant = new Lotus(name, price, species);
    else if (type == "Protea") plant = new Protea(name, price, species);
    else if (type == "Apple") plant = new Apple(name, price, species);
    else if (type == "Jacaranda") plant = new Jacaranda(name, price, species);
    else if (type == "Pine") plant = new Pine(name, price, species);
    else if (type == "Cacti") plant = new Cacti(name, price, species);
    else if (type == "Jade") plant = new Jade(name, price, species);
    else if (type == "Orchid") plant = new Orchid(name, price, species);
    else if (type == "Flower") plant = new Flower(name, price, species);
    else if (type == "Tree") plant = new Tree(name, price, species);
    else if (type == "Succulent") plant = new Succulent(name, price, species);

    else {
        std::cerr << "Unknown plant type: " << type << ". Defaulting to Protea.\n";
        plant = new Protea(name, price, species);
    }

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

bool PlantContext::harvest() {
    if (currentState != nullptr) {
        currentState->harvest(this);
    }
      return false;
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

    for (int i = 0; i < daysToAge; i++) {
        PlantState* oldState = currentState;
        if (currentState != nullptr) {
            currentState->grow(this);

            while (currentState != oldState) {
                oldState = currentState;
                std::cout << "State changed -> " << currentState->getStateName() << "\n";
                currentState->grow(this);
            }
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


