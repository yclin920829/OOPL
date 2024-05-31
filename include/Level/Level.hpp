#ifndef REPLACE_WITH_YOUR_PROJECT_NAME_LEVEL_HPP
#define REPLACE_WITH_YOUR_PROJECT_NAME_LEVEL_HPP

#include "Character/Pacman.hpp"
#include "ghost/Ghost.hpp"
#include "life/LifeSystem.hpp"
#include "fruit/FruitSystem.hpp"
#include "score/ScoreSystem.hpp"
#include "map/Map.hpp"

#include "Util/Input.hpp"
#include "Util/Time.hpp"

class Level : public Util::GameObject {
public:
    explicit Level(){

    };

    void Initialized(int nowLevel){//之後加入讀入系統
        if(nowLevel == 0){
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
            this->AddChild(map);

            lifeSystem = std::make_shared<LifeSystem>(eventManager);
            lifeSystem->SetSystemPosition({-224, -216});
            lifeSystem->InitialLifeSystem();
            this->AddChild(lifeSystem);

            //初始化scoreSystem
            scoreSystem = std::make_shared<ScoreSystem>(eventManager);
            scoreSystem->SetNowXY(-224, 208, 264);
            scoreSystem->InitialScoreSystem();
            this->AddChild(scoreSystem);

            fruitSystem = std::make_shared<FruitSystem>();
            fruitSystem->SetSystemPosition({240, -216});
            this->AddChild(fruitSystem);


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
            this->AddChild(blinky);
            this->AddChild(pinky);
            this->AddChild(inky);
            this->AddChild(clyde);

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
            this->AddChild(pacman);



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
        }
        if(nowLevel == 1){
            int x_block_num = 28;
            int y_block_num = 31;

            std::vector<std::vector<int>> map_by_number(y_block_num, std::vector<int>(x_block_num));

            /*map_by_number = {
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
            };*/

            std::vector<std::vector<int>> map_by_number_2(y_block_num, std::vector<int>(x_block_num));

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
            };

            map = std::make_shared<Map>(x_block_num, y_block_num, map_by_number);
            this->AddChild(map);

            lifeSystem = std::make_shared<LifeSystem>(eventManager);
            lifeSystem->SetSystemPosition({-224, -216});
            lifeSystem->InitialLifeSystem();
            this->AddChild(lifeSystem);

            //初始化scoreSystem
            scoreSystem = std::make_shared<ScoreSystem>(eventManager);
            scoreSystem->SetNowXY(-224, 208, 264);
            scoreSystem->InitialScoreSystem();
            this->AddChild(scoreSystem);

            fruitSystem = std::make_shared<FruitSystem>();
            fruitSystem->SetSystemPosition({240, -216});
            this->AddChild(fruitSystem);


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
            this->AddChild(blinky);
            this->AddChild(pinky);
            this->AddChild(inky);
            this->AddChild(clyde);

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
            this->AddChild(pacman);



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
        }
    }

    void Update(){

        if (Util::Input::IsKeyDown(Util::Keycode::UP)) {
            pacman->setNextDirection(Pacman::Direction::up);
        } else if (Util::Input::IsKeyDown(Util::Keycode::DOWN)) {
            pacman->setNextDirection(Pacman::Direction::down);
        } else if (Util::Input::IsKeyDown(Util::Keycode::RIGHT)) {
            pacman->setNextDirection(Pacman::Direction::right);
        } else if (Util::Input::IsKeyDown(Util::Keycode::LEFT)) {
            pacman->setNextDirection(Pacman::Direction::left);
        }

        glm::vec2 oldPosition = pacman->GetPosition();
        switch (pacman->getNextDirection()) {
            case Pacman::Direction::up:
                if (map->IsPacmanRoad({oldPosition.x, oldPosition.y + 16.0f})) {
                    pacman->setCurrentDirection(pacman->getNextDirection());
                }
                break;
            case Pacman::Direction::down:
                if (map->IsPacmanRoad({oldPosition.x, oldPosition.y - 16.0f})) {
                    pacman->setCurrentDirection(pacman->getNextDirection());
                }
                break;
            case Pacman::Direction::right:
                if (map->IsPacmanRoad({oldPosition.x + 16.0f, oldPosition.y})) {
                    pacman->setCurrentDirection(pacman->getNextDirection());
                }
                break;
            case Pacman::Direction::left:
                if (map->IsPacmanRoad({oldPosition.x - 16.0f, oldPosition.y})) {
                    pacman->setCurrentDirection(pacman->getNextDirection());
                }
                break;
            case Pacman::Direction::none:
                break;
        }

        switch (pacman->getCurrentDirection()) {
            case Pacman::Direction::up:
                if (map->IsPacmanRoad({oldPosition.x, oldPosition.y + 16.0f})) {
                    // std::this_thread::sleep_for(std::chrono::milliseconds((125 / 4)));
                    pacman->MoveUp();
                }
                break;
            case Pacman::Direction::down:
                if (map->IsPacmanRoad({oldPosition.x, oldPosition.y - 16.0f})) {
                    // std::this_thread::sleep_for(std::chrono::milliseconds((125 / 4)));
                    pacman->MoveDown();
                }
                break;
            case Pacman::Direction::right:
                if (map->IsPacmanRoad({oldPosition.x + 16.0f, oldPosition.y})) {
                    // std::this_thread::sleep_for(std::chrono::milliseconds((125 / 4)));
                    pacman->MoveRight();
                }
                break;
            case Pacman::Direction::left:
                if (map->IsPacmanRoad({oldPosition.x - 16.0f, oldPosition.y})) {
                    // std::this_thread::sleep_for(std::chrono::milliseconds((125 / 4)));
                    pacman->MoveLeft();
                }
                break;
            case Pacman::Direction::none:
                break;
        }

        for (const std::shared_ptr<Block> &bean: map->GetSmallBeans()) {
            if (pacman->eatBean(bean) && bean->GetVisibility()) {
                bean->SetVisible(false);
                pacman ->HandleScoreUpCollision();
            }
        }

        for (const std::shared_ptr<Block> &bean: map->GetLargeBeans()) {
            if (pacman->eatBean(bean) && bean->GetVisibility()) {
                bean->SetVisible(false);
                pinky->Vulnerable();
                blinky->Vulnerable();
                inky->Vulnerable();
                clyde->Vulnerable();
                pacman ->HandleScoreUpCollision(75);
                time = 0;
            }

        }

        int counter = 0;
        for (const std::shared_ptr<Block> &bean: map->GetSmallBeans()) {
            if(!bean->GetVisibility()){
                counter ++;
            }
        }

        if((counter % (map->GetSmallBeans().size() / 3)) == 0  && counter){
            fruitSystem->getCherry()->SetVisible(true);
        }

        if(pacman->IsCollidesFruit(fruitSystem->getCherry()) && fruitSystem->getCherry()->GetVisibility()){
            fruitSystem->getCherry()->SetVisible(false);
            pacman ->HandleScoreUpCollision(100);
        }

        if (pacman->IsDead() && pacman->IfAnimationEnds()){
            pacman->ReStart();
            pacman->setNextDirection(Pacman::Direction::left);
        }

        if (!pacman->IsDead() && pacman->IfCollidesGhost(blinky)) {
            if (blinky->GetState() == "Normal") {
                pacman->Dead();
            } else if (blinky->GetState() == "Vulnerable") {
                blinky->Dead();
            }
        }

        if (!pacman->IsDead() && pacman->IfCollidesGhost(pinky)) {
            if (pinky->GetState() == "Normal") {
                pacman->Dead();
            } else if (pinky->GetState() == "Vulnerable") {
                pinky->Dead();
            }
        }

        if (!pacman->IsDead() && pacman->IfCollidesGhost(inky)) {
            if (inky->GetState() == "Normal") {
                pacman->Dead();
            } else if (inky->GetState() == "Vulnerable") {
                inky->Dead();
            }
        }

        if (!pacman->IsDead() && pacman->IfCollidesGhost(clyde)) {
            if (clyde->GetState() == "Normal") {
                pacman->Dead();
            } else if (clyde->GetState() == "Vulnerable") {
                clyde->Dead();
            }
        }

        if(blinky->IsArrivePosition()){
            if(blinky->GetState() == "Dead")blinky->ReStart();
            blinky->SetTargetPosition(map->changeToPositionInVector(
//            pacman->GetPosition()
                    map->GetGhostRoad()[rand() % map->GetGhostRoad().size()]->GetPosition()
            ));
            blinky->shortestPath(
                    map->changeToPositionInVector(blinky->GetPosition())
            );
        }

        if(pinky->IsArrivePosition()){
            if(pinky->GetState() == "Dead")pinky->ReStart();
            int num = rand() % map->GetSmallBeans().size();
            while(!map->GetSmallBeans()[num]->GetVisibility()){
                num = rand() % map->GetSmallBeans().size();
            }
            pinky->SetTargetPosition(map->changeToPositionInVector(
                    map->GetSmallBeans()[num]->GetPosition()
            ));
            pinky->shortestPath(
                    map->changeToPositionInVector(pinky->GetPosition())
            );

        }

        if(inky->IsArrivePosition()){
            if(inky->GetState() == "Dead")inky->ReStart();
            inky->SetTargetPosition(map->changeToPositionInVector(
                    map->GetLargeBeans()[rand() % map->GetLargeBeans().size()]->GetPosition()
            ));
            inky->shortestPath(
                    map->changeToPositionInVector(inky->GetPosition())
            );
        }

        if(clyde->IsArrivePosition()){
            if(clyde->GetState() == "Dead")clyde->ReStart();
            clyde->SetTargetPosition(map->changeToPositionInVector(
                    map->GetGhostRoad()[rand() % map->GetGhostRoad().size()]->GetPosition()
            ));
            clyde->shortestPath(
                    map->changeToPositionInVector(clyde->GetPosition())
            );
        }

        if(blinky->GetState() == "Dead"){
            blinky->SetTargetPosition(map->changeToPositionInVector(
                    {-16,56}
            ));
            blinky->shortestPath(
                    map->changeToPositionInVector(blinky->GetPosition())
            );
        }

        if(pinky->GetState() == "Dead"){
            pinky->SetTargetPosition(map->changeToPositionInVector(
                    {-16,56}
            ));
            pinky->shortestPath(
                    map->changeToPositionInVector(pinky->GetPosition())
            );
        }

        if(inky->GetState() == "Dead"){
            inky->SetTargetPosition(map->changeToPositionInVector(
                    {-16,56}
            ));
            inky->shortestPath(
                    map->changeToPositionInVector(inky->GetPosition())
            );
        }

        if(clyde->GetState() == "Dead"){
            clyde->SetTargetPosition(map->changeToPositionInVector(
                    {-16,56}
            ));
            clyde->shortestPath(
                    map->changeToPositionInVector(clyde->GetPosition())
            );
        }

        blinky->move();
        pinky->move();
        inky->move();
        clyde->move();

        time++;
        if(time % (15 * 10) == 0){
            if(blinky->GetState() == "Vulnerable"){
                blinky->ReStart();
            }
            if(pinky->GetState() == "Vulnerable"){
                pinky->ReStart();
            }
            if(inky->GetState() == "Vulnerable"){
                inky->ReStart();
            }
            if(clyde->GetState() == "Vulnerable"){
                clyde->ReStart();
            }
        }

        if(lifeSystem->IsDone()){
            IsBackFromGame = true;
            m_CurrentState = State::END;
        }
    }

private:
    //systems contain object
    std::shared_ptr<Map> map;

    std::shared_ptr<LifeSystem> lifeSystem;
    std::shared_ptr<ScoreSystem> scoreSystem;
    std::shared_ptr<FruitSystem> fruitSystem;
    EventManager * eventManager = new EventManager();

    //roles
    std::shared_ptr<Ghost> blinky;
    std::shared_ptr<Ghost> pinky;
    std::shared_ptr<Ghost> inky;
    std::shared_ptr<Ghost> clyde;

    std::shared_ptr<Pacman> pacman;


    std::vector<std::string> VulnerableGhostsImages;

    int time = 0;

};

#endif //REPLACE_WITH_YOUR_PROJECT_NAME_LEVEL_HPP
