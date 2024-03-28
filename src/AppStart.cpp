#include "App.hpp"

#include "Util/Input.hpp"
#include "Util/Logger.hpp"

void App::Start() {
    LOG_TRACE("Start");

    int m = 28;
    int n = 32;

    std::vector<std::vector<int>> map_by_number(n, std::vector<int>(m, 0));
    std::vector<int> data = {
            5, 1, 1, 1, 1, 1, 1, 1, 1, 14, 13, 1, 1, 1, 1, 14, 13, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 6,
            3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 11, 12, 0, 0, 0, 0, 11, 12, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4,
            3, 0, 13, 9, 9, 14, 0, 13, 14, 0, 11, 12, 0, 13, 14, 0, 11, 12, 0, 13, 14, 0, 13, 9, 9, 14, 0, 4,
            3, 0, 15, 10, 10, 16, 0, 11, 12, 0, 15, 16, 0, 11, 12, 0, 15, 16, 0, 11, 12, 0, 15, 10, 10, 16, 0, 4,
            3, 0, 0, 0, 0, 0, 0, 11, 12, 0, 0, 0, 0, 11, 12, 0, 0, 0, 0, 11, 12, 0, 0, 0, 0, 0, 0, 4,
            3, 0, 13, 9, 9, 14, 0, 11, 14, 9, 9, 14, 0, 11, 12, 0, 13, 9, 9, 13, 12, 0, 13, 9, 9, 14, 0, 4,
            3, 0, 11, 13, 10, 16, 0, 15, 10, 10, 10, 16, 0, 11, 12, 0, 15, 10, 10, 10, 16, 0, 15, 10, 14, 12, 0, 4,
            3, 0, 11, 12, 0, 0, 0, 0, 0, 0, 0, 0, 0, 11, 12, 0, 0, 0, 0, 0, 0, 0, 0, 0, 11, 12, 0, 4,
            3, 0, 11, 12, 0, 13, 9, 9, 14, 0, 13, 9, 9, 16, 15, 9, 9, 14, 0, 13, 9, 9, 14, 0, 11, 12, 0, 4,
            3, 0, 15, 16, 0, 15, 10, 10, 16, 0, 15, 10, 10, 10, 10, 10, 10, 16, 0, 15, 10, 10, 16, 0, 15, 16, 0, 4,
            3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4,
            3, 0, 13, 9, 9, 14, 0, 13, 14, 0, 24, 20, 17, 19, 19, 18, 20, 25, 0, 13, 14, 0, 13, 9, 9, 14, 0, 4,
            3, 0, 11, 0, 0, 12, 0, 11, 12, 0, 22, 0, 0, 0, 0, 0, 0, 23, 0, 11, 12, 0, 11, 0, 0, 12, 0, 4,
            3, 0, 15, 10, 10, 16, 0, 11, 12, 0, 22, 0, 0, 0, 0, 0, 0, 23, 0, 11, 12, 0, 15, 10, 10, 16, 0, 4,
            3, 0, 0, 0, 0, 0, 0, 11, 12, 0, 22, 0, 0, 0, 0, 0, 0, 23, 0, 11, 12, 0, 0, 0, 0, 0, 0, 4,
            3, 0, 13, 9, 9, 14, 0, 11, 12, 0, 26, 21, 21, 21, 21, 21, 21, 27, 0, 11, 12, 0, 13, 9, 9, 14, 0, 4,
            3, 0, 15, 10, 14, 12, 0, 11, 12, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 11, 12, 0, 11, 13, 10, 16, 0, 4,
            3, 0, 0, 0, 11, 12, 0, 11, 12, 0, 13, 9, 9, 9, 9, 9, 9, 14, 0, 11, 12, 0, 11, 12, 0, 0, 0, 4,
            3, 9, 14, 0, 11, 12, 0, 15, 16, 0, 15, 10, 10, 14, 13, 10, 10, 16, 0, 15, 16, 0, 11, 12, 0, 13, 9, 4,
            3, 10, 16, 0, 11, 12, 0, 0, 0, 0, 0, 0, 0, 11, 12, 0, 0, 0, 0, 0, 0, 0, 11, 12, 0, 15, 10, 4,
            3, 0, 0, 0, 11, 12, 0, 13, 9, 9, 9, 14, 0, 11, 12, 0, 13, 9, 9, 9, 14, 0, 11, 12, 0, 0, 0, 4,
            3, 0, 13, 9, 16, 12, 0, 11, 13, 10, 10, 16, 0, 15, 16, 0, 15, 10, 10, 14, 12, 0, 11, 15, 9, 14, 0, 4,
            3, 0, 15, 10, 10, 16, 0, 11, 12, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 11, 12, 0, 15, 10, 10, 16, 0, 4,
            3, 0, 0, 0, 0, 0, 0, 11, 12, 0, 13, 14, 0, 13, 14, 0, 13, 14, 0, 11, 12, 0, 0, 0, 0, 0, 0, 4,
            3, 0, 13, 14, 0, 13, 9, 16, 12, 0, 11, 12, 0, 11, 12, 0, 11, 12, 0, 11, 15, 9, 14, 0, 13, 14, 0, 4,
            3, 0, 11, 12, 0, 15, 10, 10, 16, 0, 11, 12, 0, 15, 16, 0, 11, 12, 0, 15, 10, 10, 16, 0, 11, 12, 0, 4,
            3, 0, 11, 12, 0, 0, 0, 0, 0, 0, 11, 12, 0, 0, 0, 0, 11, 12, 0, 0, 0, 0, 0, 0, 11, 12, 0, 4,
            3, 0, 11, 13, 9, 9, 9, 9, 14, 0, 11, 15, 9, 9, 9, 9, 16, 12, 0, 13, 9, 9, 9, 9, 16, 12, 0, 4,
            3, 0, 15, 10, 10, 10, 10, 10, 16, 0, 15, 10, 10, 10, 10, 10, 10, 16, 0, 15, 10, 10, 10, 10, 10, 16, 0, 4,
            3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4,
            7, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 8
    };

    // 将数据复制到matrix中
    int row = 0, col = 0;
    for (int num: data) {
        map_by_number[row][col] = num;
        std::cout << map_by_number[row][col] << " ";
        col++;
        if (col == 28) {
            col = 0;
            row++;
            std::cout << std::endl;
        }
    }

    m_Map = std::make_shared<Map>(m, n, map_by_number);
    m_Root.AddChild(m_Map);

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
    pacman->SetUpImages({RESOURCE_DIR"/Image/Character/pacman/pacman_U_01.png", RESOURCE_DIR"/Image/Character/pacman/pacman_U_02.png"});
    pacman->SetDownImages({RESOURCE_DIR"/Image/Character/pacman/pacman_D_01.png", RESOURCE_DIR"/Image/Character/pacman/pacman_D_02.png"});
    pacman->SetRightImages({RESOURCE_DIR"/Image/Character/pacman/pacman_R_01.png", RESOURCE_DIR"/Image/Character/pacman/pacman_R_02.png"});
    pacman->SetLeftImages({RESOURCE_DIR"/Image/Character/pacman/pacman_L_01.png", RESOURCE_DIR"/Image/Character/pacman/pacman_L_02.png"});
    pacman->SetDeadImages(deadImages);

    pacman->SetZIndex(5);
    pacman->SetVisible(true);
    pacman->SetPosition({0.0f, 0.0f});
    pacman->Start();
    root.AddChild(pacman);

    cherry = std::make_shared<Fruit>(RESOURCE_DIR"/Image/Character/Fruit/cherry.png");
    cherry->SetPosition({0.0f, 100.0f});
    cherry->SetZIndex(1);
    root.AddChild(cherry);

    m_CurrentState = State::UPDATE;
}
