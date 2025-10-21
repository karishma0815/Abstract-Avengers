/*Abstract Avengers*/

/**
 * @file BrowsingState.h
 * @brief Concrete state for browsing
 * @author Taskeen Abdoola
 * @date 2025-10-16
 */

#ifndef BROWSINGSTATE_H
#define BROWSINGSTATE_H

#include "State.h"

class BrowsingState : public State 
{
    public:
    static BrowsingState& instance();
    std::string getStateName() const override;

    void onSelect(const std::string& sku, int qty) override;
    void onAssist() override;
    void onCancel() override;
};

#endif