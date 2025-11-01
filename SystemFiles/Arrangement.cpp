/*Abstract Avengers*/

/**
 * @file Arrangement.cpp
 * @brief Implementation of Arrangement.
 */

#include "Arrangement.h"
#include <sstream>

Arrangement::Arrangement(const Arrangement& other) 
{
    components.reserve(other.components.size());
    for (const auto& it : other.components) 
    {
        //Item::clone() returns std::unique_ptr<Item>
        components.emplace_back(it->clone());
    }
}

void Arrangement::add(std::unique_ptr<Item> item) 
{
    components.emplace_back(std::move(item));
}

bool Arrangement::remove(std::size_t index) 
{
    if (index >= components.size()) 
    {
        return false;
    }
    components.erase(components.begin() + static_cast<std::ptrdiff_t>(index));
    return true;
}

Item* Arrangement::getComponent(std::size_t index) const 
{
    if (index >= components.size()) 
    {
        return nullptr;
    }
    return components[index].get();
}

double Arrangement::totalPrice() const 
{
    double sum = 0.0;
    for (const auto& it : components) 
    {
        sum += it->priceFunc();
    }
    return sum;
}

std::string Arrangement::describe(const std::string& sep) const 
{
    std::ostringstream os;
    for (std::size_t i = 0; i < components.size(); ++i) 
    {
        os << components[i]->describe();
        if (i + 1 < components.size()) 
        {
            os << sep;
        }
    }
    return os.str();
}

bool Arrangement::readyForSale() const 
{
    for (const auto& it : components) 
    {
        if (!it->readyForSale()) 
        {
            return false;
        }
    }
    return true;
}

std::unique_ptr<Arrangement> Arrangement::clone() const 
{
    return std::unique_ptr<Arrangement>(new Arrangement(*this));
}