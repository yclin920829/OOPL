#ifndef REPLACE_WITH_YOUR_PROJECT_NAME_FRUIT_HPP
#define REPLACE_WITH_YOUR_PROJECT_NAME_FRUIT_HPP

#include "Util/GameObject.hpp"
#include "Util/Image.hpp"

class Fruit : public Util::GameObject {
public:
    explicit Fruit(const std::string& ImagePath) {
        m_Drawable = std::make_shared<Util::Image>(ImagePath);
        ResetPosition();
    };

    [[nodiscard]] const glm::vec2& GetPosition() const { return m_Transform.translation; }

    [[nodiscard]] bool GetVisibility() const { return m_Visible; }

    void SetPosition(const glm::vec2& Position) { m_Transform.translation = Position; }

private:
    void ResetPosition() { m_Transform.translation = {0, 0}; }
};

#endif //REPLACE_WITH_YOUR_PROJECT_NAME_FRUIT_HPP
