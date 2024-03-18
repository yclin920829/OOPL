#include "App.hpp"
#include "Util/Logger.hpp"

void App::Start() {
    LOG_TRACE("Start");

    blinky = createGhost(RESOURCE_DIR, -100.0f, -100.0f, "blinky");
    pinky = createGhost(RESOURCE_DIR, 100.0f, -100.0f, "pinky");
    inky = createGhost(RESOURCE_DIR, -100.0f, 100.0f, "inky");
    clyde = createGhost(RESOURCE_DIR, 100.0f, 100.0f, "clyde");
    m_Root.AddChild(blinky);
    m_Root.AddChild(pinky);
    m_Root.AddChild(inky);
    m_Root.AddChild(clyde);

    pacman = createPacman(RESOURCE_DIR, 0.0f, 0.0f, "pacman");
    m_Root.AddChild(pacman);

    cherry = std::make_shared<Fruit>(RESOURCE_DIR"/Image/Character/Fruit/cherry.png");
    cherry->SetPosition({0.0f, 100.0f});
    cherry->SetZIndex(1);
    m_Root.AddChild(cherry);

    std::vector<std::string> deadImages;
    deadImages.reserve(13);
    for (int i = 0; i < 13; ++i) {
        deadImages.emplace_back(RESOURCE_DIR"/Image/Character/Pacman_dead/Pacman_dead" + std::to_string(i + 1) + ".png");
    }

    pacman_dead = std::make_shared<PacmanDead>(deadImages);
    pacman_dead->SetZIndex(5);
    pacman_dead->SetVisible(true);
    pacman_dead->SetPosition({0.0f, -100.0f});
    pacman->AddChild(pacman_dead);

    ghost_dead = std::make_shared<Ghost>();
    ghost_dead->SetUpImages({RESOURCE_DIR"/Image/Character/Ghost_dead/Ghost_dead_U.png"});
    ghost_dead->SetDownImages({RESOURCE_DIR"/Image/Character/Ghost_dead/Ghost_dead_D.png"});
    ghost_dead->SetRightImages({RESOURCE_DIR"/Image/Character/Ghost_dead/Ghost_dead_R.png"});
    ghost_dead->SetLeftImages({RESOURCE_DIR"/Image/Character/Ghost_dead/Ghost_dead_L.png"});
    ghost_dead->SetDrawble2();
    ghost_dead->SetZIndex(5);
    ghost_dead->SetVisible(true);
    ghost_dead->SetPosition({100.0f, 0.0f});
    m_Root.AddChild(ghost_dead);

    std::vector<std::string> a = {
        RESOURCE_DIR"/Image/Character/VulnerableGhosts/VulnerableGhosts_B_01.png",
        RESOURCE_DIR"/Image/Character/VulnerableGhosts/VulnerableGhosts_B_02.png",
        RESOURCE_DIR"/Image/Character/VulnerableGhosts/VulnerableGhosts_W_01.png",
        RESOURCE_DIR"/Image/Character/VulnerableGhosts/VulnerableGhosts_W_02.png"
    };

    vulnerable_ghost = std::make_shared<Ghost>();
    vulnerable_ghost->SetUpImages(a);
    vulnerable_ghost->SetDownImages(a);
    vulnerable_ghost->SetRightImages(a);
    vulnerable_ghost->SetLeftImages(a);
    vulnerable_ghost->SetDrawble2();
    vulnerable_ghost->SetZIndex(5);
    vulnerable_ghost->SetVisible(true);
    vulnerable_ghost->SetPosition({-100.0f, 0.0f});
    m_Root.AddChild(vulnerable_ghost);

    m_CurrentState = State::UPDATE;
}
