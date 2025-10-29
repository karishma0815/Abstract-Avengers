// Protea.cpp
#include "Protea.h"
#include "Plant.h"

Protea::Protea(std::string name, double price, std::string species)
    : Flower(name, price, species) {
    //    plant = new Plant(name, false, "PROTEA_" + std::to_string(rand() % 1000), 10, 4);         

}

Protea::~Protea() {
    delete plant;
}

std::string Protea::getPlantType() const {
    return "Protea";
}

Plant* Protea::getPlant() const {
    return plant;
}