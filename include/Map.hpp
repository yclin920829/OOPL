#ifndef MAP_HPP
#define MAP_HPP

#include <vector>
#include <map>

#include "Util/GameObject.hpp"
#include "Block.hpp"

class Map : public Util::GameObject {
public:
    explicit Map(const int m, const int n, std::vector<std::vector<int>> map_by_number) {
        double x_transfer = (pixel / 2) * m;
        double y_transfer = (pixel / 2) * n;
        std::vector<int> row;

        for (int i = 0; i < n; ++i) {
            row.clear();
            for (int j = 0; j < m; ++j) {
                double positionX = (j * pixel) - x_transfer;
                double positionY = ((n - i + 1) * pixel) - y_transfer;

                std::shared_ptr<Block> block = std::make_shared<Block>(
                    this->Mapper.at(map_by_number[i][j]),
                    map_by_number[i][j],
                    i, j
                );
                block->SetPosition({positionX, positionY});
                std::cout << block->GetPosition().x << block->GetPosition().y << "(" << block->GetCodeNumber() << ")" << " ";
                this->AddChild(block);

                if (0 == map_by_number[i][j]) {
                    smallBeans.push_back(block);
                    pacmanRoads.push_back(block);
                    ghostRoads.push_back(block);
                    row.push_back(1);
                } else if (43 == map_by_number[i][j]) {
                    largeBeans.push_back(block);
                    pacmanRoads.push_back(block);
                    ghostRoads.push_back(block);
                    row.push_back(1);
                } else if (42 == map_by_number[i][j]) {
                    pacmanRoads.push_back(block);
                    ghostRoads.push_back(block);
                    row.push_back(1);
                }else if (19 == map_by_number[i][j] || 41 == map_by_number[i][j]){
                    ghostRoads.push_back(block);
                    row.push_back(1);
                }else{
                    row.push_back(0);
                }

            }
            std::cout << "\n";
            ghostMap.push_back(row);
        }
        printAAA();
    }

    bool printAAA(){
        for(int i = 0; i < 28; i++){
            std::cout << i << " ";
        }
        std::cout << "\n";
        int i = 0;
        for (std::vector<int> row : ghostMap){
            std::cout << i << ": ";
            for(int road : row){
                std::cout << road << " ";
            }
            i++;
            std::cout << "\n";
        }
    }

    bool IsPacmanRoad(const glm::vec2 &Position) {
        auto it = find_if(pacmanRoads.begin(), pacmanRoads.end(),
                          [&Position](const std::shared_ptr<Block> &obj) {
                              return (obj->GetPosition() == Position);
                          });

        if (it != pacmanRoads.end()) return true;
        return false;
    }

    bool IsGhostRoad(const glm::vec2 &Position) {
        auto it = find_if(ghostRoads.begin(), ghostRoads.end(),
                          [&Position](const std::shared_ptr<Block> &obj) {
                              return (obj->GetPosition() == Position);
                          });

        if (it != ghostRoads.end()) return true;
        return false;
    }

    glm::vec2 changeToPositionInVector(const glm::vec2 &Position) {
        std::shared_ptr<Block> block;
        auto it = find_if(ghostRoads.begin(), ghostRoads.end(),
                          [&Position, &block](const std::shared_ptr<Block> &obj) {
                                block = obj;
                              return (obj->GetPosition() == Position);
                          });

        if (it != ghostRoads.end()) {
            return block->getPositionInVector();
        }else{
            LOG_DEBUG("not fund");
        }
    }

    std::vector<std::vector<int>> GetGhostMap() {
        return ghostMap;
    }

    [[nodiscard]] const std::vector<std::shared_ptr<Block>> &GetSmallBeans() const {
        return smallBeans;
    }

    [[nodiscard]] const std::vector<std::shared_ptr<Block>> &GetLargeBeans() const {
        return largeBeans;
    }

    [[nodiscard]] const std::vector<std::shared_ptr<Block>> &GetGhostRoad() const {
        return ghostRoads;
    }

private:
    double pixel = 16;
    std::vector<std::shared_ptr<Block>> ghostRoads;
    std::vector<std::shared_ptr<Block>> pacmanRoads;
    std::vector<std::shared_ptr<Block>> smallBeans;
    std::vector<std::shared_ptr<Block>> largeBeans;

    std::vector<std::vector<int>> ghostMap;

    std::map<int, std::string> Mapper{
        {0,  "small_ball"},
        {1,  "upper_border"},
        {2,  "lower_border"},
        {3,  "left_border"},
        {4,  "right_border"},
        {5,  "upper_left_border"},
        {6,  "upper_right_border"},
        {7,  "lower_left_border"},
        {8,  "lower_right_border"},
        {9,  "upper_side"},
        {10, "lower_side"},
        {11, "left_side"},
        {12, "right_side"},
        {13, "upper_left_side"},
        {14, "upper_right_side"},
        {15, "lower_left_side"},
        {16, "lower_right_side"},
        {17, "left_respawn_gate"},
        {18, "right_respawn_gate"},
        {19, "respawn_gate"},
        {20, "upper_respawn"},
        {21, "lower_respawn"},
        {22, "left_respawn"},
        {23, "right_respawn"},
        {24, "upper_left_respawn"},
        {25, "upper_right_respawn"},
        {26, "lower_left_respawn"},
        {27, "lower_right_respawn"},
        {28, "innerupper_upper_right_border"},
        {29, "innerupper_upper_left_border"},
        {30, "innerlower_lower_right_border"},
        {31, "innerlower_lower_left_border"},
        {32, "innerright_upper_right_border"},
        {33, "innerright_lower_right_border"},
        {34, "innerleft_upper_left_border"},
        {35, "innerleft_lower_left_border"},
        {36, "trans_upper_right_side"},
        {37, "trans_upper_left_side"},
        {38, "trans_lower_right_side"},
        {39, "trans_lower_left_side"},
        {40, "in_game_blue"},
        {41, "in_respawn_black"},
        {42, "in_game_black"},
        {43, "large_ball"}
    };
};

#endif //MAP_HPP