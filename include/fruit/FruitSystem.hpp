#ifndef REPLACE_WITH_YOUR_PROJECT_NAME_FRUITSYSTEM_HPP
#define REPLACE_WITH_YOUR_PROJECT_NAME_FRUITSYSTEM_HPP

#include "Util/GameObject.hpp"
#include "Fruit.hpp"

class FruitSystem : public Util::GameObject {
public:

    explicit FruitSystem(const glm::vec2 &Position, const glm::vec2 cherryPosition) {
        m_Transform.translation = Position;
        m_Drawable = std::make_shared<Util::Image>(RESOURCE_DIR"/Image/Character/Fruit/cherry.png");

        cherry = std::make_shared<Fruit>(RESOURCE_DIR"/Image/Character/Fruit/cherry.png");
        cherry->SetPosition(cherryPosition);
        cherry->SetZIndex(25);
        cherry->SetVisible(false);
        this->AddChild(cherry);
    };

    [[nodiscard]] const std::shared_ptr<Fruit> &getCherry() const {
        return cherry;
    }

private:
    std::shared_ptr<Fruit> cherry;
};

#endif //REPLACE_WITH_YOUR_PROJECT_NAME_FRUITSYSTEM_HPP
