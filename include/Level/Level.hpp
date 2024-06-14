#ifndef REPLACE_WITH_YOUR_PROJECT_NAME_LEVEL_HPP
#define REPLACE_WITH_YOUR_PROJECT_NAME_LEVEL_HPP

#include <random>
#include <string>
#include <sstream>
#include <iostream>
#include <fstream>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

#include "Character/Pacman.hpp"
#include "ghost/Ghost.hpp"
#include "life/LifeSystem.hpp"
#include "fruit/FruitSystem.hpp"
#include "score/ScoreSystem.hpp"
#include "map/Map.hpp"

#include "Util/Input.hpp"
#include "Util/Time.hpp"
#include "LevelBuilder.hpp"

class Level : public Util::GameObject {
public:
    explicit Level(std::string player) {
        playerName = player;
    };

    void Initialized(int nowLevel) {//之後加入讀入系統
        this->nowLevel = nowLevel;
        std::ostringstream oss;
        oss << nowLevel;
        std::string levelNumber = oss.str();
        levelBuilder = LevelBuilder(RESOURCE_DIR"/Text/level00" + levelNumber + ".json");
        levelBuilder.Print();

        map = std::make_shared<Map>(levelBuilder.getMapSize(), levelBuilder.getMap());
        this->AddChild(map);

        lifeSystem = std::make_shared<LifeSystem>(levelBuilder.getLifeSystemHitPoint(),
                                                  levelBuilder.getLifeSystemPosition());
        lifeSystem->AddEventManager(eventManager);
        this->AddChild(lifeSystem);

        fruitSystem = std::make_shared<FruitSystem>(levelBuilder.getFruitSystemPosition(),
                                                    levelBuilder.getCherryPosition());
        this->AddChild(fruitSystem);

        scoreSystem = std::make_shared<ScoreSystem>(levelBuilder.getGameScorePosition(),
                                                    levelBuilder.getHightScorePosition());
        scoreSystem->AddEventManager(eventManager);
        this->AddChild(scoreSystem);

        for (int i = 0; i < 4; i++) {
            ghosts.at(levelBuilder.getGhostNames().at(i)) = std::make_shared<Ghost>(
                levelBuilder.getGhostNames().at(i),
                map->getGhostMap(),
                levelBuilder.getGhostInitialPosition().at(i)
            );
            this->AddChild(ghosts.at(levelBuilder.getGhostNames().at(i)));
        }

        for (auto &ghost: ghosts) {
            ghost.second->setJumpPoint(levelBuilder.getJumpPoints());
        }

        pacman = std::make_shared<Pacman>();
        pacman->AddEventManager(eventManager);
        pacman->setJumpPoint(levelBuilder.getJumpPoints());
        pacman->setInitialPosition(levelBuilder.getPacmanPosition());
        pacman->SetUpImages(levelBuilder.getPacmanUpImages());
        pacman->SetDownImages(levelBuilder.getPacmanDownImages());
        pacman->SetRightImages(levelBuilder.getPacmanRightImages());
        pacman->SetLeftImages(levelBuilder.getPacmanLeftImages());
        pacman->SetDeadImages(levelBuilder.getPacmanDeadImages());

        pacman->Start();
        this->AddChild(pacman);

        std::string scoresPath = RESOURCE_DIR"/Text/scores00" + levelNumber + ".json";
        // 打開並讀取 JSON 文件
        std::ifstream file(scoresPath);
        json scores;

        // 檢查玩家名稱是否已存在於 scores 中
        if (scores.contains(playerName)) {
            int high_score = scores[playerName];
            scoreSystem->SetHighestScore(high_score);
        }

    }

    int Update() {

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

            pacman->JumpPoint();
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
                        ghost.second->setRoad(
                            map->shortestPath(ghost.second->GetPosition(), levelBuilder.getGhostRestartPosition()));
                    }
                }
            }
        };
        pacmanCollidesGhosts();

        std::function<void()> blinkyNormalMove = [&]() {
            glm::vec2 targetPosition = ghosts.at("blinky")->getTargetPosition();
            std::vector<std::vector<glm::vec2>> jumpPoints = levelBuilder.getJumpPoints();

            auto it = find_if(jumpPoints.begin(), jumpPoints.end(),
                              [&targetPosition](std::vector<glm::vec2> &obj) {
                                  return (obj[0] == targetPosition);
                              });

            if (it != jumpPoints.end()) {
                if (ghosts.at("blinky")->IsArrivePosition()) {
                    ghosts.at("blinky")->setRoad(
                        map->shortestPath(ghosts.at("blinky")->GetPosition(), pacman->GetPosition()));
                    ghosts.at("blinky")->SetTargetPosition(pacman->GetPosition());
                }
            } else {
                glm::vec2 position = pacman->GetPosition();
                ghosts.at("blinky")->setRoad(map->shortestPath(ghosts.at("blinky")->GetPosition(), position));
                ghosts.at("blinky")->SetTargetPosition(position);
            }
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
                glm::vec2 targetPosition = ghosts.at("pinky")->getTargetPosition();
                std::vector<std::vector<glm::vec2>> jumpPoints = levelBuilder.getJumpPoints();

                auto it = find_if(jumpPoints.begin(), jumpPoints.end(),
                                  [&targetPosition](std::vector<glm::vec2> &obj) {
                                      return (obj[0] == targetPosition);
                                  });

                if (it != jumpPoints.end()) {
                    if (ghosts.at("pinky")->IsArrivePosition()) {
                        ghosts.at("pinky")->setRoad(
                            map->shortestPath(ghosts.at("pinky")->GetPosition(), pacman->GetPosition()));
                        ghosts.at("pinky")->SetTargetPosition(pacman->GetPosition());
                    }
                } else {
                    glm::vec2 position = pacman->GetPosition();
                    ghosts.at("pinky")->setRoad(map->shortestPath(ghosts.at("pinky")->GetPosition(), position));
                    ghosts.at("pinky")->SetTargetPosition(position);
                }
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
                if (ghost.second->IsArrivePosition()) {
                    ghost.second->Normal();
                }
            }
        }

        if (ghosts.at("blinky")->GetState() == "Vulnerable" && ghosts.at("blinky")->IsArrivePosition()) {
            blinkyVulnerableMove();
        }

        if (ghosts.at("pinky")->GetState() == "Vulnerable" && ghosts.at("pinky")->IsArrivePosition()) {
            pinkyVulnerableMove();
        }

        if (ghosts.at("inky")->GetState() == "Vulnerable" && ghosts.at("inky")->IsArrivePosition()) {
            inkyVulnerableMove();
        }

        if (ghosts.at("clyde")->GetState() == "Vulnerable" && ghosts.at("clyde")->IsArrivePosition()) {
            clydeVulnerableMove();
        }

        if (ghosts.at("blinky")->GetState() == "Normal") {
            blinkyNormalMove();
        }

        if (ghosts.at("pinky")->GetState() == "Normal") {
            pinkyNormalMove();
        }

        if (ghosts.at("inky")->GetState() == "Normal") {
            inkyNormalMove();
        }

        if (ghosts.at("clyde")->GetState() == "Normal") {
            clydeNormalMove();
        }

        for (auto &ghost: ghosts) {
            if (!pacman->IsDead()) {
                ghost.second->move();
                ghost.second->JumpPoint();
            }
        }


        time++;
        for (auto &ghost: ghosts) {
            if (time % (15 * 10) == 0) {
                if (ghost.second->GetState() == "Vulnerable") {
                    ghost.second->Normal();
                }
            }
        }


        if (Util::Input::IfExit()) {
            IsBackFromGame = true;
            return 1;
        }//變成END

        if (Util::Input::IsKeyUp(Util::Keycode::ESCAPE) ||
            lifeSystem->IsDone()) {
            SaveScore();
            IsBackFromGame = true;
            return 2;
        }//改到在UI按ESC才有到END，在這按ESC是回UI

        if (map->GetBeansNumber() == 0) {
            SaveScore();
            IsBackFromGame = true;
            return 3;
        }//切換下一關

        return 0;
        //root.Update();
    }

    void SaveScore() {
        std::ostringstream oss;
        oss << nowLevel;
        std::string levelNumber = oss.str();
        std::string scoresPath = RESOURCE_DIR"/Text/scores00" + levelNumber + ".json";
        // 打開並讀取 JSON 文件
        std::ifstream file(scoresPath);
        json scores;

        // 檢查玩家名稱是否已存在於 scores 中
        if (scores.contains(playerName)) {
            int high_score = scores[playerName];

            // 如果當前分數高於已有的最高分數，則更新
            if (scoreSystem->GetHighestScore() > high_score) {
                scores[playerName] = scoreSystem->GetHighestScore();
            }
        } else {
            // 如果玩家名稱不存在，添加新的玩家名稱和分數
            scores[playerName] = scoreSystem->GetHighestScore();
        }

        std::ofstream outfile(scoresPath);
        outfile << scores.dump(4); // 4 為縮進空格數
        outfile.close();
    }

private:
    //systems contain object
    std::shared_ptr<Map> map;

    std::shared_ptr<LifeSystem> lifeSystem;
    std::shared_ptr<ScoreSystem> scoreSystem;
    std::shared_ptr<FruitSystem> fruitSystem;
    EventManager *eventManager = new EventManager();
//
    std::string playerName = "player001";
    bool IsBackFromGame = true;
    int nowLevel = 1;
//
    std::shared_ptr<Ghost> blinky;
    std::shared_ptr<Ghost> pinky;
    std::shared_ptr<Ghost> inky;
    std::shared_ptr<Ghost> clyde;

    std::map<std::string, std::shared_ptr<Ghost>> ghosts = {
        {"blinky", blinky},
        {"pinky",  pinky},
        {"inky",   inky},
        {"clyde",  clyde}
    };

    std::shared_ptr<Pacman> pacman;


    std::vector<std::string> VulnerableGhostsImages;

    int time = 0;

    LevelBuilder levelBuilder;
};

#endif //REPLACE_WITH_YOUR_PROJECT_NAME_LEVEL_HPP
