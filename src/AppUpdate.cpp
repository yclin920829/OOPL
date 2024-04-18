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


    if (PACMAN && NORMAL) pacman->Start();
    if (PACMAN && DEAD){
        pacman->Dead();
    }
    if (PACMAN && UP) pacman->MoveUp();
    if (PACMAN && DOWN) pacman->MoveDown();
    if (PACMAN && RIGHT) pacman->MoveRight();
    if (PACMAN && LEFT) pacman->MoveLeft();

    int x_random = randomFactory.GenerateRandomNumber(xMap);
    int y_random = randomFactory.GenerateRandomNumber(yMap);


    glm::vec2 randomPosition = map -> map_by_number[y_random - 1][x_random - 1] -> GetPosition();
    if(map ->IsPacmanRoad(randomPosition)){
        fruitSystem ->CheckCreatable(randomPosition);
    }

    fruitSystem->CheckDeletable();

    auto FAKECOLLISION = Util::Input::IsKeyUp(Util::Keycode::NUM_4);
    if(FAKECOLLISION){
        printf("press4");
        pacman ->HandleCollision();
    }

    auto FAKEADDTION = Util::Input::IsKeyUp(Util::Keycode::NUM_5);
    if(FAKEADDTION){
        printf("press5");
        pacman ->HandleScoreUpCollision();
    }

    /*if (Util::Input::IsKeyDown(Util::Keycode::S)) {
        if (!cherry->GetVisibility()) cherry->SetVisible(true);
        else cherry->SetVisible(false);
    }*/

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

