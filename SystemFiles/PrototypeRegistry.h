/*Abstract Avengers*/

/**
 * @file PrototypeRegistry.h
 * @brief Registry of prototype items
 * @author Taskeen Abdoola
 * @date 2025-10-13
 */

#ifndef PROTOTYPEREGISTRY_H
#define PROTOTYPEREGISTRY_H

#include "Item.h"

#include <memory>
#include <string>
#include <unordered_map>

class Item;

class PrototypeRegistry 
{
    public:
        /**
        * @brief Register/replace a prototype under a key.
        * @param key Lookup key (e.g, species).
        * @param proto Ownership of prototype instance.
        */
        void registerPrototype(std::string key, std::unique_ptr<Item> proto);

        /**
        * @brief Clone the prototype under a key.
        * @param key Lookup key.
        * @return Deep copy or nullptr if key not present.
        */
        std::unique_ptr<Item> cloneOf(const std::string& key) const; //nullptr if not found

        /** @return Whether a prototype exists for key. */
        bool has(const std::string& key) const;

        /** @return Number of registered prototypes. */
        std::size_t size() const;
    
    private:
        std::unordered_map<std::string, std::unique_ptr<Item>> prototypes;
};

#endif