#ifndef REPLACE_WITH_YOUR_PROJECT_NAME_LIFESYSTEM_HPP
#define REPLACE_WITH_YOUR_PROJECT_NAME_LIFESYSTEM_HPP

#include "event/EventManager.hpp"
#include "event/EventType.hpp"
#include "Util/GameObject.hpp"
#include "Util/Logger.hpp"
#include "Life.hpp"
#include "App.hpp"

class LifeSystem : public Util::GameObject {
public:
    explicit LifeSystem(EventManager * eventManager) {
        eventManager->addListener(COLLISION_WITH_GHOST_EVENT_NOT_INVINCIBLE, std::bind(&LifeSystem::onEvent, this, std::placeholders::_1, std::placeholders::_2));
    };

    void onEvent(EventType eventType, const EventData& eventData){
        if (eventType == COLLISION_WITH_GHOST_EVENT_NOT_INVINCIBLE) {
            LifeDecrease();
        }
    }

    void LifeDecrease() {
        if(lifes.empty()){
            LOG_DEBUG("the nums of life is already out of cost");
        }else{
            this->RemoveChild(this->GetChildren().back());
            lifes.pop_back();
            hitPoints--;
        }
    };

    void InitialLifeSystem() {
        lifes.clear();
        for (int i = 0; i < hitPoints ; i++){
            std::shared_ptr<Life> life = std::make_shared<Life>();
            life->SetPosition({position.x - 32, (position.y + (float)i * 32)});
            this->AddChild(life);
            lifes.push_back(life);
        }
    };

    void SetSystemPosition(glm::vec2 position) {
        this->position = position;
    };

    bool IsDone(){
        if(hitPoints == 0) return true;
        return false;
    }

private:
    glm::vec2 position {0, 0};

    int hitPoints = 2;
    std::vector<std::shared_ptr<Life>> lifes;

};

#endif //REPLACE_WITH_YOUR_PROJECT_NAME_LIFESYSTEM_HPP
