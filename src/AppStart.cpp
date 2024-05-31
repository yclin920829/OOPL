#include "App.hpp"

#include "Util/Input.hpp"
#include "Util/Logger.hpp"

void App::Start() {
    //LOG_TRACE("Start");
    
    //levelManager ->ConstructLevel(nowLevel);

    int x_block_num = 28;
    int y_block_num = 31;

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

    /*std::vector<std::vector<int>> map_by_number_2(y_block_num, std::vector<int>(x_block_num));

    map_by_number_2 = {
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
            {48,  0,  0,  0,  0,  0,  0,  42, 42, 42, 42, 42, 42, 42, 42, 42, 42, 42, 42, 42, 42, 0,  0,  0,  0,  0,  0,  50},
            {52,  0,  13, 9,  9,  14, 0,  13, 14, 42, 24, 20, 17, 19, 19, 18, 20, 25, 42, 13, 14, 0,  13, 9,  9,  14, 0,  52},
            {49,  0,  11, 40, 40, 12, 0,  11, 12, 42, 22, 41, 41, 41, 41, 41, 41, 23, 42, 11, 12, 0,  11, 40, 40, 12, 0,  51},
            {3,  0,  15, 10, 10, 16, 0,  11, 12, 42, 22, 41, 41, 41, 41, 41, 41, 23, 42, 11, 12, 0,  15, 10, 10, 16, 0,  4},
            {3,  0,  0,  0,  0,  0,  0,  11, 12, 42, 22, 41, 41, 41, 41, 41, 41, 23, 42, 11, 12, 0,  0,  0,  0,  0,  0,  4},
            {3,  0,  13, 9,  9,  14, 0,  11, 12, 42, 26, 21, 21, 21, 21, 21, 21, 27, 42, 11, 12, 0,  13, 9,  9,  14, 0,  4},
            {3,  0,  15, 10, 36, 12, 0,  11, 12, 42, 42, 42, 42, 42, 42, 42, 42, 42, 42, 11, 12, 0,  11, 37, 10, 16, 0,  4},
            {3,  0,  0,  0,  11, 12, 0,  11, 12, 42, 13, 9,  9,  9,  9,  9,  9,  14, 42, 11, 12, 0,  11, 12, 0,  0,  0,  4},
            {35, 9,  14, 0,  11, 12, 0,  15, 16, 42, 15, 10, 10, 36, 37, 10, 10, 16, 42, 15, 16, 0,  11, 12, 0,  13, 9,  33},
            {10, 10, 16, 0,  11, 12, 0,  0,  0,  0,  0,  0,  0,  11, 12, 0,  0,  0,  0,  0,  0,  0,  11, 12, 0,  15, 10, 10},
            {52,  0,  0,  0,  11, 12, 0,  13, 9,  9,  9,  14, 0,  11, 12, 0,  13, 9,  9,  9,  14, 0,  11, 12, 0,  0,  0,  52},
            {49,  0,  13, 9,  38, 12, 0,  11, 37, 10, 10, 16, 0,  15, 16, 0,  15, 10, 10, 36, 12, 0,  11, 39, 9,  14, 0,  51},
            {3,  0,  15, 10, 10, 16, 0,  11, 12, 0,  0,  0,  0,  42, 0,  0,  0,  0,  0,  11, 12, 0,  15, 10, 10, 16, 0,  4},
            {3,  0,  0,  0,  0,  0,  0,  11, 12, 0,  13, 14, 0,  13, 14, 0,  13, 14, 0,  11, 12, 0,  0,  0,  0,  0,  0,  4},
            {3,  0,  13, 14, 0,  13, 9,  38, 12, 0,  11, 12, 0,  11, 12, 0,  11, 12, 0,  11, 39, 9,  14, 0,  13, 14, 0,  4},
            {3,  0,  11, 12, 0,  15, 10, 10, 16, 0,  11, 12, 0,  15, 16, 0,  11, 12, 0,  15, 10, 10, 16, 0,  11, 12, 0,  4},
            {3,  0,  11, 12, 43, 0,  0,  0,  0,  0,  11, 12, 0,  0,  0,  0,  11, 12, 0,  0,  0,  0,  0,  43, 11, 12, 0,  4},
            {3,  0,  11, 39, 9,  9,  9,  9,  14, 0,  11, 39, 9,  9,  9,  9,  38, 12, 0,  13, 9,  9,  9,  9,  38, 12, 0,  4},
            {3,  0,  15, 10, 10, 10, 10, 10, 16, 0,  15, 10, 10, 10, 10, 10, 10, 16, 0,  15, 10, 10, 10, 10, 10, 16, 0,  4},
            {3,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  4},
            {7,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  8}
    };*/

    map = std::make_shared<Map>(x_block_num, y_block_num, map_by_number);
    root.AddChild(map);

    lifeSystem = std::make_shared<LifeSystem>(eventManager);
    lifeSystem->SetSystemPosition({-224, -216});
    lifeSystem->InitialLifeSystem();
    root.AddChild(lifeSystem);

    //初始化scoreSystem
    scoreSystem = std::make_shared<ScoreSystem>(eventManager);
    scoreSystem->SetNowXY(-224, 208, 264);
    scoreSystem->InitialScoreSystem();
    root.AddChild(scoreSystem);

    fruitSystem = std::make_shared<FruitSystem>();
    fruitSystem->SetSystemPosition({240, -216});
    root.AddChild(fruitSystem);


    VulnerableGhostsImages = {
        RESOURCE_DIR"/Image/Character/VulnerableGhosts/VulnerableGhosts_B_01.png",
        RESOURCE_DIR"/Image/Character/VulnerableGhosts/VulnerableGhosts_B_02.png",
        RESOURCE_DIR"/Image/Character/VulnerableGhosts/VulnerableGhosts_W_01.png",
        RESOURCE_DIR"/Image/Character/VulnerableGhosts/VulnerableGhosts_W_02.png"
    };

    blinky = std::make_shared<Ghost>("blinky", map->GetGhostMap());
    pinky = std::make_shared<Ghost>("pinky", map->GetGhostMap());
    inky = std::make_shared<Ghost>("inky", map->GetGhostMap());
    clyde = std::make_shared<Ghost>("clyde", map->GetGhostMap());
    blinky->SetPosition({-0.0, 104});
    pinky->SetPosition({-40.0, 56});
    inky->SetPosition({-16.0, 56});
    clyde->SetPosition({16.0, 56});
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


    
    blinky->SetTargetPosition(map->changeToPositionInVector({-208, 248}));
    blinky->shortestPath(
        map->changeToPositionInVector(blinky->GetPosition())
    );


    pinky->SetPosition({-32, 56});
    pinky->SetTargetPosition(map->changeToPositionInVector({192, 248}));
    pinky->shortestPath(
        map->changeToPositionInVector(pinky->GetPosition())
    );

    inky->SetTargetPosition(map->changeToPositionInVector({-208, -200}));
    inky->shortestPath(
        map->changeToPositionInVector(inky->GetPosition())
    );

    clyde->SetTargetPosition(map->changeToPositionInVector({192, -200}));
    clyde->shortestPath(
        map->changeToPositionInVector(clyde->GetPosition())
    );

    //m_CurrentState = State::UI;
    m_CurrentState = State::UPDATE;
}
