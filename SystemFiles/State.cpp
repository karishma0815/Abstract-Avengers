/*Abstract Avengers*/

/**
 * @file State.cpp
 * @brief Implementation of State.
 */

#include "State.h"
#include "SalesContext.h"

void State::enterState(Customer& customer, SalesContext& context) 
{
  ctx = &context;
  ctxFunc().notify("Enter: " + getStateName());
}

void State::onSelect(const std::string&, int)   
{ 
    ctxFunc().notify(getStateName() + " ignores: select"); 
}

void State::onAssist()                          
{ 
    ctxFunc().notify(getStateName() + " ignores: assist"); 
}

void State::onAssistComplete()                  
{ 
    ctxFunc().notify(getStateName() + " ignores: assist_complete"); 
}

void State::onReplenished()                     
{ 
    ctxFunc().notify(getStateName() + " ignores: replenished"); 
}

void State::onCheckout()                        
{ 
    ctxFunc().notify(getStateName() + " ignores: checkout"); 
}

void State::onAuthorize()                       
{ 
    ctxFunc().notify(getStateName() + " ignores: authorize"); 
}

void State::onCommit()                          
{ 
    ctxFunc().notify(getStateName() + " ignores: commit"); 
}

void State::onRetry()                           
{ 
    ctxFunc().notify(getStateName() + " ignores: retry"); 
}

void State::onCancel()                          
{ 
    ctxFunc().notify(getStateName() + " ignores: cancel"); 
}

