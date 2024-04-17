#include <iostream>

#include "App.hpp"
#include "Util/Input.hpp"

void App::Update() {

    auto UP = Util::Input::IsKeyPressed(Util::Keycode::UP);
    auto DOWN = Util::Input::IsKeyPressed(Util::Keycode::DOWN);
    auto RIGHT = Util::Input::IsKeyPressed(Util::Keycode::RIGHT);
    auto LEFT = Util::Input::IsKeyPressed(Util::Keycode::LEFT);

    auto NORMAL = Util::Input::IsKeyDown(Util::Keycode::NUM_1);
    auto DEAD = Util::Input::IsKeyDown(Util::Keycode::NUM_2);
    auto VULNERABLE = Util::Input::IsKeyDown(Util::Keycode::NUM_3);

    auto BLINKY = Util::Input::IsKeyPressed(Util::Keycode::B);
    auto PINKY = Util::Input::IsKeyPressed(Util::Keycode::P);
    auto INKY = Util::Input::IsKeyPressed(Util::Keycode::I);
    auto CLYDE = Util::Input::IsKeyPressed(Util::Keycode::C);

    auto PACMAN = Util::Input::IsKeyPressed(Util::Keycode::A);

    if (BLINKY && NORMAL) blinky->SetState(normalBlinky);
    if (BLINKY && DEAD) blinky->SetState(deadGhost);
    if (BLINKY && VULNERABLE) blinky->SetState(vulnerableGhost);
    if (BLINKY && UP) blinky->MoveUp();
    if (BLINKY && DOWN) blinky->MoveDown();
    if (BLINKY && RIGHT) blinky->MoveRight();
    if (BLINKY && LEFT) blinky->MoveLeft();

    if (PINKY && NORMAL) pinky->SetState(normalPinky);
    if (PINKY && DEAD) pinky->SetState(deadGhost);
    if (PINKY && VULNERABLE) pinky->SetState(vulnerableGhost);
    if (PINKY && UP) pinky->MoveUp();
    if (PINKY && DOWN) pinky->MoveDown();
    if (PINKY && RIGHT) pinky->MoveRight();
    if (PINKY && LEFT) pinky->MoveLeft();

    if (INKY && NORMAL) inky->SetState(normalInky);
    if (INKY && DEAD) inky->SetState(deadGhost);
    if (INKY && VULNERABLE) inky->SetState(vulnerableGhost);
    if (INKY && UP) inky->MoveUp();
    if (INKY && DOWN) inky->MoveDown();
    if (INKY && RIGHT) inky->MoveRight();
    if (INKY && LEFT) inky->MoveLeft();

    if (CLYDE && NORMAL) clyde->SetState(normalClyde);
    if (CLYDE && DEAD) clyde->SetState(deadGhost);
    if (CLYDE && VULNERABLE) clyde->SetState(vulnerableGhost);
    if (CLYDE && UP) clyde->MoveUp();
    if (CLYDE && DOWN) clyde->MoveDown();
    if (CLYDE && RIGHT) clyde->MoveRight();
    if (CLYDE && LEFT) clyde->MoveLeft();

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

