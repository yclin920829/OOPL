#include <iostream>

#include "App.hpp"
#include "Util/Input.hpp"

void App::Update() {

    bool UP = (Util::Input::IsKeyPressed(Util::Keycode::UP) || Util::Input::IsKeyDown(Util::Keycode::UP));
    bool DOWN = (Util::Input::IsKeyPressed(Util::Keycode::DOWN) || Util::Input::IsKeyDown(Util::Keycode::DOWN));
    bool RIGHT = (Util::Input::IsKeyPressed(Util::Keycode::RIGHT) || Util::Input::IsKeyDown(Util::Keycode::RIGHT));
    bool LEFT = (Util::Input::IsKeyPressed(Util::Keycode::LEFT) || Util::Input::IsKeyDown(Util::Keycode::LEFT));

    if (UP && !DOWN && !RIGHT && !LEFT) {
        glm::vec2 oldPosition = pacman->GetPosition();
        glm::vec2 newPosition = {oldPosition.x, oldPosition.y + 16.0f};
        if (map->IsPacmanRoad(newPosition)) {
            pacman->MoveUp();
        }
    }

    if (!UP && DOWN && !RIGHT && !LEFT) {
        glm::vec2 oldPosition = pacman->GetPosition();
        glm::vec2 newPosition = {oldPosition.x, oldPosition.y - 16.0f};
        if (map->IsPacmanRoad(newPosition)) {
            pacman->MoveDown();
        }
    }

    if (!UP && !DOWN && RIGHT && !LEFT) {
        glm::vec2 oldPosition = pacman->GetPosition();
        glm::vec2 newPosition = {oldPosition.x + 16.0f, oldPosition.y};
        if (map->IsPacmanRoad(newPosition)) {
            pacman->MoveRight();
        }
    }

    if (!UP && !DOWN && !RIGHT && LEFT) {
        glm::vec2 oldPosition = pacman->GetPosition();
        glm::vec2 newPosition = {oldPosition.x - 16.0f, oldPosition.y};
        if (map->IsPacmanRoad(newPosition)) {
            pacman->MoveLeft();
        }
    }

    /*
     * Do not touch the code below as they serve the purpose for
     * closing the window.
     */
    if (Util::Input::IsKeyUp(Util::Keycode::ESCAPE) ||
        Util::Input::IfExit()) {
        m_CurrentState = State::END;
    }

    root.Update();
}

