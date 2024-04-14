#ifndef REPLACE_WITH_YOUR_PROJECT_NAME_GHOST_HPP
#define REPLACE_WITH_YOUR_PROJECT_NAME_GHOST_HPP

#include "GhostState.hpp"
#include "Util/GameObject.hpp"
#include "Util/Animation.hpp"
#include "GhostVulnerableState.hpp"
#include "GhostDeadState.hpp"
#include "GhostNormalState.hpp"

class Ghost : public Util::GameObject {
public:
    explicit Ghost(const std::string &name) {
        normalGhost = new GhostNormalState();
        deadGhost = new GhostDeadState();
        vulnerableGhost = new GhostVulnerableState();

        normalGhost->SetUpImages({RESOURCE_DIR"/Image/Character/" + name + "/" + name + "_U_01.png",
                                  RESOURCE_DIR"/Image/Character/" + name + "/" + name + "_U_02.png"});
        normalGhost->SetDownImages({RESOURCE_DIR"/Image/Character/" + name + "/" + name + "_D_01.png",
                                    RESOURCE_DIR"/Image/Character/" + name + "/" + name + "_D_02.png"});
        normalGhost->SetRightImages({RESOURCE_DIR"/Image/Character/" + name + "/" + name + "_R_01.png",
                                     RESOURCE_DIR"/Image/Character/" + name + "/" + name + "_R_02.png"});
        normalGhost->SetLeftImages({RESOURCE_DIR"/Image/Character/" + name + "/" + name + "_L_01.png",
                                    RESOURCE_DIR"/Image/Character/" + name + "/" + name + "_L_02.png"});

        deadGhost->SetUpImages({RESOURCE_DIR"/Image/Character/Ghost_dead/Ghost_dead_U.png"});
        deadGhost->SetDownImages({RESOURCE_DIR"/Image/Character/Ghost_dead/Ghost_dead_D.png"});
        deadGhost->SetRightImages({RESOURCE_DIR"/Image/Character/Ghost_dead/Ghost_dead_R.png"});
        deadGhost->SetLeftImages({RESOURCE_DIR"/Image/Character/Ghost_dead/Ghost_dead_L.png"});

        vulnerableGhost->SetUpImages(VulnerableGhostsImages);
        vulnerableGhost->SetDownImages(VulnerableGhostsImages);
        vulnerableGhost->SetRightImages(VulnerableGhostsImages);
        vulnerableGhost->SetLeftImages(VulnerableGhostsImages);

        ghostState = normalGhost;
        SetZIndex(15);
        SetVisible(true);
        SetDrawable(ghostState->GetUpImages());
    };

    std::string GetState() {
        return ghostState->GetState();
    }

    void Normal() {
        this->ghostState = normalGhost;
        SetDrawable(ghostState->GetUpImages());
    }

    void Vulnerable() {
        this->ghostState = vulnerableGhost;
        SetDrawable(ghostState->GetUpImages());
    }

    void Dead() {
        this->ghostState = deadGhost;
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
    GhostNormalState *normalGhost;
    GhostDeadState *deadGhost;
    GhostVulnerableState *vulnerableGhost;

    std::vector<std::string> VulnerableGhostsImages = {
        RESOURCE_DIR"/Image/Character/VulnerableGhosts/VulnerableGhosts_B_01.png",
        RESOURCE_DIR"/Image/Character/VulnerableGhosts/VulnerableGhosts_B_02.png",
        RESOURCE_DIR"/Image/Character/VulnerableGhosts/VulnerableGhosts_W_01.png",
        RESOURCE_DIR"/Image/Character/VulnerableGhosts/VulnerableGhosts_W_02.png"
    };
};

#endif //REPLACE_WITH_YOUR_PROJECT_NAME_GHOST_HPP
