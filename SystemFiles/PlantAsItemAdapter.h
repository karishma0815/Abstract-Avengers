#pragma once
#include "Item.h"
#include "Plant.h"
#include <string>

class PlantAsItemAdapter : public Item {
public:
    explicit PlantAsItemAdapter(Plant* plant);

    double priceFunc() const override;
    std::string describe() const override;
    bool readyForSale() const override;

    Plant* underlying() const; // non-owning

private:
    Plant* plant_;
};
