#ifndef REPLACE_WITH_YOUR_PROJECT_NAME_GHOSTNORMALSTATE_HPP
#define REPLACE_WITH_YOUR_PROJECT_NAME_GHOSTNORMALSTATE_HPP

#include <iostream>

#include "GhostState.hpp"

class GhostNormalState : public GhostState{
public:
    GhostNormalState() = default;

    void GetState() override {
        std::cout << "Ghost State: Normal\n";
    }
};

#endif //REPLACE_WITH_YOUR_PROJECT_NAME_GHOSTNORMALSTATE_HPP
