#ifndef MAP_HPP
#define MAP_HPP

#include <vector>
#include <string>
#include <map>
#include "Block.hpp"

#include "Util/Animation.hpp"
#include "Util/GameObject.hpp"
#include "Util/Root.hpp"
//using namespace std;


class Map : public Util::GameObject {

public:
    explicit Map(const int m, const int n, std::vector<std::vector<int>> map_by_number);

    //單一地圖開啟時呼叫一輪來貼上圖片
    void Activate(int x_index_now, int y_index_now, int max_x, int max_y, float x_transfer, float y_transfer, std::shared_ptr<Block> now_block);

private:
//
//    //圖的path(s)
//    std::vector<std::string> block_in_game_black;
//    std::vector<std::string> block_left_border;
//    std::vector<std::string> block_right_border;
//    std::vector<std::string> block_upper_border;
//    std::vector<std::string> block_lower_border;
//    std::vector<std::string> block_upper_left_border;
//    std::vector<std::string> block_upper_right_border;
//    std::vector<std::string> block_lower_left_border;
//    std::vector<std::string> block_lower_right_border;
//    std::vector<std::string> block_left_respawn_gate;
//    std::vector<std::string> block_right_respawn_gate;
//    std::vector<std::string> block_respawn_gate;
//    std::vector<std::string> block_left_respawn;
//    std::vector<std::string> block_right_respawn;
//    std::vector<std::string> block_upper_respawn;
//    std::vector<std::string> block_lower_respawn;
//    std::vector<std::string> block_upper_left_respawn;
//    std::vector<std::string> block_upper_right_respawn;
//    std::vector<std::string> block_lower_left_respawn;
//    std::vector<std::string> block_lower_right_respawn;
//    std::vector<std::string> block_left_side;
//    std::vector<std::string> block_right_side;
//    std::vector<std::string> block_upper_side;
//    std::vector<std::string> block_lower_side;
//    std::vector<std::string> block_upper_left_side;
//    std::vector<std::string> block_upper_right_side;
//    std::vector<std::string> block_lower_left_side;
//    std::vector<std::string> block_lower_right_side;
//
    std::vector<std::vector<std::shared_ptr<Block>>> map;
//
//    //shared_ptr似乎是傳遞建構式參數用的
//    std::shared_ptr<Core::Drawable> UP;
//    std::shared_ptr<Core::Drawable> DOWN;
//    std::shared_ptr<Core::Drawable> RIGHT;
//    std::shared_ptr<Core::Drawable> LEFT;

};

#endif //MAP_HPP