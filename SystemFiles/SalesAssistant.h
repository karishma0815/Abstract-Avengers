/**
 * @file SalesAssistant.h
 * @brief this is the definition of SalesAssistant class for customer service and sales
 * @author Karishma Boodhoo
 * @date 13-10-2025
 */

#ifndef SALESASSISTANT_H
#define SALESASSISTANT_H

#include "Staff.h"
#include "CustomerQueryHandler.h"

/**
 * @class SalesAssistant
 * @brief this is the customer facing staff member handling sales and basic customer inquiries
 * this class represents sales personnel who participate in both the Factory Method pattern as Staff members and the Chain of Responsibility pattern as frontline
 * customer query handlers. Sales assistants handle general customer questions, pricing inquiries, and plant sales while escalating specialized plant care questions to experts
 */

class SalesAssistant : public Staff, public CustomerQueryHandler{
    private:
        double commissionRate;
    public:
        /**
         * @brief this is a constructor that constructs a SalesAssistant with commission structure
         * @param name this is the sales assistants name
         * @param id this is a unique identifier for the staff member
         * @param med this is a pointer to the inventory mediator for stock coordination
         * @param commission this is the the commission rate for sales 0.05 for 5%
         */
        SalesAssistant(const std::string& name, int id, InventoryMediator* med, double commission);

        /**
         * @brief this function gets the role description of this staff member
         * @return std::string The role name "Sales Assistant"
         */
        std::string getRole() const;

        /**
         * @brief this function performs plant related duties specific to sales staff
         * the sales assistants handle plant display, arrangement, and basic maintenance for sales floor presentation rather than deep plant care
         */
        void careForPlants();

        /**
         * @brief this function handles customer queries within sales expertise
         * @param query this is the customer query to process
         * it processes general customer questions and pricing inquiries and it escalates plant care advice questions to experts and complex issues to managers in the customer query chain
         */
        void handleQuery(const CustomerQuery& query);

        /**
         * @brief this function determines if this handler can process the given customer query
         * @param query this is the customer query to evaluate
         * @return it returns true if this handler can answer the query otherwise false
         * the sales assistants handle general questions and pricing inquiries but escalate plant care advice, complaints tp specialized handlers in the customer service chain
         */
        bool canHandle(const CustomerQuery& query) const;
};

#endif