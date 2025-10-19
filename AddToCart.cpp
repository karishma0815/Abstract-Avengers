#include"AddToCart.h"

AddToCart::AddToCart(){}

AddToCart::~AddToCart() {}

void AddToCart::execute(Plant* plant, PlantInventory* cartInven) {
    if ((cartInven != nullptr)&& (plant != nullptr)) {
        std::cout << "Adding plant of type: " << plant->getType() << " to cart." << std::endl;
        // Logic to add the plant to the cart using the 
        //there is no inventory for a customer cart we just add directly

        cartInven->addToCart(plant); // Placeholder for actual addition logic
    }
}