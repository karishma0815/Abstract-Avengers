/*Abstract Avengers*/

/**
 * @file SalesContext.h
 * @brief Context interface for the sales state.
 * @author Taskeen Abdoola
 * @date 2025-10-16
 */

#ifndef SALESCONTEXT_H
#define SALESCONTEXT_H

#include <string>

class State;

class SalesContext 
{
    public:
        virtual ~SalesContext() {}

        virtual void setState(State& next) = 0;

        virtual void notify(const std::string& msg) = 0;

        //Inventory
        virtual bool hasStock(const std::string& sku, int qty) const = 0;
        virtual bool reserveStock(const std::string& sku, int qty) = 0;
        virtual void releaseStock(const std::string& sku, int qty) = 0;

        //Order housekeeping
        virtual void clearOrder() = 0;

        //Payments
        virtual bool authorizePayment() = 0;
        virtual bool capturePayment() = 0;
};

#endif