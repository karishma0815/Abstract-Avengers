#include "Pine.h"

Pine::Pine(std::string name, double price, std::string species)
    : Tree(name, price, species) {
}

Pine::~Pine() {
}

std::string Pine::getPlantType() const {
    return "Pine";
}