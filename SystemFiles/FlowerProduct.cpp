#include "FlowerProduct.h"

FlowerProduct::FlowerProduct(std::string name, double price) 
    : name(name), price(price) {
}

FlowerProduct::~FlowerProduct() {
}

std::string FlowerProduct::getPlantType() const {
    return "Flower";
}

std::string FlowerProduct::getName() const {
    return name;
}

void FlowerProduct::add(FlowerProduct* plant) {
    // Default implementation
}

void FlowerProduct::remove(FlowerProduct* plant) {
    // Default implementation
}