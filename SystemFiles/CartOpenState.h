/*Abstract Avengers*/

/**
 * @file CartOpenState.h
 * @brief Concrete state for open cart
 * @author Taskeen Abdoola
 * @date 2025-10-16
 */

#ifndef CARTOPENSTATE_H
#define CARTOPENSTATE_H

#include "State.h"

class CartOpenState : public State 
{
public:
  static CartOpenState& instance();

  std::string getStateName() const override;
  void enterState(Customer& customer, SalesContext& ctx) override;

  void onCheckout() override;
  void onCancel() override;
  void onAssist() override;

private:
  CartOpenState() = default;
};

#endif