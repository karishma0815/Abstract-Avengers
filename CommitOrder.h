/**
 * @file CommitOrder.h
 * @brief Concrete Command to commit an order
 */
#ifndef COMMITORDER_H
#define COMMITORDER_H

#include "Command.h"

class CommitOrder : public Command {
public:
    /**
     * @brief Constructs a CommitOrder command
     */
    CommitOrder();
    /**
     * @brief Destructor
     */
    ~CommitOrder();
    /**
     * @brief Executes the commit order command
     */
    void execute(State& state) override;
};
#endif