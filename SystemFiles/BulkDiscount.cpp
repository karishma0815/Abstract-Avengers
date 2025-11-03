#include "BulkDiscount.h"

BulkDiscount::BulkDiscount(){}

BulkDiscount::~BulkDiscount(){}

// Treat basePrice as the current CART TOTAL and apply a discount when
// numberOfPlants (cart item count) meets the threshold.
double BulkDiscount::calculatePrice(int numberOfPlants, double basePrice, std::string /*coupon*/){
    const int threshold = 10;       // Bulk discount kicks in at 10+ items
    const double rate   = 0.10;     // 10% off

    if (numberOfPlants >= threshold) {
        std::cout << " Bulk discount applied (10% off): " << std::endl;
        return basePrice * (1.0 - rate);
    }
    // No discount below threshold – return original total
    return basePrice;
}