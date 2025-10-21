/*Abstract Avengers*/

/**
 * @file State.h
 * @brief Base state with context-free events.
 * @author Taskeen Abdoola
 * @date 2025-10-16
 */

#ifndef STATE_H
#define STATE_H

#include <string>

class Customer;
class SalesContext;

class State 
{
public:
  virtual ~State() {}

  /** @brief Name for logging/UI. */
  virtual std::string getStateName() const = 0;

  /** @brief Called when the context enters this state. */
  virtual void enterState(Customer& customer, SalesContext& ctx);

  /** @brief Optional periodic update. */
  virtual void update(Customer& customer) {}

  virtual void onSelect(const std::string& sku, int qty);
  virtual void onAssist();
  virtual void onAssistComplete();
  virtual void onReplenished();
  virtual void onCheckout();
  virtual void onAuthorize();
  virtual void onCommit();
  virtual void onRetry();
  virtual void onCancel();

protected:
  SalesContext& ctxFunc() const 
  { 
    return *ctx; 
  }  

private:
  SalesContext* ctx = nullptr;               
};

#endif 
