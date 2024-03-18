#ifndef APP_HPP
#define APP_HPP

#include "pch.hpp" // IWYU pragma: export
#include "Fruit.hpp"
#include "Ghost.hpp"
#include "Pacman.hpp"
#include "Util/Root.hpp"
#include "PacmanDead.hpp"

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

    std::shared_ptr<Ghost> blinky;
    std::shared_ptr<Ghost> pinky;
    std::shared_ptr<Ghost> inky;
    std::shared_ptr<Ghost> clyde;
    std::shared_ptr<Ghost> ghost_dead;
    std::shared_ptr<Ghost> vulnerable_ghost;

    std::shared_ptr<Pacman> pacman;
    std::shared_ptr<PacmanDead> pacman_dead;

    std::shared_ptr<Fruit> cherry;

protected:
    std::shared_ptr<Ghost> createGhost(const std::string& dir, float posX, float posY, const std::string& name) {
        std::shared_ptr<Ghost> ghost = std::make_shared<Ghost>();
        ghost->SetUpImages({dir + "/Image/Character/" + name + "/" + name + "_U_01.png", dir + "/Image/Character/" + name + "/" + name + "_U_02.png"});
        ghost->SetDownImages({dir + "/Image/Character/" + name + "/" + name + "_D_01.png", dir + "/Image/Character/" + name + "/" + name + "_D_02.png"});
        ghost->SetRightImages({dir + "/Image/Character/" + name + "/" + name + "_R_01.png", dir + "/Image/Character/" + name + "/" + name + "_R_02.png"});
        ghost->SetLeftImages({dir + "/Image/Character/" + name + "/" + name + "_L_01.png", dir + "/Image/Character/" + name + "/" + name + "_L_02.png"});

        ghost->SetZIndex(5);
        ghost->SetVisible(true);
        ghost->SetPosition({posX, posY});
        ghost->SetDrawble2();

        return ghost;
    }

    std::shared_ptr<Pacman> createPacman(const std::string& dir, float posX, float posY, const std::string& name) {
        std::shared_ptr<Pacman> pacman = std::make_shared<Pacman>();
        pacman->SetUpImages({dir + "/Image/Character/" + name + "/" + name + "_U_01.png", dir + "/Image/Character/" + name + "/" + name + "_U_02.png"});
        pacman->SetDownImages({dir + "/Image/Character/" + name + "/" + name + "_D_01.png", dir + "/Image/Character/" + name + "/" + name + "_D_02.png"});
        pacman->SetRightImages({dir + "/Image/Character/" + name + "/" + name + "_R_01.png", dir + "/Image/Character/" + name + "/" + name + "_R_02.png"});
        pacman->SetLeftImages({dir + "/Image/Character/" + name + "/" + name + "_L_01.png", dir + "/Image/Character/" + name + "/" + name + "_L_02.png"});

        pacman->SetDrawble2();
        pacman->SetZIndex(5);
        pacman->SetVisible(true);
        pacman->SetPosition({posX, posY});

        return pacman;
    }
};

#endif
