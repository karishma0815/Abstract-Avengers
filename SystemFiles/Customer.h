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

class Customer 
{
public:
  explicit Customer(std::string name = "Guest");
  const std::string& nameFunc() const;
  void setName(std::string n);

private:
  std::string name;
};

#endif 
