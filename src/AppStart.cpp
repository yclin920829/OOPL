#include "App.hpp"

#include "Util/Input.hpp"
#include "Util/Logger.hpp"

void App::Start() {
    LOG_TRACE("Start");

    int x_block_num = 28;
    int y_block_num = 31;

    std::vector<std::vector<int>> map_by_number(y_block_num, std::vector<int>(x_block_num));

    map_by_number = {
        {5,  1,  1,  1,  1,  1,  1,  1,  1,  1,  28, 29, 1,  1,  1,  1,  28, 29, 1,  1,  1,  1,  1,  1,  1,  1,  1,  6},
        {3,  0,  0,  0,  0,  0,  0,  0,  0,  0,  11, 12, 0,  0,  0,  0,  11, 12, 0,  0,  0,  0,  0,  0,  0,  0,  0,  4},
        {3,  0,  13, 9,  9,  14, 0,  13, 14, 0,  11, 12, 0,  13, 14, 0,  11, 12, 0,  13, 14, 0,  13, 9,  9,  14, 0,  4},
        {3,  0,  15, 10, 10, 16, 0,  11, 12, 0,  15, 16, 0,  11, 12, 0,  15, 16, 0,  11, 12, 0,  15, 10, 10, 16, 0,  4},
        {3,  0,  0,  0,  0,  0,  0,  11, 12, 0,  0,  0,  0,  11, 12, 0,  0,  0,  0,  11, 12, 0,  0,  0,  0,  0,  0,  4},
        {3,  0,  13, 9,  9,  14, 0,  11, 39, 9,  9,  14, 0,  11, 12, 0,  13, 9,  9,  38, 12, 0,  13, 9,  9,  14, 0,  4},
        {3,  0,  11, 37, 10, 16, 0,  15, 10, 10, 10, 16, 0,  11, 12, 0,  15, 10, 10, 10, 16, 0,  15, 10, 36, 12, 0,  4},
        {3,  0,  11, 12, 0,  0,  0,  0,  0,  0,  0,  0,  0,  11, 12, 0,  0,  0,  0,  0,  0,  0,  0,  0,  11, 12, 0,  4},
        {3,  0,  11, 12, 0,  13, 9,  9,  14, 0,  13, 9,  9,  38, 39, 9,  9,  14, 0,  13, 9,  9,  14, 0,  11, 12, 0,  4},
        {3,  0,  15, 16, 0,  15, 10, 10, 16, 0,  15, 10, 10, 10, 10, 10, 10, 16, 0,  15, 10, 10, 16, 0,  15, 16, 0,  4},
        {3,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  4},
        {3,  0,  13, 9,  9,  14, 0,  13, 14, 0,  24, 20, 17, 19, 19, 18, 20, 25, 0,  13, 14, 0,  13, 9,  9,  14, 0,  4},
        {3,  0,  11, 40, 40, 12, 0,  11, 12, 0,  22, 0,  0,  0,  0,  0,  0,  23, 0,  11, 12, 0,  11, 40, 40, 12, 0,  4},
        {3,  0,  15, 10, 10, 16, 0,  11, 12, 0,  22, 0,  0,  0,  0,  0,  0,  23, 0,  11, 12, 0,  15, 10, 10, 16, 0,  4},
        {3,  0,  0,  0,  0,  0,  0,  11, 12, 0,  22, 0,  0,  0,  0,  0,  0,  23, 0,  11, 12, 0,  0,  0,  0,  0,  0,  4},
        {3,  0,  13, 9,  9,  14, 0,  11, 12, 0,  26, 21, 21, 21, 21, 21, 21, 27, 0,  11, 12, 0,  13, 9,  9,  14, 0,  4},
        {3,  0,  15, 10, 36, 12, 0,  11, 12, 0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  11, 12, 0,  11, 37, 10, 16, 0,  4},
        {3,  0,  0,  0,  11, 12, 0,  11, 12, 0,  13, 9,  9,  9,  9,  9,  9,  14, 0,  11, 12, 0,  11, 12, 0,  0,  0,  4},
        {35, 9,  14, 0,  11, 12, 0,  15, 16, 0,  15, 10, 10, 36, 37, 10, 10, 16, 0,  15, 16, 0,  11, 12, 0,  13, 9,  33},
        {34, 10, 16, 0,  11, 12, 0,  0,  0,  0,  0,  0,  0,  11, 12, 0,  0,  0,  0,  0,  0,  0,  11, 12, 0,  15, 10, 32},
        {3,  0,  0,  0,  11, 12, 0,  13, 9,  9,  9,  14, 0,  11, 12, 0,  13, 9,  9,  9,  14, 0,  11, 12, 0,  0,  0,  4},
        {3,  0,  13, 9,  38, 12, 0,  11, 37, 10, 10, 16, 0,  15, 16, 0,  15, 10, 10, 36, 12, 0,  11, 39, 9,  14, 0,  4},
        {3,  0,  15, 10, 10, 16, 0,  11, 12, 0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  11, 12, 0,  15, 10, 10, 16, 0,  4},
        {3,  0,  0,  0,  0,  0,  0,  11, 12, 0,  13, 14, 0,  13, 14, 0,  13, 14, 0,  11, 12, 0,  0,  0,  0,  0,  0,  4},
        {3,  0,  13, 14, 0,  13, 9,  38, 12, 0,  11, 12, 0,  11, 12, 0,  11, 12, 0,  11, 39, 9,  14, 0,  13, 14, 0,  4},
        {3,  0,  11, 12, 0,  15, 10, 10, 16, 0,  11, 12, 0,  15, 16, 0,  11, 12, 0,  15, 10, 10, 16, 0,  11, 12, 0,  4},
        {3,  0,  11, 12, 0,  0,  0,  0,  0,  0,  11, 12, 0,  0,  0,  0,  11, 12, 0,  0,  0,  0,  0,  0,  11, 12, 0,  4},
        {3,  0,  11, 39, 9,  9,  9,  9,  14, 0,  11, 39, 9,  9,  9,  9,  38, 12, 0,  13, 9,  9,  9,  9,  38, 12, 0,  4},
        {3,  0,  15, 10, 10, 10, 10, 10, 16, 0,  15, 10, 10, 10, 10, 10, 10, 16, 0,  15, 10, 10, 10, 10, 10, 16, 0,  4},
        {3,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  4},
        {7,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  8}
    };
    map = std::make_shared<Map>(x_block_num, y_block_num, map_by_number);
    root.AddChild(map);

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

    std::vector<std::string> deadImages;
    deadImages.reserve(13);
    for (int i = 0; i < 13; ++i) {
        deadImages.emplace_back(
            RESOURCE_DIR"/Image/Character/Pacman_dead/Pacman_dead" + std::to_string(i + 1) + ".png");
    }

    pacman = std::make_shared<Pacman>();
    pacman->SetUpImages(
        {RESOURCE_DIR"/Image/Character/pacman/pacman_U_01.png", RESOURCE_DIR"/Image/Character/pacman/pacman_U_02.png"});
    pacman->SetDownImages(
        {RESOURCE_DIR"/Image/Character/pacman/pacman_D_01.png", RESOURCE_DIR"/Image/Character/pacman/pacman_D_02.png"});
    pacman->SetRightImages(
        {RESOURCE_DIR"/Image/Character/pacman/pacman_R_01.png", RESOURCE_DIR"/Image/Character/pacman/pacman_R_02.png"});
    pacman->SetLeftImages(
        {RESOURCE_DIR"/Image/Character/pacman/pacman_L_01.png", RESOURCE_DIR"/Image/Character/pacman/pacman_L_02.png"});
    pacman->SetDeadImages(deadImages);

    pacman->SetZIndex(5);
    pacman->SetVisible(true);
    pacman->SetPosition({-0.0f, -88.0f});
    pacman->Start();
    root.AddChild(pacman);

    cherry = std::make_shared<Fruit>(RESOURCE_DIR"/Image/Character/Fruit/cherry.png");
    cherry->SetPosition({0.0f, 100.0f});
    cherry->SetZIndex(1);
    cherry->SetVisible(false);
    root.AddChild(cherry);

    m_CurrentState = State::UPDATE;
}
