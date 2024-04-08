#ifndef REPLACE_WITH_YOUR_PROJECT_NAME_PACMAN_HPP
#define REPLACE_WITH_YOUR_PROJECT_NAME_PACMAN_HPP

#include "Util/GameObject.hpp"
#include "Util/Animation.hpp"

class Pacman : public Util::GameObject {
public:
    explicit Pacman() = default;

    void SetUpImages(const std::vector<std::string> &images) {
        UP = std::make_shared<Util::Animation>(images, true, 300, true, 0);
    }

    void SetDownImages(const std::vector<std::string> &images) {
        DOWN = std::make_shared<Util::Animation>(images, true, 300, true, 0);
    }

    void SetRightImages(const std::vector<std::string> &images) {
        RIGHT = std::make_shared<Util::Animation>(images, true, 300, true, 0);
    }

    void SetLeftImages(const std::vector<std::string> &images) {
        LEFT = std::make_shared<Util::Animation>(images, true, 300, true, 0);
    }

    void SetDeadImages(const std::vector<std::string> &images) {
        DEAD = std::make_shared<Util::Animation>(images, true, 300, true, 0);
    }

    void Start() {
        SetDrawable(UP);
    }

    void MoveUp() {
        SetDrawable(UP);
        auto position = GetPosition();
        SetPosition({position.x, position.y + 16.0f});
    }

    void MoveDown() {
        SetDrawable(DOWN);
        auto position = GetPosition();
        SetPosition({position.x, position.y - 16.0f});
    }

    void MoveRight() {
        SetDrawable(RIGHT);
        auto position = GetPosition();
        SetPosition({position.x + 16.0f, position.y});
    }

    void MoveLeft() {
        SetDrawable(LEFT);
        auto position = GetPosition();
        SetPosition({position.x - 16.0f, position.y});
    }

    void Dead() {
        SetDrawable(DEAD);
    }

    [[nodiscard]] const glm::vec2 &GetPosition() const { return m_Transform.translation; }

    void SetPosition(const glm::vec2 &Position) { m_Transform.translation = Position; }

private:
    std::shared_ptr<Core::Drawable> UP;
    std::shared_ptr<Core::Drawable> DOWN;
    std::shared_ptr<Core::Drawable> RIGHT;
    std::shared_ptr<Core::Drawable> LEFT;
    std::shared_ptr<Core::Drawable> DEAD;
};

#endif //REPLACE_WITH_YOUR_PROJECT_NAME_PACMAN_HPP
