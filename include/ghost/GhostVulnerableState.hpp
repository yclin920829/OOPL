#ifndef REPLACE_WITH_YOUR_PROJECT_NAME_GHOSTVULNERABLESTATE_HPP
#define REPLACE_WITH_YOUR_PROJECT_NAME_GHOSTVULNERABLESTATE_HPP

#include <iostream>

#include "GhostState.hpp"

class GhostVulnerableState : public GhostState {
public:
    GhostVulnerableState() = default;

    void GetState() override {
        std::cout << "Ghost State: Vulnerable\n";
    }
};

#endif //REPLACE_WITH_YOUR_PROJECT_NAME_GHOSTVULNERABLESTATE_HPP
