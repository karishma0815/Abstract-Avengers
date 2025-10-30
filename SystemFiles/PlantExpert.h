/**
 * @file PlantExpert.h
 * @brief this is the definition of PlantExpert class for specialized plant care advice
 * @author Karishma Boodhoo
 * @date 13-10-2025
 */

#ifndef PLANTEXPERT_H
#define PLANTEXPERT_H

#include "CustomerQueryHandler.h"

/**
 * @class PlantExpert
 * @brief this is a specialized handler for plant care and cultivation questions
 * This class represents specialists in the Chain of Responsibility pattern for customer queries. Plant experts handle complex plant care
 * questions, disease diagnosis, and gardening advice that require deep botanical knowledge beyond the
 * capabilities of general customer service staff
 */

class PlantExpert : public CustomerQueryHandler{
    public:
        /**
         * @brief this function processes specialized plant care queries
         * @param query this is the customer query to be handled
         * it provides expert advice on plant care, disease treatment gardening techniques. If the query involves managerial authority, 
         * it is passed to the next handler in the chain.
         */
        void handleQuery(const CustomerQuery& query);

        /**
         * @brief this function determines if this handler can process the given customer query
         * @param query this is the customer query to evaluate
         * @return it returns true if this handler can answer the query otherwise false
         * Plant experts handle all plant care advice questions but defer complaints, pricing inquiries,
         * and special requests to other specialists in the customer service chain.
         */
        bool canHandle(const CustomerQuery& query) const;
};

#endif