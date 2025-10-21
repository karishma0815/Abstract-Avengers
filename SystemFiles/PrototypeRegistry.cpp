/*Abstract Avengers*/

/**
 * @file PrototypeRegistry.cpp
 * @brief Implementation of PrototypeRegistry.
 */

#include "PrototypeRegistry.h"

void PrototypeRegistry::registerPrototype(std::string key, std::unique_ptr<Item> proto) 
{
    prototypes[std::move(key)] = std::move(proto);
}

// Return a deep clone so callers can freely modify the copy.
std::unique_ptr<Item> PrototypeRegistry::cloneOf(const std::string& key) const 
{
  auto it = prototypes.find(key);
  if (it == prototypes.end()) return nullptr;
  return it->second->clone();
}

//inspect the registry
bool PrototypeRegistry::has(const std::string& key) const 
{
  return prototypes.find(key) != prototypes.end();
}

std::size_t PrototypeRegistry::size() const 
{ 
    return prototypes.size(); 
}