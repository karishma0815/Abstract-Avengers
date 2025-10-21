/**
 * @file JuniorStaff.h
 * @brief this is the definition of JuniorStaff class for basic customer query handling
 * @author Karishma Boodhoo
 * @date 13-10-2025
 */

#ifndef JUNIORSTAFF_H
#define JUNIORSTAFF_H

#include "CustomerQueryHandler.h"

/**
 * @class JuniorStaff
 * @brief this is the entry level customer service handler for basic customer inquiries
 * This class represents junior customer service staff in the Chain of Responsibility pattern for customer queries. Junior staff handle general questions and basic
 * pricing inquiries, serving as the first point of contact for customers and escalating more specialized questions to experts in the chain
 */

class JuniorStaff : public CustomerQueryHandler{
    public:
        /**
         * @brief this function processes customer queries within the handler's expertise
         * @param query this is the customer query to be handled
         * it addresses general customer inquiries and basic questions. If the query requires specialized knowledge it is passed to the next handler in the chain.
         */
        void handleQuery(const CustomerQuery& query);

        /**
         * @brief this function determines if this handler can process the given customer query
         * @param query this is the customer query to evaluate
         * @return it returns true if this handler can answer the query otherwise false
         * Junior staff can handle general nursery information and basic pricing questions. Specialized plant care advice, complaints, and complex
         * requests are escalated to more experienced staff members.
         */
        bool canHandle(const CustomerQuery& query) const;
};

#endif