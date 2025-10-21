#include "SoldState.h"
#include "PlantContext.h"
#include <iostream>

SoldState::SoldState()
    : saleDte(""), soldPrice(0.0), soldSeason(""), fsoldSequence(0.0),
      fgrwContext(""), fharvestContext(nullptr), fcheckReadiness(nullptr),
      fgetStateName("Sold"), fgetSoldPrice(0.0), fgetData("") {}

SoldState::~SoldState() {}

void SoldState::checkReadiness() {
    std::cout << "Plant has been sold. No further actions needed." << std::endl;
}

void SoldState::harvest(PlantContext*) {
    std::cout << "Plant has already been harvested and sold." << std::endl;
}

void SoldState::grow(PlantContext*) {
    std::cout << "Plant lifecycle is complete. No further growth." << std::endl;
}

std::string SoldState::getStateName() {
    return "Sold";
}

bool SoldState::isValid() {
    return soldPrice > 0.0;
}

bool SoldState::ageDataValid() {
    return true;
}

double SoldState::soldSequence(double price, std::string date, std::string season) {
    soldPrice = price;
    saleDte = date;
    soldSeason = season;
    std::cout << "Plant sold for $" << price << " on " << date 
              << " during " << season << " season" << std::endl;
    return soldPrice;
}

double SoldState::getSoldPrice() {
    return soldPrice;
}

std::string SoldState::getData() {
    return "Sale Date: " + saleDte + ", Price: $" + std::to_string(soldPrice) 
           + ", Season: " + soldSeason;
}

void SoldState::setSaleDte(const std::string& date) { saleDte = date; }
void SoldState::setSoldPrice(double price) { soldPrice = price; }
void SoldState::setSoldSeason(const std::string& season) { soldSeason = season; }