/*Abstract Avengers*/

/**
 * @file SalesOrder.h
 * @brief Concrete SalesContext that owns the current State, inventory, and payment flow.
 * @author Taskeen Abdoola
 * @date 2025-10-17
 */

#ifndef SALESORDER_H
#define SALESORDER_H

#include "SalesContext.h"
#include "Customer.h"
#include "State.h"

#include <unordered_map>
#include <string>
#include <iostream>   

/**
 * @class sales::SalesOrder
 * @brief Concrete context for the sales state machine.
 *
 * Responsibilities:
 *  - Tracks the current State and calls enterState() on transitions.
 *  - Provides stock checks/reservations.
 *  - Simulates authorization/capture (bool flag).
 *  - Exposes convenience methods (select/checkout/authorize/commit/…) to emit events.
 */
class SalesOrder : public SalesContext 
{
public:
  /**
   * @brief Construct a new SalesOrder.
   * @param start   Initial state (e.g., BrowsingState::instance()).
   * @param customer The active customer.
   */
  
  SalesOrder(State& start, Customer& customer);

  void setState(State& next) override;
  void notify(const std::string& msg) override;

  bool hasStock(const std::string& sku, int qty) const override;
  bool reserveStock(const std::string& sku, int qty) override;
  void releaseStock(const std::string& sku, int qty) override;

  void clearOrder() override;

  bool authorizePayment() override;
  bool capturePayment() override;

  void putStock(const std::string& sku, int qty);   
  int  stockOf(const std::string& sku) const;       

  //accessors
  State& current() const;
  Customer& customerFunc() const;

  void eventSelect(const std::string& sku, int qty);
  void eventAssist();
  void eventAssistComplete();
  void eventReplenished();
  void eventCheckout();
  void eventAuthorize();
  void eventCommit();
  void eventRetry();
  void eventCancel();

private:
  State* state = nullptr;           
  Customer* customer = nullptr;          

  std::unordered_map<std::string, int> stock;

  // Payment simulation
  bool authorized{false};
};

#endif 