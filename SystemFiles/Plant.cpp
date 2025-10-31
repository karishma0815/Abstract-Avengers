#include "Plant.h"
#include <iostream>
#include <iomanip>

Plant::Plant(std::string name, bool fert, std::string id, int sunHours, int waterLevel,double price)
    : name(name), fertilized(fert), plantID(id), 
      exposureSunlightHours(sunHours), lastWaterLevel(waterLevel),price(price), isAlive(true) {}

void Plant::setCareInstructions(const std::string& instructions) {
    // Assuming careInstruc is a member variable of Plant
    careInstruc = instructions;
}

double Plant::getPrice() const {
    return price;
}

void Plant::setPrice(double price) {
    this->price = price;
}

bool Plant::getIsAlive() const{
    return isAlive;
}
