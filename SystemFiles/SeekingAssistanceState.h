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
#include <string>

class CustomerQuery; //forward declaring

class SeekingAssistanceState : public State 
{
public:
  static SeekingAssistanceState& instance();

  std::string getStateName() const override;


  void onEnter() override; //for customer query

  void onAssistComplete() override;
  void onSelect(const std::string& sku, int qty) override; //will call query first
  void onCancel() override;
  
  // run CoR and decide where to go next (sets state internally)
  void handleCustomerQuery(const CustomerQuery& query);

  // tiny helper: extract (sku,qty) from text like "SKU ABC qty 2"
  static bool parseSkuQty(const std::string& text, std::string& skuOut, int& qtyOut);
};

#endif