/*Abstract Avengers*/

/**
 * @file GiftWrap.h
 * @brief ConcreteDecorator adding a gift wrap and optional message
 * @author Taskeen Abdoola
 * @date 2025-10-12
 */

#ifndef GIFTWRAP_H
#define GIFTWRAP_H

#include "ItemDecorator.h"

#include <string>

class GiftWrap : public ItemDecorator
{
    public:
        GiftWrap(std::unique_ptr<Item> dec, std::string message, double extra);
        double price() const override;
        std::string describe() const override;
        bool readyForSale() const override;
        
        std::unique_ptr<Item> clone() const override; //prototype
        
        const std::string& messageFunc() const;
        double extraFunc() const;
    
    private:
        std::string message;
        double extra;
        
};

#endif