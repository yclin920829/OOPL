#include "App.hpp"

#include "Util/Input.hpp"
#include "Util/Logger.hpp"

void App::Start() {
    LOG_TRACE("Start");

    levelBuilder = LevelBuilder(RESOURCE_DIR"/Text/level001.json");
    levelBuilder.Print();

    map = std::make_shared<Map>(levelBuilder.getMapSize(), levelBuilder.getMap());
    root.AddChild(map);

    lifeSystem = std::make_shared<LifeSystem>(levelBuilder.getLifeSystemHitPoint(),
                                              levelBuilder.getLifeSystemPosition());
    lifeSystem->AddEventManager(eventManager);
    root.AddChild(lifeSystem);

    fruitSystem = std::make_shared<FruitSystem>(levelBuilder.getFruitSystemPosition());
    root.AddChild(fruitSystem);

    scoreSystem = std::make_shared<ScoreSystem>(levelBuilder.getGameScorePosition(), levelBuilder.getHightScorePosition());
    scoreSystem->AddEventManager(eventManager);
    root.AddChild(scoreSystem);


    ghosts.at("blinky") = std::make_shared<Ghost>("blinky", map->GetGhostMap(), glm::vec2{0.0, 104});
    ghosts.at("pinky") = std::make_shared<Ghost>("pinky", map->GetGhostMap(), glm::vec2{-32, 56});
    ghosts.at("inky") = std::make_shared<Ghost>("inky", map->GetGhostMap(), glm::vec2{-16.0, 56});
    ghosts.at("clyde") = std::make_shared<Ghost>("clyde", map->GetGhostMap(), glm::vec2{16.0, 56});

    for (auto &ghost: ghosts) {
        root.AddChild(ghost.second);
    }

    std::vector<std::string> deadImages;
    deadImages.reserve(13);
    for (int i = 0; i < 13; ++i) {
        deadImages.push_back(
            RESOURCE_DIR"/Image/Character/Pacman_dead/Pacman_dead" + std::to_string(i + 1) + ".png");
    }


    pacman = std::make_shared<Pacman>(eventManager);
    pacman->SetUpImages(
        {RESOURCE_DIR"/Image/Character/pacman/pacman_U_01.png", RESOURCE_DIR"/Image/Character/pacman/pacman_U_02.png"});
    pacman->SetDownImages(
        {RESOURCE_DIR"/Image/Character/pacman/pacman_D_01.png", RESOURCE_DIR"/Image/Character/pacman/pacman_D_02.png"});
    pacman->SetRightImages(
        {RESOURCE_DIR"/Image/Character/pacman/pacman_R_01.png", RESOURCE_DIR"/Image/Character/pacman/pacman_R_02.png"});
    pacman->SetLeftImages(
        {RESOURCE_DIR"/Image/Character/pacman/pacman_L_01.png", RESOURCE_DIR"/Image/Character/pacman/pacman_L_02.png"});
    pacman->SetDeadImages(deadImages);

    pacman->SetZIndex(20);
    pacman->SetVisible(true);
    pacman->SetPosition({-0.0f, -88.0f});
    pacman->Start();
    root.AddChild(pacman);

    for (auto &ghost: ghosts) {
        ghost.second->SetTargetPosition(map->changeToPositionInVector({-208, 248}));
        ghost.second->shortestPath(
            map->changeToPositionInVector(ghost.second->GetPosition())
        );
    }

    m_CurrentState = State::UPDATE;
}
