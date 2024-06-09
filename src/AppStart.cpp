#include "App.hpp"

#include "Util/Input.hpp"
#include "Util/Logger.hpp"

void App::Start() {
    LOG_TRACE("Start");

    levelBuilder = LevelBuilder(RESOURCE_DIR"/Text/level002.json");
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


    for(int i = 0; i < 4;i++){
        ghosts.at(levelBuilder.getGhostNames().at(i)) = std::make_shared<Ghost>(
            levelBuilder.getGhostNames().at(i),
            levelBuilder.getGhostBFSMap(),
            levelBuilder.getGhostInitialPosition().at(i)
        );
        root.AddChild(ghosts.at(levelBuilder.getGhostNames().at(i)));
    }

    pacman = std::make_shared<Pacman>();
    pacman->AddEventManager(eventManager);
    pacman->setJumpPoint(levelBuilder.getJumpPoints());
    pacman->SetUpImages(levelBuilder.getPacmanUpImages());
    pacman->SetDownImages(levelBuilder.getPacmanDownImages());
    pacman->SetRightImages(levelBuilder.getPacmanRightImages());
    pacman->SetLeftImages(levelBuilder.getPacmanLeftImages());
    pacman->SetDeadImages(levelBuilder.getPacmanDeadImages());

    pacman->SetPosition(levelBuilder.getPacmanPosition());
    pacman->Start();
    root.AddChild(pacman);

    m_CurrentState = State::UPDATE;
}
