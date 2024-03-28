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
    if (PACMAN && DEAD) pacman->Dead();
    if (PACMAN && UP) pacman->MoveUp();
    if (PACMAN && DOWN) pacman->MoveDown();
    if (PACMAN && RIGHT) pacman->MoveRight();
    if (PACMAN && LEFT) pacman->MoveLeft();

    if (Util::Input::IsKeyDown(Util::Keycode::S)) {
        if (!cherry->GetVisibility()) cherry->SetVisible(true);
        else cherry->SetVisible(false);
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

