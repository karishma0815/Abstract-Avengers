#include "PlantAsItemAdapter.h"

PlantAsItemAdapter::PlantAsItemAdapter(Plant* plant) : plant_(plant) {}

double PlantAsItemAdapter::priceFunc() const 
{ 
    return plant_ ? plant_->getPrice() : 0.0; 
}

std::string PlantAsItemAdapter::describe() const 
{ 
    return plant_ ? plant_->getName() : "Unknown Plant"; 
}

bool PlantAsItemAdapter::readyForSale() const 
{ 
    return plant_ != nullptr; 
}

Plant* PlantAsItemAdapter::underlying() const 
{ 
    return plant_; 
} 
