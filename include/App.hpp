#ifndef APP_HPP
#define APP_HPP

#include "pch.hpp" // IWYU pragma: export

#include "Util/Root.hpp"
#include "Map.hpp"
#include "Block.hpp"
#include "Util/Text.hpp"
//#include "PhaseResourceManger.hpp"
//#include "AnimatedCharacter.hpp"

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

    Util::Root m_Root;

    std::shared_ptr<Map> m_Map;
    std::shared_ptr<Block> m_Block;
    /*std::vector<std::shared_ptr<Character>> m_Doors;

    std::shared_ptr<AnimatedCharacter> m_Bee;
    std::shared_ptr<AnimatedCharacter> m_Ball;

    std::shared_ptr<PhaseResourceManger> m_PRM;*/

    bool m_EnterDown = false;
};

#endif
