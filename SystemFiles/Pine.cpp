// Pine.cpp
#include "Pine.h"
#include "Plant.h"

Pine::Pine(std::string name, double price, std::string species)
    : Tree(name, price, species) {
        // plant = new Plant(name, false, "PINE_" + std::to_string(rand() % 1000), 30, 5);  

}

Pine::~Pine() {
    delete plant;
}

std::string Pine::getPlantType() const{
    return "Pine";
}

Plant* Pine::getPlant() const {
    return plant;
}