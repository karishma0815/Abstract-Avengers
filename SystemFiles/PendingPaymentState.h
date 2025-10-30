/*Abstract Avengers*/

/**
 * @file PendingPaymentState.h
 * @brief Concrete state for pending payment
 * @author Taskeen Abdoola
 * @date 2025-10-16
 */

#ifndef PENDINGPAYMENTSTATE_H
#define PENDINGPAYMENTSTATE_H

#include "State.h"

class PendingPaymentState : public State 
{
public:
  static PendingPaymentState& instance();

  std::string getStateName() const override;

  void onAuthorize() override;
  void onCancel() override;

private:
  PendingPaymentState() = default;
};

#endif