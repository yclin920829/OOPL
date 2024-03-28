#include "Map.hpp"
#include "Block.hpp"
#include <iostream>
#include <vector>

//建構map時給定m,n和地圖對表的數值
Map::Map(const int m, const int n, std::vector<std::vector<int>> map_by_number) {

    map = std::vector<std::vector<std::shared_ptr<Block>>>(n, std::vector<std::shared_ptr<Block>>(m));
    float x_transfer = 8 * m;//將座標(0,0)偏移至左上角
    float y_transfer = 8 * n;
    /*std::pair<float, float> transfer;
    transfer.first = x_transfer;
    transfer.second = y_transfer;*/
    // 将每个指针指向一个新创建的 Block 对象並給值
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            map[i][j] = std::make_shared<Block>(map_by_number[i][j]);
            this->AddChild(map[i][j]);
            std::cout << " ";
            Activate(j, i, m, n, x_transfer, y_transfer, map[i][j]);
        }
        std::cout << std::endl;
    }

//    for (int i = 0; i < n; ++i) {
//        for (int j = 0; j < m; ++j) {
//            std::cout << map[i][j]->GetBlockNumber() << " ";
//        }
//        std::cout << std::endl;
//    }

    /*ghost_L = {AnimationPaths[3], AnimationPaths[7]};
    RIGHT = std::make_shared<Util::Animation>(ghost_R, true, 300, true, 0);
    LEFT = std::make_shared<Util::Animation>(ghost_L, true, 300, true, 0);
    SetDrawable(UP);*/
}

void Map::Activate(int x_index_now, int y_index_now, int max_x, int max_y, float x_transfer, float y_transfer, std::shared_ptr<Block> now_block) {
    //顯示，偏移量也該傳入
    now_block -> SetPosition({(x_index_now * 16) - x_transfer, ((max_y - y_index_now + 1) * 16) - y_transfer});
    //auto position = GetPosition();
    //SetPosition({position.x, position.y + 2.5f});
}

/*bool Ghost::IfAnimationEnds() const {
    auto animation = std::dynamic_pointer_cast<Util::Animation>(m_Drawable);
    return animation->GetCurrentFrameIndex() == animation->GetFrameCount() - 1;
}*/
