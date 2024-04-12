#ifndef REPLACE_WITH_YOUR_PROJECT_NAME_GHOST_HPP
#define REPLACE_WITH_YOUR_PROJECT_NAME_GHOST_HPP

#include "GhostState.hpp"
#include "Util/GameObject.hpp"
#include "Util/Animation.hpp"

class Ghost : public Util::GameObject {
public:
    explicit Ghost() = default;

    std::string GetState() {
        return ghostState->GetState();
    }

    void SetState(GhostState *state) {
        this->ghostState = state;
        Draw();
    }

    void SetUpImages(const std::vector<std::string> &images) {
        this->ghostState->SetUpImages(images);
    }

    void SetDownImages(const std::vector<std::string> &images) {
        this->ghostState->SetDownImages(images);
    }

    void SetRightImages(const std::vector<std::string> &images) {
        this->ghostState->SetRightImages(images);
    }

    void SetLeftImages(const std::vector<std::string> &images) {
        this->ghostState->SetLeftImages(images);
    }

    void Draw() {
        SetDrawable(ghostState->GetUpImages());
    }

    void MoveUp() {
        SetDrawable(ghostState->GetUpImages());
        auto position = GetPosition();
        SetPosition({position.x, position.y + 8.0f});
    }

    void MoveDown() {
        SetDrawable(ghostState->GetDownImages());
        auto position = GetPosition();
        SetPosition({position.x, position.y - 8.0f});
    }

    void MoveRight() {
        SetDrawable(ghostState->GetRightImages());
        auto position = GetPosition();
        SetPosition({position.x + 8.0f, position.y});
    }

    void MoveLeft() {
        SetDrawable(ghostState->GetLeftImages());
        auto position = GetPosition();
        SetPosition({position.x - 8.0f, position.y});
    }

    [[nodiscard]] const glm::vec2 &GetPosition() const { return m_Transform.translation; }

    void SetPosition(const glm::vec2 &Position) { m_Transform.translation = Position; }

private:
    GhostState *ghostState;
};

#endif //REPLACE_WITH_YOUR_PROJECT_NAME_GHOST_HPP
