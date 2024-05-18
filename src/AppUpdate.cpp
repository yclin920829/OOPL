#include <iostream>
#include<chrono>
#include<thread>

#include "App.hpp"
#include "Util/Input.hpp"
#include "Util/Time.hpp"

void App::Update() {
    if (Util::Input::IsKeyDown(Util::Keycode::UP)) {
        pacman->setNextDirection(Pacman::Direction::up);
    } else if (Util::Input::IsKeyDown(Util::Keycode::DOWN)) {
        pacman->setNextDirection(Pacman::Direction::down);
    } else if (Util::Input::IsKeyDown(Util::Keycode::RIGHT)) {
        pacman->setNextDirection(Pacman::Direction::right);
    } else if (Util::Input::IsKeyDown(Util::Keycode::LEFT)) {
        pacman->setNextDirection(Pacman::Direction::left);
    }

    glm::vec2 oldPosition = pacman->GetPosition();
    switch (pacman->getNextDirection()) {
        case Pacman::Direction::up:
            if (map->IsPacmanRoad({oldPosition.x, oldPosition.y + 16.0f})) {
                pacman->setCurrentDirection(pacman->getNextDirection());
            }
            break;
        case Pacman::Direction::down:
            if (map->IsPacmanRoad({oldPosition.x, oldPosition.y - 16.0f})) {
                pacman->setCurrentDirection(pacman->getNextDirection());
            }
            break;
        case Pacman::Direction::right:
            if (map->IsPacmanRoad({oldPosition.x + 16.0f, oldPosition.y})) {
                pacman->setCurrentDirection(pacman->getNextDirection());
            }
            break;
        case Pacman::Direction::left:
            if (map->IsPacmanRoad({oldPosition.x - 16.0f, oldPosition.y})) {
                pacman->setCurrentDirection(pacman->getNextDirection());
            }
            break;
        case Pacman::Direction::none:
            break;
    }

    switch (pacman->getCurrentDirection()) {
        case Pacman::Direction::up:
            if (map->IsPacmanRoad({oldPosition.x, oldPosition.y + 16.0f})) {
                // std::this_thread::sleep_for(std::chrono::milliseconds((125 / 4)));
                pacman->MoveUp();
            }
            break;
        case Pacman::Direction::down:
            if (map->IsPacmanRoad({oldPosition.x, oldPosition.y - 16.0f})) {
                // std::this_thread::sleep_for(std::chrono::milliseconds((125 / 4)));
                pacman->MoveDown();
            }
            break;
        case Pacman::Direction::right:
            if (map->IsPacmanRoad({oldPosition.x + 16.0f, oldPosition.y})) {
                // std::this_thread::sleep_for(std::chrono::milliseconds((125 / 4)));
                pacman->MoveRight();
            }
            break;
        case Pacman::Direction::left:
            if (map->IsPacmanRoad({oldPosition.x - 16.0f, oldPosition.y})) {
                // std::this_thread::sleep_for(std::chrono::milliseconds((125 / 4)));
                pacman->MoveLeft();
            }
            break;
        case Pacman::Direction::none:
            break;
    }

    for (const std::shared_ptr<Block> &bean: map->GetSmallBeans()) {
        if (pacman->eatBean(bean) && bean->GetVisibility()) {
            bean->SetVisible(false);
            pacman ->HandleScoreUpCollision();
        }
    }

    for (const std::shared_ptr<Block> &bean: map->GetLargeBeans()) {
        if (pacman->eatBean(bean) && bean->GetVisibility()) {
            bean->SetVisible(false);
            pinky->Vulnerable();
            blinky->Vulnerable();
            inky->Vulnerable();
            clyde->Vulnerable();
            pacman ->HandleScoreUpCollision(75);
            time = 0;
        }

    }

    int counter = 0;
    for (const std::shared_ptr<Block> &bean: map->GetSmallBeans()) {
        if(!bean->GetVisibility()){
            counter ++;
        }
    }

    if((counter % (map->GetSmallBeans().size() / 3)) == 0  && counter){
        fruitSystem->getCherry()->SetVisible(true);
    }

    if(pacman->IsCollidesFruit(fruitSystem->getCherry()) && fruitSystem->getCherry()->GetVisibility()){
        fruitSystem->getCherry()->SetVisible(false);
        pacman ->HandleScoreUpCollision(100);
    }

    if (pacman->IsDead() && pacman->IfAnimationEnds()){
        pacman->ReStart();
        pacman->setNextDirection(Pacman::Direction::left);
    }

    if (!pacman->IsDead() && pacman->IfCollidesGhost(blinky)) {
        if (blinky->GetState() == "Normal") {
            pacman->Dead();
        } else if (blinky->GetState() == "Vulnerable") {
            blinky->Dead();
        }
    }

    if (!pacman->IsDead() && pacman->IfCollidesGhost(pinky)) {
        if (pinky->GetState() == "Normal") {
            pacman->Dead();
        } else if (pinky->GetState() == "Vulnerable") {
            pinky->Dead();
        }
    }

    if (!pacman->IsDead() && pacman->IfCollidesGhost(inky)) {
        if (inky->GetState() == "Normal") {
            pacman->Dead();
        } else if (inky->GetState() == "Vulnerable") {
            inky->Dead();
        }
    }

    if (!pacman->IsDead() && pacman->IfCollidesGhost(clyde)) {
        if (clyde->GetState() == "Normal") {
            pacman->Dead();
        } else if (clyde->GetState() == "Vulnerable") {
            clyde->Dead();
        }
    }

    if(blinky->IsArrivePosition()){
        if(blinky->GetState() == "Dead")blinky->ReStart();
        blinky->SetTargetPosition(map->changeToPositionInVector(
//            pacman->GetPosition()
            map->GetGhostRoad()[rand() % map->GetGhostRoad().size()]->GetPosition()
        ));
        blinky->shortestPath(
            map->changeToPositionInVector(blinky->GetPosition())
        );
    }

    if(pinky->IsArrivePosition()){
        if(pinky->GetState() == "Dead")pinky->ReStart();
        int num = rand() % map->GetSmallBeans().size();
        while(!map->GetSmallBeans()[num]->GetVisibility()){
            num = rand() % map->GetSmallBeans().size();
        }
        pinky->SetTargetPosition(map->changeToPositionInVector(
            map->GetSmallBeans()[num]->GetPosition()
        ));
        pinky->shortestPath(
            map->changeToPositionInVector(pinky->GetPosition())
        );

    }

    if(inky->IsArrivePosition()){
        if(inky->GetState() == "Dead")inky->ReStart();
        inky->SetTargetPosition(map->changeToPositionInVector(
            map->GetLargeBeans()[rand() % map->GetLargeBeans().size()]->GetPosition()
        ));
        inky->shortestPath(
            map->changeToPositionInVector(inky->GetPosition())
        );
    }

    if(clyde->IsArrivePosition()){
        if(clyde->GetState() == "Dead")clyde->ReStart();
        clyde->SetTargetPosition(map->changeToPositionInVector(
            map->GetGhostRoad()[rand() % map->GetGhostRoad().size()]->GetPosition()
        ));
        clyde->shortestPath(
            map->changeToPositionInVector(clyde->GetPosition())
        );
    }

    if(blinky->GetState() == "Dead"){
        blinky->SetTargetPosition(map->changeToPositionInVector(
            {-16,56}
        ));
        blinky->shortestPath(
            map->changeToPositionInVector(blinky->GetPosition())
        );
    }

    if(pinky->GetState() == "Dead"){
        pinky->SetTargetPosition(map->changeToPositionInVector(
            {-16,56}
        ));
        pinky->shortestPath(
            map->changeToPositionInVector(pinky->GetPosition())
        );
    }

    if(inky->GetState() == "Dead"){
        inky->SetTargetPosition(map->changeToPositionInVector(
            {-16,56}
        ));
        inky->shortestPath(
            map->changeToPositionInVector(inky->GetPosition())
        );
    }

    if(clyde->GetState() == "Dead"){
        clyde->SetTargetPosition(map->changeToPositionInVector(
            {-16,56}
        ));
        clyde->shortestPath(
            map->changeToPositionInVector(clyde->GetPosition())
        );
    }

    blinky->move();
    pinky->move();
    inky->move();
    clyde->move();

    time++;
    if(time % (15 * 10) == 0){
        if(blinky->GetState() == "Vulnerable"){
            blinky->ReStart();
        }
        if(pinky->GetState() == "Vulnerable"){
            pinky->ReStart();
        }
        if(inky->GetState() == "Vulnerable"){
            inky->ReStart();
        }
        if(clyde->GetState() == "Vulnerable"){
            clyde->ReStart();
        }
    }

    if(lifeSystem->IsDone()) m_CurrentState = State::END;

    /*
     * Do not touch the code below as they serve the purpose for
     * closing the window.
     */
    if (Util::Input::IsKeyUp(Util::Keycode::ESCAPE) ||
        Util::Input::IfExit()) {
        m_CurrentState = State::END;
    }//改到在UI按ESC才有到END，在這按ESC是回UI

    root.Update();
}

// load file

