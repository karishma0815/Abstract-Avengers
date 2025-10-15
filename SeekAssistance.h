/**
 * @file SeekAssistance.h
 * @brief Concrete Command to seek assistance from staff
 */
#ifndef SEEKASSISTANCE_H
#define SEEKASSISTANCE_H

#include "Command.h"

class SeekAssistance : public Command {
public:
    /**
     * @brief Constructs a SeekAssistance command
     */
    SeekAssistance();
    /**
     * @brief Destructor
     */
    ~SeekAssistance();
    /**
     * @brief Executes the seek assistance command
     */
    void execute(State& state) override;
};
#endif