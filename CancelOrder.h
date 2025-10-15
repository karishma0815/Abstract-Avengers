/**
 * @file CancelOrder.h
 * @brief Concrete Command to cancel an order
 */
#ifndef CANCELORDER_H
#define CANCELORDER_H

#include "Command.h"

class CancelOrder : public Command {
public:
    /**
     * @brief Constructs a CancelOrder command
     */
    CancelOrder();
    /**
     * @brief Destructor
     */
    ~CancelOrder();
    /**
     * @brief Executes the cancel order command
     */
    void execute(State& state) override;
};
#endif