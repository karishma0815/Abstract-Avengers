#include "Plant.h"

Plant::Plant(std::string name, bool fert, std::string id, int sunHours, int waterLevel,int price)
    : name(name), fertilized(fert), plantID(id), 
      exposureSunlightHours(sunHours), lastWaterLevel(waterLevel),price(price) {}

std::string Plant::getName() { 
    return name; 
}

bool Plant::isFertilized() { 
    return fertilized; 
}

std::string Plant::getPlantID() { 
    return plantID; 
}

int Plant::getExposureSunlightHours() { 
    return exposureSunlightHours; 
}

int Plant::getLastWaterLevel() { 
    return lastWaterLevel; 
}

void Plant::setName(const std::string& n) { 
    name = n; 
}

void Plant::setFertilized(bool fert) { 
    fertilized = fert; 
}

void Plant::setPlantID(const std::string& id) { 
    plantID = id; 
}

void Plant::setExposureSunlightHours(int hours) { 
    exposureSunlightHours = hours; 
}

void Plant::setLastWaterLevel(int level) { 
    lastWaterLevel = level; 
}

std::string Plant::getCareInstructions() const {
    // If explicit care instructions were set, return them (preferred).
    if (!careInstruc.empty()) {
        return careInstruc;
    }

    // Otherwise build a default care description from internal fields.
    std::string careInstruc2 = "Water level be maintained at " + std::to_string(lastWaterLevel) +
        " and sunlight exposure should be around " + std::to_string(exposureSunlightHours) + " hours daily.";
    if (fertilized) {
        careInstruc2 += " This plant is fertilized.";
    } else {
        careInstruc2 += " This plant is not fertilized.";
    }
    return careInstruc2;
}

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