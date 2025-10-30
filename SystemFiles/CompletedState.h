/*Abstract Avengers*/

/**
 * @file CompletedState.h
 * @brief Concrete state for completed
 * @author Taskeen Abdoola
 * @date 2025-10-16
 */

#ifndef COMPLETEDSTATE_H
#define COMPLETEDSTATE_H

#include "State.h"

class CompletedState : public State 
{
public:
  static CompletedState& instance();

  std::string getStateName() const override;
  void enterState(Customer& customer, SalesContext& ctx) override;
};

#endif 
