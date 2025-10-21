/**
 * @file SalesExpert.h
 * @brief this is the definition of SalesExpert class for advanced sales and pricing inquiries
 * @author Karishma Boodhoo
 * @date 13-10-2025
 */

#ifndef SALESEXPERT_H
#define SALESEXPERT_H

#include "CustomerQueryHandler.h"

/**
 * @class SalesExpert
 * @brief this is a handler for complex sales and pricing questions
 * this class represents senior sales specialists in the Chain of Responsibility pattern for customer queries. Sales experts handle advanced pricing inquiries 
 * and complex sales arrangements that require deeper sales expertise than general customer service staff possess.
 */

class SalesExpert : public CustomerQueryHandler{
    public:
        /**
         * @brief this function processes advanced sales and pricing queries
         * @param query this is the customer query to be handled
         * it provides expert assistance with complex pricing structures special sales scenarios and it escalates plant care questions and managerial issues to appropriate
         * specialists in the customer service chain
         */
        void handleQuery(const CustomerQuery& query);

        /**
         * @brief this function determines if this handler can process the given customer query
         * @param query this is the customer query to evaluate
         * @return it returns true if this handler can answer the query otherwise false
         * the sales experts handle complex pricing questions and special sales arrangements but defer plant care advice, general questions, and
         * managerial issues to other specialists in the customer service chain
         */
        bool canHandle(const CustomerQuery& query) const;
};

#endif