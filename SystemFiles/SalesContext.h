/*Abstract Avengers*/

/**
 * @file SalesContext.h
 * @brief SalesContext that owns the current State, inventory, and payment flow.
 * @author Taskeen Abdoola
 * @date 2025-10-17
 */

#ifndef SALESCONTEXT_H
#define SALESCONTEXT_H

#include "Customer.h"
#include "State.h"
#include "BrowsingState.h"

#include <unordered_map>
#include <string>
#include <iostream>   

/**
 * @class sales::SalesContext
 * @brief Context for the sales state machine.
 *
 * Responsibilities:
 *  - Tracks the current State and calls enterState() on transitions.
 *  - Provides stock checks/reservations.
 *  - Simulates authorization/capture (bool flag).
 *  - Exposes convenience methods (select/checkout/authorize/commit/…) to emit events.
 */
class SalesContext 
{
public:
  /**
   * @brief Construct a new SalesContext.
   * @param start   Initial state (e.g., BrowsingState::instance()).
   * @param customer The active customer.
   */
  
  SalesContext(State& start, Customer& customer);

  void setState(State& next);
  void notify(const std::string& msg);

  bool hasStock(const std::string& sku, int qty) const;
  bool reserveStock(const std::string& sku, int qty);
  void releaseStock(const std::string& sku, int qty);

  void clearOrder();

  bool authorizePayment();
  bool capturePayment();

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

  bool isTerminal() const;
  void resetToBrowsing();

private:
  State* state = nullptr;           
  Customer* customer = nullptr;          

  std::unordered_map<std::string, int> stock;

  // Payment simulation
  bool authorized{false};

  //toggle for demoing branches of sucess/failure

  #ifdef SUPPORT_TEST_TOGGLES
private:
  bool testAuthNext{true};       //next authorize result
  bool testCaptureNext{true};    //next capture result
  bool testAuthArmed{false};     //if true, consume testAuthNext once
  bool testCaptureArmed{false};  //if true, consume testCaptureNext once
public:
  // One-shot: the *next* authorize/capture will return this result, then we auto reset.
  void forceNextAuth(bool ok)    
  { 
    testAuthNext = ok;    
    testAuthArmed = true; 
  }

  void forceNextCapture(bool ok) 
  { 
    testCaptureNext = ok; 
    testCaptureArmed = true;
  }

#endif

};

#endif 