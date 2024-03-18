#include "App.hpp"
#include "Util/Input.hpp"

void App::Update() {

    auto UP = Util::Keycode::UP;
    auto DOWN = Util::Keycode::DOWN;
    auto RIGHT = Util::Keycode::RIGHT;
    auto LEFT = Util::Keycode::LEFT;


    if ((Util::Input::IsKeyPressed(UP) && Util::Input::IsKeyPressed(Util::Keycode::B)) || Util::Input::IfExit()) blinky->MoveUp();
    if ((Util::Input::IsKeyPressed(DOWN) && Util::Input::IsKeyPressed(Util::Keycode::B)) || Util::Input::IfExit()) blinky->MoveDown();
    if ((Util::Input::IsKeyPressed(RIGHT) && Util::Input::IsKeyPressed(Util::Keycode::B)) || Util::Input::IfExit()) blinky->MoveRight();
    if ((Util::Input::IsKeyPressed(LEFT) && Util::Input::IsKeyPressed(Util::Keycode::B)) || Util::Input::IfExit()) blinky->MoveLeft();

    if ((Util::Input::IsKeyPressed(UP) && Util::Input::IsKeyPressed(Util::Keycode::P)) || Util::Input::IfExit()) pinky->MoveUp();
    if ((Util::Input::IsKeyPressed(DOWN) && Util::Input::IsKeyPressed(Util::Keycode::P)) || Util::Input::IfExit()) pinky->MoveDown();
    if ((Util::Input::IsKeyPressed(RIGHT) && Util::Input::IsKeyPressed(Util::Keycode::P)) || Util::Input::IfExit()) pinky->MoveRight();
    if ((Util::Input::IsKeyPressed(LEFT) && Util::Input::IsKeyPressed(Util::Keycode::P)) || Util::Input::IfExit()) pinky->MoveLeft();

    if ((Util::Input::IsKeyPressed(UP) && Util::Input::IsKeyPressed(Util::Keycode::I)) || Util::Input::IfExit()) inky->MoveUp();
    if ((Util::Input::IsKeyPressed(DOWN) && Util::Input::IsKeyPressed(Util::Keycode::I)) || Util::Input::IfExit()) inky->MoveDown();
    if ((Util::Input::IsKeyPressed(RIGHT) && Util::Input::IsKeyPressed(Util::Keycode::I)) || Util::Input::IfExit()) inky->MoveRight();
    if ((Util::Input::IsKeyPressed(LEFT) && Util::Input::IsKeyPressed(Util::Keycode::I)) || Util::Input::IfExit()) inky->MoveLeft();

    if ((Util::Input::IsKeyPressed(UP) && Util::Input::IsKeyPressed(Util::Keycode::C)) || Util::Input::IfExit()) clyde->MoveUp();
    if ((Util::Input::IsKeyPressed(DOWN) && Util::Input::IsKeyPressed(Util::Keycode::C)) || Util::Input::IfExit()) clyde->MoveDown();
    if ((Util::Input::IsKeyPressed(RIGHT) && Util::Input::IsKeyPressed(Util::Keycode::C)) || Util::Input::IfExit()) clyde->MoveRight();
    if ((Util::Input::IsKeyPressed(LEFT) && Util::Input::IsKeyPressed(Util::Keycode::C)) || Util::Input::IfExit()) clyde->MoveLeft();

    if ((Util::Input::IsKeyPressed(UP) && Util::Input::IsKeyPressed(Util::Keycode::A)) || Util::Input::IfExit()) pacman->MoveUp();
    if ((Util::Input::IsKeyPressed(DOWN) && Util::Input::IsKeyPressed(Util::Keycode::A)) || Util::Input::IfExit()) pacman->MoveDown();
    if ((Util::Input::IsKeyPressed(RIGHT) && Util::Input::IsKeyPressed(Util::Keycode::A)) || Util::Input::IfExit()) pacman->MoveRight();
    if ((Util::Input::IsKeyPressed(LEFT) && Util::Input::IsKeyPressed(Util::Keycode::A)) || Util::Input::IfExit()) pacman->MoveLeft();


    if ((Util::Input::IsKeyPressed(UP) && Util::Input::IsKeyPressed(Util::Keycode::D)) || Util::Input::IfExit()) ghost_dead->MoveUp();
    if ((Util::Input::IsKeyPressed(DOWN) && Util::Input::IsKeyPressed(Util::Keycode::D)) || Util::Input::IfExit()) ghost_dead->MoveDown();
    if ((Util::Input::IsKeyPressed(RIGHT) && Util::Input::IsKeyPressed(Util::Keycode::D)) || Util::Input::IfExit()) ghost_dead->MoveRight();
    if ((Util::Input::IsKeyPressed(LEFT) && Util::Input::IsKeyPressed(Util::Keycode::D)) || Util::Input::IfExit()) ghost_dead->MoveLeft();

    if (Util::Input::IsKeyPressed(Util::Keycode::S) || Util::Input::IfExit()) cherry->SetVisible(false);
    if (Util::Input::IsKeyUp(Util::Keycode::S) || Util::Input::IfExit()) cherry->SetVisible(true);

    if ((Util::Input::IsKeyPressed(UP) && Util::Input::IsKeyPressed(Util::Keycode::T)) || Util::Input::IfExit()) vulnerable_ghost->MoveUp();
    if ((Util::Input::IsKeyPressed(DOWN) && Util::Input::IsKeyPressed(Util::Keycode::T)) || Util::Input::IfExit()) vulnerable_ghost->MoveDown();
    if ((Util::Input::IsKeyPressed(RIGHT) && Util::Input::IsKeyPressed(Util::Keycode::T)) || Util::Input::IfExit()) vulnerable_ghost->MoveRight();
    if ((Util::Input::IsKeyPressed(LEFT) && Util::Input::IsKeyPressed(Util::Keycode::T )) || Util::Input::IfExit()) vulnerable_ghost->MoveLeft();

    /*
     * Do not touch the code below as they serve the purpose for
     * closing the window.
     */
    if (Util::Input::IsKeyUp(Util::Keycode::ESCAPE) ||
        Util::Input::IfExit()) {
        m_CurrentState = State::END;
    }

    m_Root.Update();
}