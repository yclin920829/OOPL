#ifndef REPLACE_WITH_YOUR_PROJECT_NAME_LIFESYSTEM_HPP
#define REPLACE_WITH_YOUR_PROJECT_NAME_LIFESYSTEM_HPP

#include "Util/GameObject.hpp"
#include "EventManager.hpp"
#include "EventType.hpp"
#include "Life.hpp"
#include "Map.hpp"

class LifeSystem : public Util::GameObject{
public:

    explicit LifeSystem(EventManager& eventManager);
    ~LifeSystem() override = default;

    // 实现事件监听器接口
    void onEvent(EventType eventType, const EventData& eventData){
        if (eventType == COLLISION_WITH_GHOST_EVENT_NOT_INVINCIBLE) {
            // 当碰撞事件发生时，执行生命系统相关逻辑
            LifeDecrease();
        }
    }

    [[nodiscard]] bool GetVisibility() const { return m_Visible; }


    void LifeDecrease();

    void LifeCreate();

    void SetNowXY(float xMin, float yMin);

    //bool CheckLifeLogical();

    void InitialLifeSystem();

private:
    //void ResetPosition() { m_Transform.translation = {0, 0}; }
    float xMin, yMin;

    EventManager& eventManager; // 事件管理器对象
    int nowLife;
    std::shared_ptr<Life> Life1,Life2,Life3;
    std::vector<std::shared_ptr<Life>>life_list;

};

#endif //REPLACE_WITH_YOUR_PROJECT_NAME_LIFESYSTEM_HPP
