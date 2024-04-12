#ifndef REPLACE_WITH_YOUR_PROJECT_NAME_GHOSTNORMALSTATE_HPP
#define REPLACE_WITH_YOUR_PROJECT_NAME_GHOSTNORMALSTATE_HPP

#include <iostream>

#include "GhostState.hpp"

class GhostNormalState : public GhostState {
public:
    GhostNormalState() = default;

    std::string GetState() override {
        return "Normal";
    }
};

#endif //REPLACE_WITH_YOUR_PROJECT_NAME_GHOSTNORMALSTATE_HPP
