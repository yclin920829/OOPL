#include "App.hpp"

#include "Util/Input.hpp"
#include "Util/Logger.hpp"

void App::Start() {
    LOG_TRACE("Start");

    int x_block_num = 28;
    int y_block_num = 31;

    xMap = x_block_num;
    yMap = y_block_num;

    std::vector<std::vector<int>> map_by_number(y_block_num, std::vector<int>(x_block_num));

    map_by_number = {
        {5,  1,  1,  1,  1,  1,  1,  1,  1,  1,  28, 29, 1,  1,  1,  1,  28, 29, 1,  1,  1,  1,  1,  1,  1,  1,  1,  6},
        {3,  43, 0,  0,  0,  0,  0,  0,  0,  0,  11, 12, 0,  0,  0,  0,  11, 12, 0,  0,  0,  0,  0,  0,  0,  0,  43, 4},
        {3,  0,  13, 9,  9,  14, 0,  13, 14, 0,  11, 12, 0,  13, 14, 0,  11, 12, 0,  13, 14, 0,  13, 9,  9,  14, 0,  4},
        {3,  0,  15, 10, 10, 16, 0,  11, 12, 0,  15, 16, 0,  11, 12, 0,  15, 16, 0,  11, 12, 0,  15, 10, 10, 16, 0,  4},
        {3,  0,  0,  0,  0,  0,  0,  11, 12, 0,  0,  0,  0,  11, 12, 0,  0,  0,  0,  11, 12, 0,  0,  0,  0,  0,  0,  4},
        {3,  0,  13, 9,  9,  14, 0,  11, 39, 9,  9,  14, 0,  11, 12, 0,  13, 9,  9,  38, 12, 0,  13, 9,  9,  14, 0,  4},
        {3,  0,  11, 37, 10, 16, 0,  15, 10, 10, 10, 16, 0,  11, 12, 0,  15, 10, 10, 10, 16, 0,  15, 10, 36, 12, 0,  4},
        {3,  0,  11, 12, 0,  0,  0,  0,  0,  0,  0,  0,  0,  11, 12, 0,  0,  0,  0,  0,  0,  0,  0,  0,  11, 12, 0,  4},
        {3,  0,  11, 12, 0,  13, 9,  9,  14, 42, 13, 9,  9,  38, 39, 9,  9,  14, 42, 13, 9,  9,  14, 0,  11, 12, 0,  4},
        {3,  0,  15, 16, 0,  15, 10, 10, 16, 42, 15, 10, 10, 10, 10, 10, 10, 16, 42, 15, 10, 10, 16, 0,  15, 16, 0,  4},
        {3,  0,  0,  0,  0,  0,  0,  42, 42, 42, 42, 42, 42, 42, 42, 42, 42, 42, 42, 42, 42, 0,  0,  0,  0,  0,  0,  4},
        {3,  0,  13, 9,  9,  14, 0,  13, 14, 42, 24, 20, 17, 19, 19, 18, 20, 25, 42, 13, 14, 0,  13, 9,  9,  14, 0,  4},
        {3,  0,  11, 40, 40, 12, 0,  11, 12, 42, 22, 41, 41, 41, 41, 41, 41, 23, 42, 11, 12, 0,  11, 40, 40, 12, 0,  4},
        {3,  0,  15, 10, 10, 16, 0,  11, 12, 42, 22, 41, 41, 41, 41, 41, 41, 23, 42, 11, 12, 0,  15, 10, 10, 16, 0,  4},
        {3,  0,  0,  0,  0,  0,  0,  11, 12, 42, 22, 41, 41, 41, 41, 41, 41, 23, 42, 11, 12, 0,  0,  0,  0,  0,  0,  4},
        {3,  0,  13, 9,  9,  14, 0,  11, 12, 42, 26, 21, 21, 21, 21, 21, 21, 27, 42, 11, 12, 0,  13, 9,  9,  14, 0,  4},
        {3,  0,  15, 10, 36, 12, 0,  11, 12, 42, 42, 42, 42, 42, 42, 42, 42, 42, 42, 11, 12, 0,  11, 37, 10, 16, 0,  4},
        {3,  0,  0,  0,  11, 12, 0,  11, 12, 42, 13, 9,  9,  9,  9,  9,  9,  14, 42, 11, 12, 0,  11, 12, 0,  0,  0,  4},
        {35, 9,  14, 0,  11, 12, 0,  15, 16, 42, 15, 10, 10, 36, 37, 10, 10, 16, 42, 15, 16, 0,  11, 12, 0,  13, 9,  33},
        {34, 10, 16, 0,  11, 12, 0,  0,  0,  0,  0,  0,  0,  11, 12, 0,  0,  0,  0,  0,  0,  0,  11, 12, 0,  15, 10, 32},
        {3,  0,  0,  0,  11, 12, 0,  13, 9,  9,  9,  14, 0,  11, 12, 0,  13, 9,  9,  9,  14, 0,  11, 12, 0,  0,  0,  4},
        {3,  0,  13, 9,  38, 12, 0,  11, 37, 10, 10, 16, 0,  15, 16, 0,  15, 10, 10, 36, 12, 0,  11, 39, 9,  14, 0,  4},
        {3,  0,  15, 10, 10, 16, 0,  11, 12, 0,  0,  0,  0,  42, 0,  0,  0,  0,  0,  11, 12, 0,  15, 10, 10, 16, 0,  4},
        {3,  0,  0,  0,  0,  0,  0,  11, 12, 0,  13, 14, 0,  13, 14, 0,  13, 14, 0,  11, 12, 0,  0,  0,  0,  0,  0,  4},
        {3,  0,  13, 14, 0,  13, 9,  38, 12, 0,  11, 12, 0,  11, 12, 0,  11, 12, 0,  11, 39, 9,  14, 0,  13, 14, 0,  4},
        {3,  0,  11, 12, 0,  15, 10, 10, 16, 0,  11, 12, 0,  15, 16, 0,  11, 12, 0,  15, 10, 10, 16, 0,  11, 12, 0,  4},
        {3,  0,  11, 12, 43, 0,  0,  0,  0,  0,  11, 12, 0,  0,  0,  0,  11, 12, 0,  0,  0,  0,  0,  43, 11, 12, 0,  4},
        {3,  0,  11, 39, 9,  9,  9,  9,  14, 0,  11, 39, 9,  9,  9,  9,  38, 12, 0,  13, 9,  9,  9,  9,  38, 12, 0,  4},
        {3,  0,  15, 10, 10, 10, 10, 10, 16, 0,  15, 10, 10, 10, 10, 10, 10, 16, 0,  15, 10, 10, 10, 10, 10, 16, 0,  4},
        {3,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  4},
        {7,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  8}
    };

    map = std::make_shared<Map>(x_block_num, y_block_num, map_by_number);
    root.AddChild(map);

    //初始化lifeSystem
    lifeSystem = std::make_shared<LifeSystem>(eventManager);
//    float lifeSysX = map->map_by_number[y_block_num-1][0]->GetPosition().x;
//    float lifeSysY = map->map_by_number[y_block_num-1][0]->GetPosition().y;
//    lifeSystem->SetNowXY(lifeSysX,lifeSysY );
    lifeSystem->SetNowXY(-224, -216);
    root.AddChild(lifeSystem);

    //初始化scoreSystem
    scoreSystem = std::make_shared<ScoreSystem>(eventManager);
//    float scoreSysMinx = map->map_by_number[0][0]->GetPosition().x;
//    float scoreSysMaxx = map->map_by_number[0][x_block_num - 1]->GetPosition().x;
//    float scoreSysMaxy = map->map_by_number[0][0]->GetPosition().y;
//    scoreSystem -> SetNowXY(scoreSysMinx, scoreSysMaxx, scoreSysMaxy);
    scoreSystem->SetNowXY(-224, 208, 264);
    scoreSystem->InitialScoreSystem();
    root.AddChild(scoreSystem);

    //初始化fruitSystem
    fruitSystem = std::make_shared<FruitSystem>();
//    float fruitSysX = map->map_by_number[y_block_num - 1][x_block_num - 1]->GetPosition().x + 32;
//    float fruitSysY = map->map_by_number[y_block_num - 1][x_block_num - 1]->GetPosition().y;
//    glm::vec2 fruitSys;
//    fruitSys.x = fruitSysX;
//    fruitSys.y = fruitSysY;
    fruitSystem->SetPosition({240, -216});
    root.AddChild(fruitSystem);


    VulnerableGhostsImages = {
        RESOURCE_DIR"/Image/Character/VulnerableGhosts/VulnerableGhosts_B_01.png",
        RESOURCE_DIR"/Image/Character/VulnerableGhosts/VulnerableGhosts_B_02.png",
        RESOURCE_DIR"/Image/Character/VulnerableGhosts/VulnerableGhosts_W_01.png",
        RESOURCE_DIR"/Image/Character/VulnerableGhosts/VulnerableGhosts_W_02.png"
    };

    blinky = std::make_shared<Ghost>("blinky");
    pinky = std::make_shared<Ghost>("pinky");
    inky = std::make_shared<Ghost>("inky");
    clyde = std::make_shared<Ghost>("clyde");
    blinky->SetPosition({-0.0, 104});
    pinky->SetPosition({-40.0, 56});
    inky->SetPosition({-8.0, 56});
    clyde->SetPosition({24.0, 56});
    root.AddChild(blinky);
    root.AddChild(pinky);
    root.AddChild(inky);
    root.AddChild(clyde);

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

    /*cherry = std::make_shared<Fruit>(RESOURCE_DIR"/Image/Character/Fruit/cherry.png");
    cherry->SetPosition({0.0f, 100.0f});
    cherry->SetZIndex(1);

    cherry->SetVisible(false);
    root.AddChild(cherry);
    */

    m_CurrentState = State::UPDATE;
}
