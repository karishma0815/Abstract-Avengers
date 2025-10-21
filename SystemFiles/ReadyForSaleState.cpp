#include "ReadyForSaleState.h"
#include "PlantContext.h"
#include "SoldState.h"
#include <iostream>
#include <sstream>

ReadyForSaleState::ReadyForSaleState()
    : daysinState(0), price(0.0), season(""), prepareSale(""),
      fwaitContext(nullptr), fgrwContext(nullptr), fharvestContext(nullptr),
      fcheckReadiness(nullptr), fgetStateName("Ready for Sale"), fisValid(true),
      fgetDaysinState(0), fgetPrice(0.0) {}

ReadyForSaleState::~ReadyForSaleState() {}

void ReadyForSaleState::checkReadiness() {
    std::cout << "Plant is ready for sale at price: $" << price << std::endl;
}

void ReadyForSaleState::harvest(PlantContext* ctx) {
    std::cout << "Plant has been sold! Transitioning to Sold state." << std::endl;
    ctx->transitionTo(new SoldState());
}

void ReadyForSaleState::grow(PlantContext*) {
    std::cout << "Plant is waiting to be sold. No further growth." << std::endl;
}

std::string ReadyForSaleState::getStateName() {
    return "Ready for Sale";
}

bool ReadyForSaleState::isValid() {
    return price > 0.0;
}

bool ReadyForSaleState::ageDataValid() {
    return daysinState >= 0;
}

void ReadyForSaleState::wait(PlantContext*) {
    std::cout << "Plant is waiting for a buyer..." << std::endl;
    daysinState++;
}

int ReadyForSaleState::getDaysinState() {
    return daysinState;
}

double ReadyForSaleState::getPrice() {
    return price;
}

std::string ReadyForSaleState::prepareSaleForSale(double priceVal, std::string seasonVal) {
    price = priceVal;
    season = seasonVal;
    std::ostringstream oss;
    oss << "Plant prepared for sale at $" << price << " during " << season;
    return oss.str();
}

void ReadyForSaleState::setDaysinState(int days) { daysinState = days; }
void ReadyForSaleState::setPrice(double p) { price = p; }
void ReadyForSaleState::setSeason(const std::string& s) { season = s; }
void ReadyForSaleState::setPrepareSale(const std::string& prep) { prepareSale = prep; }