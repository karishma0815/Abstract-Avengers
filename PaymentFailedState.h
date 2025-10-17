/*Abstract Avengers*/

/**
 * @file PaymentFailedState.h
 * @brief Concrete state for payment failed
 * @author Taskeen Abdoola
 * @date 2025-10-16
 */

#ifndef PAYMENTFAILEDSTATE_H
#define PAYMENTFAILEDSTATE_H

#include "State.h"

class PaymentFailedState : public State {
public:
  static PaymentFailedState& instance();

  std::string getStateName() const override;

  void onRetry() override;
  void onCancel() override;
};

#endif 
