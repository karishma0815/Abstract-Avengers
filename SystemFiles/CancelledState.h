/*Abstract Avengers*/

/**
 * @file CancelledState.h
 * @brief Concrete state for cancelled
 * @author Taskeen Abdoola
 * @date 2025-10-16
 */

#ifndef CANCELLEDSTATE_H
#define CANCELLEDSTATE_H

#include "State.h"

class CancelledState : public State 
{
public:
  static CancelledState& instance();

  std::string getStateName() const override;
  void enterState(Customer& customer, SalesContext& ctx) override;
};

#endif 
