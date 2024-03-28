#ifndef REPLACE_WITH_YOUR_PROJECT_NAME_GHOSTDEADSTATE_HPP
#define REPLACE_WITH_YOUR_PROJECT_NAME_GHOSTDEADSTATE_HPP

#include <iostream>

#include "GhostState.hpp"

class GhostDeadState : public GhostState {
public:
    GhostDeadState() = default;

    void GetState() override {
        std::cout << "Ghost State: Dead\n";
    }
};

#endif //REPLACE_WITH_YOUR_PROJECT_NAME_GHOSTDEADSTATE_HPP
