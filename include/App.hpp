#ifndef APP_HPP
#define APP_HPP

#include "pch.hpp" // IWYU pragma: export
#include "Fruit.hpp"
#include "Pacman.hpp"
#include "ghost/Ghost.hpp"
#include "ghost/GhostDeadState.hpp"
#include "ghost/GhostNormalState.hpp"
#include "ghost/GhostVulnerableState.hpp"
#include "outSkirt/LifeSystem.hpp"
#include "outSkirt/FruitSystem.hpp"
#include "RandomFactory.hpp"
#include "outSkirt/ScoreSystem.hpp"

#include "Util/Renderer.hpp"
#include "Map.hpp"
#include "Block.hpp"
#include "Util/Text.hpp"

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

    //方便外框顯示的位置調整
    int thisMapX;
    int thisMapY;
    std::shared_ptr<Map> map;
    //std::shared_ptr<Block> m_Block;
    bool m_EnterDown = false;

    std::shared_ptr<LifeSystem> lifeSystem;
    std::shared_ptr<ScoreSystem> scoreSystem;
    std::shared_ptr<FruitSystem> fruitSystem;
    EventManager eventManager = EventManager();
    RandomFactory randomFactory = RandomFactory();

    std::shared_ptr<Ghost> blinky;
    std::shared_ptr<Ghost> pinky;
    std::shared_ptr<Ghost> inky;
    std::shared_ptr<Ghost> clyde;

    std::shared_ptr<Pacman> pacman;

    //std::shared_ptr<Fruit> cherry;

    enum Direction { UP, DOWN, RIGHT, LEFT, NONE };
    Direction currentDirection = LEFT;
    Direction nextDirection = NONE;
    std::vector<std::string> VulnerableGhostsImages;

    int xMap;
    int yMap;

protected:


protected:

    std::shared_ptr<Map> GetMap(){
        return map;
    }
};

#endif
