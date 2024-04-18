#include "outSkirt/LifeSystem.hpp"
#include "Block.hpp"
#include <iostream>
#include <vector>


LifeSystem::LifeSystem(EventManager& eventManager) : eventManager(eventManager) {
    // 在构造函数中将 LifeSystem 实例注册为事件监听器
    eventManager.addListener(COLLISION_WITH_GHOST_EVENT_NOT_INVINCIBLE, std::bind(&LifeSystem::onEvent, this, std::placeholders::_1, std::placeholders::_2));
    this->eventManager = eventManager;
}

void LifeSystem::InitialLifeSystem() {

    nowLife = 3;
    for(int times = 0; times < life_list.size(); times++){
        LifeDecrease();
    }
    LifeCreate();

}

void LifeSystem::LifeDecrease(){
    if(life_list.empty()){
        LOG_DEBUG("the nums of life is already out of cost");
    }else{
        life_list[life_list.size() - 1] ->SetVisible(false);
        life_list.pop_back();
        //RemoveChild(Life3);
        nowLife--;
    }
}

void LifeSystem::LifeCreate() {
    glm::vec2 Position;
    Position.x = xMin - 32;
    Position.y = yMin;
    Life1 = std::make_shared<Life>();;
    Life1 -> SetPosition(Position);
    //this->Life1;
    this->AddChild(Life1);
    life_list.push_back(Life1);
    //AddChild(Life1);

    Position.y = yMin + 32;
    Life2 = std::make_shared<Life>();;
    Life2 -> SetPosition(Position);
    this->AddChild(Life2);
    life_list.push_back(Life2);
    //AddChild(Life2);

    Position.y = yMin + 64;
    Life3 = std::make_shared<Life>();;
    Life3 -> SetPosition(Position);
    this->AddChild(Life3);
    life_list.push_back(Life3);
    //AddChild(Life3);
}

void LifeSystem::SetNowXY(float xMin, float yMin) {
    this->xMin = xMin;
    this->yMin = yMin;
    InitialLifeSystem();
}

/*void Map::Activate(int x_index_now, int y_index_now, int max_x, int max_y, float x_transfer, float y_transfer, std::shared_ptr<Block> now_block) {
    //顯示，偏移量也該傳入
    now_block -> SetPosition({(x_index_now * 16) - x_transfer, ((max_y - y_index_now + 1) * 16) - y_transfer});
    //auto position = GetPosition();
    //SetPosition({position.x, position.y + 2.5f});
}*/

/*bool Ghost::IfAnimationEnds() const {
    auto animation = std::dynamic_pointer_cast<Util::Animation>(m_Drawable);
    return animation->GetCurrentFrameIndex() == animation->GetFrameCount() - 1;
}*/
