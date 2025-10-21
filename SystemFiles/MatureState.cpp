#include "MatureState.h"
#include "PlantContext.h"
#include "ReadyForSaleState.h"
#include <iostream>

MatureState::MatureState()
    : daysinState(0), isPrimeForSale(false), isInInSeason(false),
      maturedStateSeason(""), fwaitContext(nullptr), fgrwContext(nullptr),
      fharvestContext(nullptr), fcheckReadiness(nullptr), fgetStateName("Mature"),
      fisValid(true), fgetDaysinState(0), fisPrimeForSale(false),
      fevaluateSaleReadiness("") {}

MatureState::~MatureState() {}

void MatureState::checkReadiness() {
    if (isPrimeForSale && isInInSeason) {
        std::cout << "Plant is ready for sale" << std::endl;
    } else {
        std::cout << "Plant is maturing but not ready for sale yet" << std::endl;
    }
}

void MatureState::harvest(PlantContext* ctx) {
    if (isPrimeForSale) {
        ctx->transitionTo(new ReadyForSaleState());
    } else {
        std::cout << "Plant is not ready for harvest yet" << std::endl;
    }
}

void MatureState::grow(PlantContext*) {
    daysinState++;
    if (daysinState >= 30 && isInInSeason) {
        isPrimeForSale = true;
    }
}

std::string MatureState::getStateName() {
    return fgetStateName;
}

bool MatureState::isValid() {
    return fisValid;
}

bool MatureState::ageDataValid() {
    return daysinState >= 0;
}

void MatureState::wait(PlantContext*) {
    std::cout << "Mature plant is waiting..." << std::endl;
}

int MatureState::getDaysinState() {
    return daysinState;
}

bool MatureState::getIsPrimeForSale() {
    return isPrimeForSale;
}

std::string MatureState::evaluateSaleReadiness(int) {
    if (isPrimeForSale && isInInSeason) {
        return "Ready for sale";
    }
    return "Not ready for sale";
}

void MatureState::setDaysinState(int days) { daysinState = days; }
void MatureState::setIsPrimeForSale(bool prime) { isPrimeForSale = prime; }
void MatureState::setIsInInSeason(bool season) { isInInSeason = season; }
void MatureState::setMaturedStateSeason(const std::string& season) { maturedStateSeason = season; }