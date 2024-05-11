#ifndef APP_HPP
#define APP_HPP

#include "Pacman.hpp"
#include "ghost/Ghost.hpp"
#include "life/LifeSystem.hpp"
#include "fruit/FruitSystem.hpp"
#include "score/ScoreSystem.hpp"

#include "Util/Renderer.hpp"
#include "Map.hpp"
#include "LevelBuilder.hpp"

class App {
public:
    enum class State {
        START,
        UPDATE,
        END,
    };

    State GetCurrentState() const { return m_CurrentState; }

    void Start();

    void Update();

    void End(); // NOLINT(readability-convert-member-functions-to-static)

private:
    void ValidTask();

private:
  
    State m_CurrentState = State::START;

    Util::Renderer root;

    std::shared_ptr<Map> map;

    std::shared_ptr<LifeSystem> lifeSystem;
    std::shared_ptr<ScoreSystem> scoreSystem;
    std::shared_ptr<FruitSystem> fruitSystem;
    EventManager * eventManager = new EventManager();

    std::shared_ptr<Ghost> blinky;
    std::shared_ptr<Ghost> pinky;
    std::shared_ptr<Ghost> inky;
    std::shared_ptr<Ghost> clyde;

    std::map<std::string, std::shared_ptr<Ghost>> ghosts ={
        {"blinky",blinky},
        {"pinky",pinky},
        {"inky",inky},
        {"clyde",clyde}
    };

    std::shared_ptr<Pacman> pacman;


    std::vector<std::string> VulnerableGhostsImages;

    int time = 0;

    LevelBuilder levelBuilder;
};

#endif
