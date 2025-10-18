#include "Plant.h"

Plant::Plant(std::string name, bool fert, std::string id, int sunHours, int waterLevel)
    : name(name), fertilized(fert), plantID(id), 
      exposureSunlightHours(sunHours), lastWaterLevel(waterLevel) {}

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