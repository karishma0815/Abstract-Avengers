/*Abstract Avengers*/

/**
 * @file AwaitingStockState.h
 * @brief Concrete state for awaiting stock
 * @author Taskeen Abdoola
 * @date 2025-10-16
 */

#ifndef AWAITINGSTOCKSTATE_H
#define AWAITINGSTOCKSTATE_H

#include "State.h"

class AwaitingStockState : public State 
{
public:
  static AwaitingStockState& instance();

  std::string getStateName() const override;

  void onReplenished() override;
  void onCancel() override;
};

#endif