/*Abstract Avengers*/

/**
 * @file PaymentAuthorizedState.h
 * @brief Concrete state for payment authorized
 * @author Taskeen Abdoola
 * @date 2025-10-16
 */

#ifndef PAYMENTAUTHORIZEDSTATE_H
#define PAYMENTAUTHORIZEDSTATE_H

#include "State.h"

class PaymentAuthorizedState : public State 
{
public:
  static PaymentAuthorizedState& instance();

  std::string getStateName() const override;

  void onCommit() override;
  void onCancel() override;

private:
  PaymentAuthorizedState() = default;
};

#endif