#ifndef REPLACE_WITH_YOUR_PROJECT_NAME_FRUITSYSTEM_HPP
#define REPLACE_WITH_YOUR_PROJECT_NAME_FRUITSYSTEM_HPP

#include "Util/GameObject.hpp"
#include "EventManager.hpp"
#include "EventType.hpp"
#include "Fruit.hpp"
#include "Map.hpp"

class FruitSystem : public Util::GameObject{
public://可能可以預設被通知要刪掉被碰撞到的cherry

    explicit FruitSystem(/*EventManager& eventManager*/) = default;
    //~FruitSystem() override = default;

    // 实现事件监听器接口
    /*void onEvent(EventType eventType, const EventData& eventData){
        if (eventType == COLLISION_WITH_GHOST_EVENT_NOT_INVINCIBLE) {
            // 当碰撞事件发生时，执行生命系统相关逻辑
            //FruitDecrease();
        }
    }*/

    [[nodiscard]] bool GetVisibility() const { return m_Visible; }

    void SetImage(const std::string& ImagePath){
        //m_ImagePath = ImagePath;
        m_Drawable = std::make_shared<Util::Image>(ImagePath);
    };

    void SetPosition(const glm::vec2& Position) {
        m_Transform.translation = Position;
        SetImage(RESOURCE_DIR"/Image/Character/Fruit/cherry.png");
    };

    void CheckCreatable(glm::vec2& Position){
        if(createUnitTime == 100){
            std::shared_ptr<Fruit> cherry;
            cherry = std::make_shared<Fruit>(RESOURCE_DIR"/Image/Character/Fruit/cherry.png");
            cherry -> SetPosition(Position);
            this->AddChild(cherry);
            fruit_list.push_back(cherry);
        }
    }

    void CheckDeletable() {
        for (auto it = fruit_list.begin(); it != fruit_list.end();) {
            if ((*it)->GetDeleteUnitTime() >= 1000) {
                it = fruit_list.erase(it); // 返回指向下一个元素的迭代器
            } else {
                (*it)->SetDeleteTime();
                ++it; // 迭代器向前移动
            }
        }
    }

    void Clear(){
        fruit_list.clear();
    }


private:
    //void ResetPosition() { m_Transform.translation = {0, 0}; }
    int createUnitTime = 0;//短一點(要看更新單位)
    int deleteUnitTime = 0;//可以長一點
    float xMax, yMin;

    //EventManager& eventManager; // 事件管理器对象

    std::vector<std::shared_ptr<Fruit>>fruit_list;

};

#endif //REPLACE_WITH_YOUR_PROJECT_NAME_FRUITSYSTEM_HPP
