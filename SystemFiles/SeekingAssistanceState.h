/*Abstract Avengers*/

/**
 * @file SeekingAssistanceState.h
 * @brief Concrete state for seeking assistance
 * @author Taskeen Abdoola
 * @date 2025-10-16
 */

#ifndef SEEKINGASSISTANCESTATE_H
#define SEEKINGASSISTANCESTATE_H

#include "State.h"

class SeekingAssistanceState : public State 
{
public:
  static SeekingAssistanceState& instance();

  std::string getStateName() const override;

  void onAssistComplete() override;
  void onSelect(const std::string& sku, int qty) override;
  void onCancel() override;
};

#endif