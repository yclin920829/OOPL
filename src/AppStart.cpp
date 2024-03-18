#include "App.hpp"

#include "Util/Logger.hpp"

void App::Start() {
    LOG_TRACE("Start");

    VulnerableGhostsImages = {
            RESOURCE_DIR"/Image/Character/VulnerableGhosts/VulnerableGhosts_B_01.png",
            RESOURCE_DIR"/Image/Character/VulnerableGhosts/VulnerableGhosts_B_02.png",
            RESOURCE_DIR"/Image/Character/VulnerableGhosts/VulnerableGhosts_W_01.png",
            RESOURCE_DIR"/Image/Character/VulnerableGhosts/VulnerableGhosts_W_02.png"
    };

    blinky = CreateGhost(RESOURCE_DIR, -100.0f, -100.0f, "blinky", normalBlinky);
    pinky = CreateGhost(RESOURCE_DIR, 100.0f, -100.0f, "pinky", normalPinky);
    inky = CreateGhost(RESOURCE_DIR, -100.0f, 100.0f, "inky", normalInky);
    clyde = CreateGhost(RESOURCE_DIR, 100.0f, 100.0f, "clyde", normalClyde);
    root.AddChild(blinky);
    root.AddChild(pinky);
    root.AddChild(inky);
    root.AddChild(clyde);

    pacman = std::make_shared<Pacman>();
    pacman->SetUpImages({RESOURCE_DIR"/Image/Character/pacman/pacman_U_01.png", RESOURCE_DIR"/Image/Character/pacman/pacman_U_02.png"});
    pacman->SetDownImages({RESOURCE_DIR"/Image/Character/pacman/pacman_D_01.png", RESOURCE_DIR"/Image/Character/pacman/pacman_D_02.png"});
    pacman->SetRightImages({RESOURCE_DIR"/Image/Character/pacman/pacman_R_01.png", RESOURCE_DIR"/Image/Character/pacman/pacman_R_02.png"});
    pacman->SetLeftImages({RESOURCE_DIR"/Image/Character/pacman/pacman_L_01.png", RESOURCE_DIR"/Image/Character/pacman/pacman_L_02.png"});

    pacman->SetDrawble2();
    pacman->SetZIndex(5);
    pacman->SetVisible(true);
    pacman->SetPosition({0.0f, 0.0f});
    
    root.AddChild(pacman);

    std::vector<std::string> deadImages;
    deadImages.reserve(13);
    for (int i = 0; i < 13; ++i) {
        deadImages.emplace_back(
                RESOURCE_DIR"/Image/Character/Pacman_dead/Pacman_dead" + std::to_string(i + 1) + ".png");
    }

    pacman_dead = std::make_shared<PacmanDead>(deadImages);
    pacman_dead->SetZIndex(5);
    pacman_dead->SetVisible(true);
    pacman_dead->SetPosition({0.0f, -100.0f});
    pacman->AddChild(pacman_dead);

    cherry = std::make_shared<Fruit>(RESOURCE_DIR"/Image/Character/Fruit/cherry.png");
    cherry->SetPosition({0.0f, 100.0f});
    cherry->SetZIndex(1);
    root.AddChild(cherry);

    m_CurrentState = State::UPDATE;
}
