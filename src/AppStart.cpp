#include "App.hpp"

#include "Util/Input.hpp"


void App::Start() {

    levelManager = std::make_shared<LevelManager>();
    root.AddChild(levelManager);
    levelManager -> ConstructLevel(nowLevel, playerID);

    m_CurrentState = State::UPDATE;
}
