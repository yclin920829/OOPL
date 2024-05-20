#include <iostream>
#include<chrono>
#include <random>

#include "App.hpp"
#include "Util/Input.hpp"

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
                pacman->MoveUp();
            }
            break;
        case Pacman::Direction::down:
            if (map->IsPacmanRoad({oldPosition.x, oldPosition.y - 16.0f})) {
                pacman->MoveDown();
            }
            break;
        case Pacman::Direction::right:
            if (map->IsPacmanRoad({oldPosition.x + 16.0f, oldPosition.y})) {
                pacman->MoveRight();
            }
            break;
        case Pacman::Direction::left:
            if (map->IsPacmanRoad({oldPosition.x - 16.0f, oldPosition.y})) {
                pacman->MoveLeft();
            }
            break;
        case Pacman::Direction::none:
            break;
    }

    for (const std::shared_ptr<Block> &bean: map->GetSmallBeans()) {
        if (pacman->eatBean(bean) && bean->GetVisibility()) {
            bean->SetVisible(false);
            pacman->HandleScoreUpCollision();
        }
    }

    for (const std::shared_ptr<Block> &bean: map->GetLargeBeans()) {
        if (pacman->eatBean(bean) && bean->GetVisibility()) {
            bean->SetVisible(false);
            for (auto &ghost: ghosts) {
                ghost.second->Vulnerable();
            }
            pacman->HandleScoreUpCollision(75);
            time = 0;
        }
    }

    int counter = 0;
    for (const std::shared_ptr<Block> &bean: map->GetSmallBeans()) {
        if (!bean->GetVisibility()) {
            counter++;
        }
    }

    if ((counter % (map->GetSmallBeans().size() / 3)) == 0 && counter) {
        fruitSystem->getCherry()->SetVisible(true);
    }

    if (pacman->IsCollides(fruitSystem->getCherry()) && fruitSystem->getCherry()->GetVisibility()) {
        fruitSystem->getCherry()->SetVisible(false);
        pacman->HandleScoreUpCollision(100);
    }

    if (pacman->IsDead() && pacman->IfAnimationEnds()) {
        pacman->ReStart();
        pacman->setNextDirection(Pacman::Direction::left);
        for (const auto &ghost: ghosts) {
            ghost.second->ReStart();
            ghost.second->SetTargetPosition(map->changeToPositionInVector({-208, 248}));
            ghost.second->shortestPath(
                map->changeToPositionInVector(ghost.second->GetPosition())
            );
        }
    }

    for (auto &ghost: ghosts) {
        if (!pacman->IsDead() && pacman->IsCollides(ghost.second)) {
            if (ghost.second->GetState() == "Normal") {
                pacman->Dead();
            } else if (ghost.second->GetState() == "Vulnerable") {
                ghost.second->Dead();
            }
        }
    }

    std::random_device rd;
    std::mt19937 gen(rd());

    if (ghosts.at("blinky")->IsArrivePosition()) {
        if (ghosts.at("blinky")->GetState() == "Dead") {
            ghosts.at("blinky")->ReStart();
        }
        ghosts.at("blinky")->SetTargetPosition(map->changeToPositionInVector(
//            pacman->GetPosition()
            map->GetGhostRoad()[gen() % map->GetGhostRoad().size()]->GetPosition()
        ));
        ghosts.at("blinky")->shortestPath(
            map->changeToPositionInVector(ghosts.at("blinky")->GetPosition())
        );
    }

    if (ghosts.at("pinky")->IsArrivePosition()) {
        if (ghosts.at("pinky")->GetState() == "Dead")ghosts.at("pinky")->ReStart();
        unsigned num = gen() % map->GetSmallBeans().size();
        while (!map->GetSmallBeans()[num]->GetVisibility()) {
            num = gen() % map->GetSmallBeans().size();
        }
        ghosts.at("pinky")->SetTargetPosition(map->changeToPositionInVector(
            map->GetSmallBeans()[num]->GetPosition()
        ));
        ghosts.at("pinky")->shortestPath(
            map->changeToPositionInVector(ghosts.at("pinky")->GetPosition())
        );

    }

    if (ghosts.at("inky")->IsArrivePosition()) {
        if (ghosts.at("inky")->GetState() == "Dead")ghosts.at("inky")->ReStart();
        ghosts.at("inky")->SetTargetPosition(map->changeToPositionInVector(
            map->GetLargeBeans()[gen() % map->GetLargeBeans().size()]->GetPosition()
        ));
        ghosts.at("inky")->shortestPath(
            map->changeToPositionInVector(ghosts.at("inky")->GetPosition())
        );
    }

    if (ghosts.at("clyde")->IsArrivePosition()) {
        if (ghosts.at("clyde")->GetState() == "Dead")ghosts.at("clyde")->ReStart();
        ghosts.at("clyde")->SetTargetPosition(map->changeToPositionInVector(
            map->GetGhostRoad()[gen() % map->GetGhostRoad().size()]->GetPosition()
        ));
        ghosts.at("clyde")->shortestPath(
            map->changeToPositionInVector(ghosts.at("clyde")->GetPosition())
        );
    }

    for (auto &ghost: ghosts) {
        if (ghost.second->GetState() == "Dead") {
            ghost.second->SetTargetPosition(map->changeToPositionInVector(
                {-16, 56}
            ));
            ghost.second->shortestPath(
                map->changeToPositionInVector(ghost.second->GetPosition())
            );
        }
    }

    for (auto &ghost: ghosts) {
        if (!pacman->IsDead()) {
            ghost.second->move();
        }
    }


    time++;
    for (auto &ghost: ghosts) {
        if (time % (15 * 10) == 0) {
            if (ghost.second->GetState() == "Vulnerable") {
                ghost.second->ReStart();
            }
        }
    }


//    if (lifeSystem->IsDone()) m_CurrentState = State::END;

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

// load file

