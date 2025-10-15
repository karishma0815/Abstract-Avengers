/**
 * @file CapturePayment.h
 * @brief Concrete Command to capture a payment
 */
#ifndef CAPTUREPAYMENT_H
#define CAPTUREPAYMENT_H
#include "Command.h"

class CapturePayment : public Command {
public: 
    /**
     * @brief Constructs a CapturePayment command
     */
    CapturePayment();
    /**
     * @brief Destructor
     */
    ~CapturePayment();
    /**
     * @brief Executes the capture payment command
     */
    void execute(State& state) override;
};
#endif