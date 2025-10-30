/*Abstract Avengers*/

/**
 * @file DecorativePot.h
 * @brief ConcreteDecorator adding a decorative pot
 * @author Taskeen Abdoola
 * @date 2025-10-12
 */

#ifndef DECORATIVEPOT_H
#define DECORATIVEPOT_H

#include "ItemDecorator.h"

#include <string>

class DecorativePot : public ItemDecorator
{
    public:
        DecorativePot(std::unique_ptr<Item> dec, std::string color, double extra);

        double price() const override;
        std::string describe() const override;
        bool readyForSale() const override;

        std::unique_ptr<Item> clone() const override; //prototype
    
        const std::string& colorFunc() const;
        double extraFunc() const;

    private:
        std::string color;
        double extra;
};

#endif