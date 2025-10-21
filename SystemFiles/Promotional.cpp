#include"Promotional.h"

Promotional::Promotional(){}

Promotional::~Promotional(){}

double Promotional::calculatePrice(int numberOfPlants,double basePrice,std::string coupon){
    if ((coupon=="Nusery1@:)")||(coupon=="Nusery1@;)"))
    {
        std::cout<<"Now you get 90'%' off ;) : ";
        return basePrice*0.90;
    }
    else{
        std::cout<<"Incorrect Promo code :( : ";
        return basePrice;
    }   
}