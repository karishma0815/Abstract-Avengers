/*Abstract Avengers*/

/**
 * @file Arrangement.h
 * @brief Simple container of personalized Items built via the Builder; supports deep clone.
 * @author Taskeen Abdoola
 * @date 2025-10-19
 */

#ifndef ARRANGEMENT_H
#define ARRANGEMENT_H

#include "Item.h"

#include <vector>
#include <memory>
#include <string>

class Arrangement 
{
public:
    //Default construct an empty arrangement.
    Arrangement() = default;

    //Deep-copy construct (performs deep clone of all contained Items).
    Arrangement(const Arrangement& other);

    Arrangement& operator=(const Arrangement& other) = delete;          
    Arrangement(Arrangement&&) noexcept = default;                       
    Arrangement& operator=(Arrangement&&) noexcept = default;            

    //Add a personalized item.
    void add(std::unique_ptr<Item> item);

    //Remove by index; returns false if out of range.
    bool remove(std::size_t index);

    //Number of items in the arrangement.
    std::size_t count() const 
    {
        return components.size(); 
    }

    Item* getComponent(std::size_t index) const;

    //Clear all items.
    void clear() 
    { 
        components.clear(); 
    }

    //Sum of all item prices.
    double totalPrice() const;

    //Human readable summary (e.g., "Rose + Pot(blue), Wrap('Happy Birthday') | ...").
    std::string describe(const std::string& sep = " | ") const;

    //True if every component reports readyForSale().
    bool readyForSale() const;

    //Deep clone of the arrangement (clones each contained Item).
    std::unique_ptr<Arrangement> clone() const;

private:
    std::vector<std::unique_ptr<Item>> components;
};

#endif
