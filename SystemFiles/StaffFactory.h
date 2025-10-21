/**
 * @file StaffFactory.h
 * @brief this is the definition of StaffFactory abstract base class for Factory Method pattern
 * @author Karishma Boodhoo
 * @date 13-10-2025
 */

#ifndef STAFFFACTORY_H
#define STAFFFACTORY_H

#include <string>

class Staff;

/**
 * @class StaffFactory
 * @brief this is an abstract factory interface for creating Staff objects
 * this class defines the Factory Method pattern interface for creating different types of staff members in the nursery system. Concrete factory
 * classes implement this interface to create specific staff roles 
 */

class StaffFactory {
    public:
        /**
         * @brief this is a virtual destructor for cleanup of derived classes
         */
        virtual ~StaffFactory();

        /**
         * @brief this function Ccreates a new Staff instance
         * @return this is a Staff* pointer to the newly created Staff object
         * this is a pure virtual method that concrete factories must implement to create specific types of staff members with appropriate default parameters
         */
        virtual Staff* createStaff() = 0;

        /**
         * @brief this function gets the name of the role this factory creates
         * @return std::string The specific role name
         * this is a pure virtual method that concrete factories must implement to return the name of the staff role they produce
         */
        virtual std::string getRoleName() const = 0;
};

#endif