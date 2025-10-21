#include"RemoveFromCart.h"

RemoveFromCart::RemoveFromCart() {}

RemoveFromCart::~RemoveFromCart() {}

void RemoveFromCart::execute(Plant* plant, PlantInventory* cartInven){

   if ((cartInven != nullptr)&& (plant != nullptr)) {
        std::cout << "Removing plant of type: " << plant->getName() << " from cart." << std::endl;
        cartInven->removeFromCart(plant);
    }
}

