#ifndef MAP_HPP
#define MAP_HPP

#include <map>
#include <vector>
#include <format>
#include <iomanip>

#include "Block.hpp"
#include "Util/GameObject.hpp"

class Map : public Util::GameObject {
public:
    explicit Map(const glm::vec2 size, std::vector<std::vector<int>> map_by_number) {
        double x_transfer = (pixel / 2) * size.x;
        double y_transfer = (pixel / 2) * size.y;
        std::vector<int> row;
        std::vector<std::shared_ptr<Block>> printRow;

        for (int i = 0; i < size.y; ++i) {
            row.clear();
            printRow.clear();
            for (int j = 0; j < size.x; ++j) {
                double positionX = (j * pixel) - x_transfer;
                double positionY = ((size.y - i + 1) * pixel) - y_transfer;

                std::shared_ptr<Block> block;
                if (43 == map_by_number[i][j]) {
                    block = std::make_shared<Block>(
                        std::vector<std::string>{this->Mapper.at(map_by_number[i][j]), "small_ball"},
                        map_by_number[i][j],
                        i, j
                    );
                } else {
                    block = std::make_shared<Block>(
                        this->Mapper.at(map_by_number[i][j]),
                        map_by_number[i][j],
                        i, j
                    );
                }

                block->SetPosition({positionX, positionY});
                this->AddChild(block);

                if (0 == map_by_number[i][j] || 43 == map_by_number[i][j]) { // beans
                    beans.push_back(block);
                    pacmanRoads.push_back(block);
                    ghostRoads.push_back(block);
                    row.push_back(1);
                } else if (42 == map_by_number[i][j]) { // in_game_black
                    pacmanRoads.push_back(block);
                    ghostRoads.push_back(block);
                    row.push_back(1);
                } else if (19 == map_by_number[i][j] || 41 == map_by_number[i][j]) { // respawn
                    ghostRoads.push_back(block);
                    row.push_back(1);
                } else {
                    row.push_back(0);
                }
                printRow.push_back(block);
            }
            ghostMap.push_back(row);
            printMap.push_back(printRow);
        }
    }


    void printMapInformation(){
        LOG_INFO("");
        LOG_INFO("This is map's information:");
        std::ostringstream info;
        info.str("");
        info << "[    ]";
        for(int i = 0; i < printMap[0].size(); i++){
            info << "[                   " << std::setw(2) << i+1 << "                  ]";
            if(i != printMap[0].size()-1){
                info << " / ";
            }
        }
        LOG_INFO("{}", info.str());
        int i = 1;
        for(const std::vector<std::shared_ptr<Block>>& printRow : printMap){
            info.str("");
            info << "[ " << std::setw(2) << i << " ]";
            for(std::shared_ptr<Block> block : printRow){
                info << "{";
                info << "Code number: " << std::setw(2) << block->GetCodeNumber() << ", ";
                info << "Position: [" ;
                info << std::setw(4) << block->GetPosition().x;
                info << ", ";
                info << std::setw(4) << block->GetPosition().y;
                info << "]";
                info << "}";

                if(block != printRow.back()){
                    info << " / ";
                }
            }
            info.clear();
            LOG_INFO("{}", info.str());
            i++;
        }
        LOG_INFO("");
    }

    void printMapInformation(int i, int j) {
        i--;
        j--;
        if (i < 0 || i > printMap[j].size() || j < 0 || j > printMap.size()) {
            LOG_ERROR("Invalid indexes: ({}, {}).", i, j);
            return;
        }

        LOG_INFO("");
        LOG_INFO("Information at indexes ({}, {}):", i, j);
        std::shared_ptr<Block> block = printMap[j][i];

        std::ostringstream info;
        info << "{";
        info << "Code number: " << std::setw(2) << block->GetCodeNumber() << ", ";
        info << "Position: [" ;
        info << std::setw(4) << block->GetPosition().x;
        info << ", ";
        info << std::setw(4) << block->GetPosition().y;
        info << "]";
        info << "}";

        LOG_INFO("{}", info.str());
        LOG_INFO("");
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

    [[nodiscard]] const std::vector<std::shared_ptr<Block>> &GetSmallBeans() const {
        return beans;
    }

    [[nodiscard]] const std::vector<std::shared_ptr<Block>> &GetGhostRoad() const {
        return ghostRoads;
    }

private:
    double pixel = 16;
    std::vector<std::shared_ptr<Block>> ghostRoads;
    std::vector<std::shared_ptr<Block>> pacmanRoads;
    std::vector<std::shared_ptr<Block>> beans;

    std::vector<std::vector<int>> ghostMap;
    std::vector<std::vector<std::shared_ptr<Block>>> printMap;

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