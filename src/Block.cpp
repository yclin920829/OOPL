#include <iostream>
#include "Block.hpp"
#include "Util/Image.hpp"

Block :: Block(int map_code_number) {
    Mapper[0] = "in_game_black";
    Mapper[1] = "upper_border";
    Mapper[2] = "lower_border";
    Mapper[3] = "left_border";
    Mapper[4] = "right_border";
    Mapper[5] = "upper_left_border";
    Mapper[6] = "upper_right_border";
    Mapper[7] = "lower_left_border";
    Mapper[8] = "lower_right_border";
    Mapper[9] = "upper_side";
    Mapper[10] = "lower_side";
    Mapper[11] = "left_side";
    Mapper[12] = "right_side";
    Mapper[13] = "upper_left_side";
    Mapper[14] = "upper_right_side";
    Mapper[15] = "lower_left_side";
    Mapper[16] = "lower_right_side";
    Mapper[17] = "left_respawn_gate";
    Mapper[18] = "right_respawn_gate";
    Mapper[19] = "respawn_gate";
    Mapper[20] = "upper_respawn";
    Mapper[21] = "lower_respawn";
    Mapper[22] = "left_respawn";
    Mapper[23] = "right_respawn";
    Mapper[24] = "upper_left_respawn";
    Mapper[25] = "upper_right_respawn";
    Mapper[26] = "lower_left_respawn";
    Mapper[27] = "lower_right_respawn";
    SetImage(RESOURCE_DIR"/Image/Map_Blocks/" + Mapper[map_code_number] + ".png");
//    std::cout << RESOURCE_DIR"/Image/Map_Blocks/" + Mapper[map_code_number] + ".png\n";
//    std::cout << std::to_string(map_code_number) ;
//    SetImage(RESOURCE_DIR"/Image/Map_Blocks/lower_right_respawn.png");

}

int Block::GetBlockNumber(){
    return map_code_number;
}

void Block::SetImage(const std::string &ImagePath) {
    m_ImagePath = ImagePath;

    m_Drawable = std::make_shared<Util::Image>(m_ImagePath);
}
