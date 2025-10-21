/**
 * @file CustomerQuery.h
 * @brief this is a definition of the CustomerQuery class for handling customer inquiries
 * @author Karishma Boodhoo
 * @date 13-10-2025
 */

#ifndef CUSTOMERQUERY_H
#define CUSTOMERQUERY_H

#include <string>

class Customer;

/**
 * @class CustomerQuery
 * @brief it represents a customer inquiry in the system
 * 
 * This class encapsulates customer queries with their type, content, and associated customer. It serves as the Request object in the Chain of
 * Responsibility pattern and it flows through different staff handlers until an appropriate individual handles it
 */

class CustomerQuery{
    public:
        /**
         * @brief this is an enumeration of possible query types
         * it defines the categories of customer inquiries that can be processed by the staff through the Chain of Responsibility pattern
         */
        enum Type { GENERAL, CARE_ADVICE, PRICING, COMPLAINT, SPECIAL_REQUEST };
        Type type;
        std::string question;
        Customer* customer;

        /**
         * @brief this function constructs a CustomerQuery with specified parameters
         * @param type this is the category of the query
         * @param question this is the question text from the customer
         * @param customer this is a pointer to the customer making the query
         * it creates a new customer query object that can be processed through the Chain of Responsibility pattern by various staff
         */
        CustomerQuery(Type type, const std::string& question, Customer* customer);
};

#endif