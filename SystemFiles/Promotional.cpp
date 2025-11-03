#include "Promotional.h"

Promotional::Promotional(){}

Promotional::~Promotional(){}

// Treat basePrice as the current CART TOTAL
double Promotional::calculatePrice(int /*numberOfPlants*/, double basePrice, std::string coupon){
    // Accepted promo codes (note: original code had "Nusery"; preserve both variants)
    if ((coupon == "Nusery1@:)") || (coupon == "Nusery1@;)") || (coupon == "Nursery1@:)"))
    {
        std::cout << "Promo applied (10% off): ";
        return basePrice * 0.90; // 10% off
    }
    else{
        std::cout << "Incorrect promo code – no discount: ";
        return basePrice;
    }
}