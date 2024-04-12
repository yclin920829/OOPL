#ifndef REPLACE_WITH_YOUR_PROJECT_NAME_GHOSTVULNERABLESTATE_HPP
#define REPLACE_WITH_YOUR_PROJECT_NAME_GHOSTVULNERABLESTATE_HPP

#include <iostream>

#include "GhostState.hpp"

class GhostVulnerableState : public GhostState {
public:
    GhostVulnerableState() = default;

    std::string GetState() override {
        return "Vulnerable";
    }
};

#endif //REPLACE_WITH_YOUR_PROJECT_NAME_GHOSTVULNERABLESTATE_HPP
