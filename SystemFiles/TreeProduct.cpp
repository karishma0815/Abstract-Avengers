#include "TreeProduct.h"

TreeProduct::TreeProduct(std::string name, double price) 
    : name(name), price(price) {
}

TreeProduct::~TreeProduct() {
}

std::string TreeProduct::getPlantType() const {
    return "Tree";
}

std::string TreeProduct::getName() const {
    return name;
}

void TreeProduct::add(TreeProduct* plant) {
    // Default implementation
}

void TreeProduct::remove(TreeProduct* plant) {
    // Default implementation
}

double TreeProduct::getPrice() const{
    return price;
}
