/**
 * @file AuthorisePayment.h
 * @brief Concrete Command to authorise a payment
 */
#ifndef AUTHORISEPAYMENT_H
#define AUTHORISEPAYMENT_H
#include "Command.h"

class AuthorisePayment : public Command {
public: 
    /**
     * @brief Constructs an AuthorisePayment command
     */
    AuthorisePayment();
    /**
     * @brief Destructor
     */
    ~AuthorisePayment();
    /**
     * @brief Executes the authorise payment command
     */
    void execute(State& state) override;
};
#endif