/*Abstract Avengers*/

/**
 * @file Note.h
 * @brief ConcreteDecorator adding a small note to the arrangement
 * @author Taskeen Abdoola
 * @date 2025-10-12
 */

#ifndef NOTE_H
#define NOTE_H

#include "ItemDecorator.h"

#include <string>

class Note : public ItemDecorator
{
    public:
        Note(std::unique_ptr<Item> dec, std::string text, double extra);
        double price() const override;
        std::string describe() const override;
        bool readyForSale() const override;
        std::unique_ptr<Item> clone() const override;
        const std::string& textFunc() const;
        double extraFunc() const;
    
    private:
        std::string text;
        double extra;
};

#endif