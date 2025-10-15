#ifndef STATE_H
#define STATE_H

class State {
public:
    virtual ~State() {}
    virtual void handle() = 0;
};
#endif