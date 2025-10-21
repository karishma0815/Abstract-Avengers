/**
 * @file CustomerQueryHandler.h
 * @brief this is the definition of CustomerQueryHandler class for Chain of Responsibility pattern
 * @author Karishma Boodhoo
 * @date 13-10-2025
 */

#ifndef CUSTOMERQUERYHANDLER_H
#define CUSTOMERQUERYHANDLER_H

class CustomerQuery;

/**
 * @class CustomerQueryHandler
 * @brief this is an abstract base class for handling customer queries in Chain of Responsibility pattern
 * This class defines the interface for handlers in the customer query processing chain.
 * Each concrete handler decides whether it can process a query or should pass it to the next handler in the chain
 */

class CustomerQueryHandler{
    protected:
        CustomerQueryHandler* nextHandler;
    public:
        /**
         * @brief this is a constructor and it constructs a CustomerQueryHandler
         */
        CustomerQueryHandler();

        /**
         * @brief this is a virtual destructor for cleanup of the derived classes
         */
        virtual ~CustomerQueryHandler();

        /**
         * @brief this function sets the next handler in the chain
         * @param handler this is a pointer to the next handler to receive unhandled queries
         * it establishes the next handler in the responsibility chain. If this handler cannot process a query, it will be passed to the next handler
         */
        void setNext(CustomerQueryHandler* handler);

        /**
         * @brief this function processes a customer query
         * @param query this is the customer query to handle
         * it attempts to process the query. If this handler cannot handle the query, it passes the query to the next handler in the chain if one exists
         */
        virtual void handleQuery(const CustomerQuery& query) = 0;

        /**
         * @brief this function determines if this handler can process the given query
         * @param query this is the customer query to check
         * @return it returns true if this handler can process the query otherwise false
         * Each concrete handler implements this method to decide whether it has the expertise to handle the specific type of customer query
         */
        virtual bool canHandle(const CustomerQuery& query) const = 0;
};

#endif