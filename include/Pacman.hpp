#ifndef REPLACE_WITH_YOUR_PROJECT_NAME_PACMAN_HPP
#define REPLACE_WITH_YOUR_PROJECT_NAME_PACMAN_HPP

#include <vector>
#include <string>

#include "Util/Animation.hpp"
#include "Util/GameObject.hpp"

class Pacman : public Util::GameObject {
public:
    explicit Pacman() = default;

    [[nodiscard]] bool IsLooping() const {
        return std::dynamic_pointer_cast<Util::Animation>(m_Drawable)->GetLooping();
    }

    [[nodiscard]] bool IsPlaying() const {
        return std::dynamic_pointer_cast<Util::Animation>(m_Drawable)->GetState() == Util::Animation::State::PLAY;
    }

    void SetLooping(bool looping) {
        auto temp = std::dynamic_pointer_cast<Util::Animation>(m_Drawable);
        temp->SetLooping(looping);
    }

    void SetPlaying() {
        auto temp = std::dynamic_pointer_cast<Util::Animation>(m_Drawable);
        temp->Play();
    }

    [[nodiscard]] bool IfAnimationEnds() const {
        auto animation = std::dynamic_pointer_cast<Util::Animation>(m_Drawable);
        return animation->GetCurrentFrameIndex() == animation->GetFrameCount() - 1;
    };

    void Stop() {
        auto temp = std::dynamic_pointer_cast<Util::Animation>(m_Drawable);
        temp->Pause();
    };

    void MoveUp() {
        SetDrawable(UP);
        auto position = GetPosition();
        SetPosition({position.x, position.y + 2.5f});
    }

    void MoveDown() {
        SetDrawable(DOWN);
        auto position = GetPosition();
        SetPosition({position.x, position.y - 2.5f});
    }

    void MoveRight() {
        SetDrawable(RIGHT);
        auto position = GetPosition();
        SetPosition({position.x + 2.5f, position.y});
    }

    void MoveLeft() {
        SetDrawable(LEFT);
        auto position = GetPosition();
        SetPosition({position.x - 2.5f, position.y});
    }

    [[nodiscard]] const glm::vec2& GetPosition() const { return m_Transform.translation; }

    void SetPosition(const glm::vec2& Position) { m_Transform.translation = Position; }

    void SetUpImages(const std::vector<std::string>& AnimationPaths) {
        UP = std::make_shared<Util::Animation>(AnimationPaths, true, 300, true, 0);
    }

    void SetDownImages(const std::vector<std::string>& AnimationPaths) {
        DOWN = std::make_shared<Util::Animation>(AnimationPaths, true, 300, true, 0);
    }

    void SetRightImages(const std::vector<std::string>& AnimationPaths) {
        RIGHT = std::make_shared<Util::Animation>(AnimationPaths, true, 300, true, 0);
    }

    void SetLeftImages(const std::vector<std::string>& AnimationPaths) {
        LEFT = std::make_shared<Util::Animation>(AnimationPaths, true, 300, true, 0);
    }

    void SetDrawble2() {
        SetDrawable(UP);
    }

private:
    std::vector<std::string> ghost_U;
    std::vector<std::string> ghost_D;
    std::vector<std::string> ghost_R;
    std::vector<std::string> ghost_L;

    std::shared_ptr<Core::Drawable> UP;
    std::shared_ptr<Core::Drawable> DOWN;
    std::shared_ptr<Core::Drawable> RIGHT;
    std::shared_ptr<Core::Drawable> LEFT;
};

#endif //REPLACE_WITH_YOUR_PROJECT_NAME_PACMAN_HPP
