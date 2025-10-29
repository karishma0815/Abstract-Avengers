// Jacaranda.cpp
#include "Jacaranda.h"
#include "Plant.h"

Jacaranda::Jacaranda(std::string name, double price, std::string species)
    : Tree(name, price, species) {
            // plant = new Plant(name, false, "JACARANDA_" + std::to_string(rand() % 1000), 20, 3);

}


Jacaranda::~Jacaranda() {
    delete plant;
}

std::string Jacaranda::getPlantType() const{
    return "Jacaranda";
}

Plant* Jacaranda::getPlant() const {
    return plant;
}