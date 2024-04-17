#ifndef MAP_HPP
#define MAP_HPP

#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <map>
#include "Block.hpp"

#include "outSkirt/LifeSystem.hpp"
#include "Util/Animation.hpp"
#include "Util/GameObject.hpp"
#include "Util/Root.hpp"
//using namespace std;


/*class Map : public Util::GameObject {

public:
    explicit Map(const int x_size, const int y_size, std::vector<std::vector<int>> map_by_number);

    //單一地圖開啟時呼叫一輪來貼上圖片
    void Activate(int x_index_now, int y_index_now, int max_x, int max_y, float x_transfer, float y_transfer, std::shared_ptr<Block> now_block);

    std::vector<std::vector<std::shared_ptr<Block>>> map;

};*/

class Map : public Util::GameObject {
public:
    explicit Map(const int m, const int n, std::vector<std::vector<int>> map_by_number) {
        double x_transfer = (pixel / 2) * m;
        double y_transfer = (pixel / 2) * n;
        std::vector<std::shared_ptr<Block>> row;

        for (int i = 0; i < n; ++i) {
            row.clear();
            for (int j = 0; j < m; ++j) {
                double positionX = (j * pixel) - x_transfer;
                double positionY = ((n - i + 1) * pixel) - y_transfer;

                std::shared_ptr<Block> block = std::make_shared<Block>(map_by_number[i][j]);
                block->SetPosition({positionX, positionY});
                this->AddChild(block);
                row.push_back(block);

            }
            this->map_by_number.push_back(row);
        }
        this->print();

    }

    void print() {
        int i = 0;
        for (const std::vector<std::shared_ptr<Block>> &row: map_by_number) {
            std::cout << std::setw(2) << i + 1 << ": ";
            int j = 0;
            for (const std::shared_ptr<Block> &column: row) {
                std::cout << j + 1 << "(" << std::setw(5) << column->GetPosition().x << ", " << std::setw(5)
                          << column->GetPosition().y << "), ";
                std::cout << column->GetScaledSize().x << column->GetScaledSize().y;
                j++;
            }
            std::cout << "\n";
            i++;
        }
    }

    bool IsPacmanRoad(const glm::vec2 &Position) {
        for (const std::vector<std::shared_ptr<Block>> &row: map_by_number) {
            for (const std::shared_ptr<Block> &column: row) {
                if (column->GetPosition() == Position) {
                    if (column->GetBlockNumber() == 0) {
                        return true;
                    } else {
                        return false;
                    }
                }
            }
        }
        return false;
    }

    std::vector<std::vector<std::shared_ptr<Block>>> map_by_number;

private:
    double pixel = 16;
    //std::vector<std::vector<std::shared_ptr<Block>>> map_by_number;
};

#endif //MAP_HPP