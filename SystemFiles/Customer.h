/*Abstract Avengers*/

/**
 * @file Customer.h
 * @brief Minimal placeholder Customer type for the state machine.
 * @author Taskeen Abdoola
 * @date 2025-10-17
 */

#ifndef CUSTOMER_H
#define CUSTOMER_H

#include <string>
#include "Command.h"
#include "PlantInventory.h"

class Customer 
{
public:
  explicit Customer(std::string name = "Guest");
  ~Customer();
  const std::string& nameFunc() const;
  void setName(std::string n);
  PlantInventory* getCart();
  PlantInventory* getInven();

private:
  std::string name;
  //PlantInventory* cart;
  PlantInventory* inventory;
};

#endif 
