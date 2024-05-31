#include<chrono>
#include <random>
#include <iostream>

#include "App.hpp"
#include "Util/Input.hpp"

void App::Update() {
    std::function<void()> pacmanMove = [&]() {
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
        }
    };
    pacmanMove();

    std::function<void()> eatBeans = [&]() {
        for (const std::shared_ptr<Block> &bean: map->GetSmallBeans()) {
            if (pacman->eatBean(bean) && bean->GetVisibility()) {
                bean->SetVisible(false);
                if (bean->GetCodeNumber() == 0) {
                    pacman->HandleScoreUpCollision();
                } else if (bean->GetCodeNumber() == 43) {
                    for (auto &ghost: ghosts) {
                        ghost.second->Vulnerable();
                    }
                    pacman->HandleScoreUpCollision(75);
                    time = 0;
                }

            }
        }
    };
    eatBeans();

    std::function<void()> fruitEvent = [&]() {
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
    };
    fruitEvent();

    std::function<void()> pacmanDead = [&]() {
        if (pacman->IsDead() && pacman->IfAnimationEnds()) {
            pacman->ReStart();
            for (const auto &ghost: ghosts) {
                ghost.second->ReStart();
            }
        }
    };
    pacmanDead();

    std::function<void()> pacmanCollidesGhosts = [&]() {
        for (auto &ghost: ghosts) {
            if (!pacman->IsDead() && pacman->IsCollides(ghost.second)) {
                if (ghost.second->GetState() == "Normal") {
                    pacman->Dead();
                } else if (ghost.second->GetState() == "Vulnerable") {
                    ghost.second->Dead();
                    ghost.second->setRoad(map->shortestPath(ghost.second->GetPosition(), glm::vec2{-16, 56}));
                }
            }
        }
    };
    pacmanCollidesGhosts();

    std::function<void()> blinkyNormalMove = [&]() {
        ghosts.at("blinky")->setRoad(map->shortestPath(ghosts.at("blinky")->GetPosition(), pacman->GetPosition()));
    };

    std::function<void()> pinkyNormalMove = [&]() {

        glm::vec2 position = pacman->GetPosition();

        switch (pacman->getCurrentDirection()) {
            case Pacman::Direction::up:
                position.y += 64.0f;
                break;
            case Pacman::Direction::down:
                position.y -= 64.0f;
                break;
            case Pacman::Direction::right:
                position.x += 64.0f;
                break;
            case Pacman::Direction::left:
                position.x -= 64.0f;
        }
        if (map->IsGhostRoad(position)) {
            ghosts.at("pinky")->setRoad(map->shortestPath(ghosts.at("pinky")->GetPosition(), position));
        }
    };

    std::function<void()> inkyNormalMove = [&]() {
        glm::vec2 centerPosition = pacman->GetPosition();

        switch (pacman->getCurrentDirection()) {
            case Pacman::Direction::up:
                centerPosition.y += 32.0f;
                break;
            case Pacman::Direction::down:
                centerPosition.y -= 32.0f;
                break;
            case Pacman::Direction::right:
                centerPosition.x += 32.0f;
                break;
            case Pacman::Direction::left:
                centerPosition.x -= 32.0f;
        }

        centerPosition *= 2;
        glm::vec2 ghostPosition = ghosts.at("blinky")->GetPosition();
        glm::vec2 position = centerPosition - ghostPosition;

        if (!map->IsGhostRoad(position)) {
            position = ghostPosition - centerPosition;
        }
        if (map->IsGhostRoad(position)) {
            ghosts.at("inky")->setRoad(map->shortestPath(ghosts.at("inky")->GetPosition(), position));
        }

        if (ghosts.at("inky")->IsArrivePosition()) {
            std::random_device rd;
            std::mt19937 gen(rd());

            unsigned num = gen() % map->GetSmallBeans().size();
            while (!map->GetSmallBeans()[num]->GetVisibility()) {
                num = gen() % map->GetSmallBeans().size();
            }
            ghosts.at("inky")->setRoad(
                map->shortestPath(ghosts.at("inky")->GetPosition(), map->GetSmallBeans()[num]->GetPosition()));
        }

    };

    std::function<void()> clydeNormalMove = [&]() {
        glm::vec2 pacmanPosition = pacman->GetPosition();
        glm::vec2 ghostPosition = ghosts.at("clyde")->GetPosition();

        if (ghosts.at("clyde")->IsArrivePosition()) {

            auto IsIntersection = [&](unsigned num) {
                LOG_DEBUG("123456");
                int counter = 0;
                glm::vec2 positionA = map->GetGhostRoad()[num]->GetPosition();
                if (map->IsGhostRoad({positionA.x, positionA.y + 16}) ||
                    map->IsGhostRoad({positionA.x, positionA.y - 16}))
                    counter += 1;
                if (map->IsGhostRoad({positionA.x + 16, positionA.y}) ||
                    map->IsGhostRoad({positionA.x - 16, positionA.y}))
                    counter += 1;
                return counter;
            };

            auto IsDistanceBiggerThanEight = [&]() {
                if ((abs(pacmanPosition.x - ghostPosition.x) > 128) ||
                    (abs(pacmanPosition.y - ghostPosition.y) > 128)) {
                    return true;
                }
                if ((abs(pacmanPosition.x - ghostPosition.x) < 128) ||
                    (abs(pacmanPosition.y - ghostPosition.y) < 128)) {
                    return false;
                }
                return false;
            };

            if (IsDistanceBiggerThanEight()) {
                ghosts.at("clyde")->setRoad(map->shortestPath(ghostPosition, pacman->GetPosition()));
            } else {
                std::random_device rd;
                std::mt19937 gen(rd());

                unsigned num = gen() % map->GetGhostRoad().size();

                while (!IsIntersection(num) && IsDistanceBiggerThanEight()) {
                    num = gen() % map->GetGhostRoad().size();

                }
                ghosts.at("clyde")->setRoad(
                    map->shortestPath(ghosts.at("clyde")->GetPosition(), map->GetGhostRoad()[num]->GetPosition()));

            }
        }
    };

    auto isBetween = [&](glm::vec2 maxPosition, glm::vec2 minPosition, glm::vec2 position) {
        return minPosition.x <= position.x &&
               position.x <= maxPosition.x &&
               minPosition.y <= position.y &&
               position.y <= maxPosition.y;
    };

    std::function<void()> blinkyVulnerableMove = [&]() {
        std::random_device rd;
        std::mt19937 gen(rd());

        unsigned num = gen() % map->GetGhostRoad().size();
        while (!isBetween(levelBuilder.getBlinkyVulnerableMax(), levelBuilder.getBlinkyVulnerableMin(),
                          map->GetGhostRoad()[num]->GetPosition())) {
            num = gen() % map->GetGhostRoad().size();
        }

        if (ghosts.at("blinky")->IsArrivePosition()) {
            ghosts.at("blinky")->setRoad(
                map->shortestPath(ghosts.at("blinky")->GetPosition(), map->GetGhostRoad()[num]->GetPosition()));
        }
    };

    std::function<void()> pinkyVulnerableMove = [&]() {
        std::random_device rd;
        std::mt19937 gen(rd());

        unsigned num = gen() % map->GetGhostRoad().size();
        while (!isBetween(levelBuilder.getPinkyVulnerableMax(), levelBuilder.getPinkyVulnerableMin(),
                          map->GetGhostRoad()[num]->GetPosition())) {
            num = gen() % map->GetGhostRoad().size();
        }

        if (ghosts.at("pinky")->IsArrivePosition()) {
            ghosts.at("pinky")->setRoad(
                map->shortestPath(ghosts.at("pinky")->GetPosition(), map->GetGhostRoad()[num]->GetPosition()));
        }
    };

    std::function<void()> inkyVulnerableMove = [&]() {
        std::random_device rd;
        std::mt19937 gen(rd());

        unsigned num = gen() % map->GetGhostRoad().size();
        while (!isBetween(levelBuilder.getInkyVulnerableMax(), levelBuilder.getInkyVulnerableMin(),
                          map->GetGhostRoad()[num]->GetPosition())) {
            num = gen() % map->GetGhostRoad().size();
        }

        if (ghosts.at("inky")->IsArrivePosition()) {
            ghosts.at("inky")->setRoad(
                map->shortestPath(ghosts.at("inky")->GetPosition(), map->GetGhostRoad()[num]->GetPosition()));
        }
    };

    std::function<void()> clydeVulnerableMove = [&]() {
        std::random_device rd;
        std::mt19937 gen(rd());

        unsigned num = gen() % map->GetGhostRoad().size();
        while (!isBetween(levelBuilder.getClydeVulnerableMax(), levelBuilder.getClydeVulnerableMin(),
                          map->GetGhostRoad()[num]->GetPosition())) {
            num = gen() % map->GetGhostRoad().size();
        }

        if (ghosts.at("clyde")->IsArrivePosition()) {
            ghosts.at("clyde")->setRoad(
                map->shortestPath(ghosts.at("clyde")->GetPosition(), map->GetGhostRoad()[num]->GetPosition()));
        }
    };

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

