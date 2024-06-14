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
    explicit LifeSystem(int hitPoints, glm::vec2 position) : hitPoints(hitPoints) {
        for (int i = 0; i < hitPoints - 1; i++) {
            std::shared_ptr<Life> life = std::make_shared<Life>();
            life->SetPosition({position.x, (position.y + (float) i * 32)});
            this->AddChild(life);
        }
    };

    void AddEventManager(EventManager *eventManager) {
        eventManager->addListener(COLLISION_WITH_GHOST_EVENT_NOT_INVINCIBLE,
                                  std::bind(&LifeSystem::onEvent, this, std::placeholders::_1, std::placeholders::_2));
    }

    void onEvent(EventType eventType, const EventData &eventData) {
        if (eventType == COLLISION_WITH_GHOST_EVENT_NOT_INVINCIBLE) {
            LifeDecrease();
        }
    }

    void LifeDecrease() {
        this->RemoveChild(this->GetChildren().back());
        hitPoints--;
    };

    [[nodiscard]] bool IsDone() const {
        return hitPoints == 0;
    }

private:
    int hitPoints;
};

#endif //REPLACE_WITH_YOUR_PROJECT_NAME_LIFESYSTEM_HPP
