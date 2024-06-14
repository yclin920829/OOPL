#ifndef REPLACE_WITH_YOUR_PROJECT_NAME_GHOST_HPP
#define REPLACE_WITH_YOUR_PROJECT_NAME_GHOST_HPP

#include "GhostState.hpp"
#include "Util/GameObject.hpp"
#include "Util/Animation.hpp"
#include "GhostVulnerableState.hpp"
#include "GhostDeadState.hpp"
#include "GhostNormalState.hpp"
#include "Util/Logger.hpp"
#include <queue>
#include<thread>

class Ghost : public Util::GameObject {
public:
    explicit Ghost(std::string name, std::vector<std::vector<int>> map, glm::vec2 initPosotion) : initPosotion(
        initPosotion), map(map) {
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
        SetPosition(initPosotion);
        SetDrawable(ghostState->GetUpImages());
    }

    std::string GetState() {
        return ghostState->GetState();
    }

    void Normal() {
        this->ghostState = normalGhost;
        SetDrawable(ghostState->GetUpImages());
        road.clear();
    }

    void Vulnerable() {
        this->ghostState = vulnerableGhost;
        SetDrawable(ghostState->GetUpImages());
        road.clear();
    }

    void Dead() {
        this->ghostState = deadGhost;
        SetDrawable(ghostState->GetUpImages());
        road.clear();
    }

    void ReStart() {
        this->ghostState = normalGhost;
        SetPosition(initPosotion);
        road.clear();
    }

    void MoveUp() {
        SetDrawable(ghostState->GetUpImages());
        auto position = GetPosition();
        SetPosition({position.x, position.y + 16.0f});
    }

    void MoveDown() {
        SetDrawable(ghostState->GetDownImages());
        auto position = GetPosition();
        SetPosition({position.x, position.y - 16.0f});
    }

    void MoveRight() {
        SetDrawable(ghostState->GetRightImages());
        auto position = GetPosition();
        SetPosition({position.x + 16.0f, position.y});
    }

    void MoveLeft() {
        SetDrawable(ghostState->GetLeftImages());
        auto position = GetPosition();
        SetPosition({position.x - 16.0f, position.y});
    }

    [[nodiscard]] const glm::vec2 &GetPosition() const { return m_Transform.translation; }

    void SetPosition(const glm::vec2 &Position) { m_Transform.translation = Position; }

    void setRoad(const std::vector<glm::vec2> &road) {
        this->road.clear();
        this->road = road;
    }

    void move() {
        std::this_thread::sleep_for(std::chrono::milliseconds((125 / 8)));
        if (road.size() < 2) {
            road.clear();
            return;
        };
        if ((road[0].x == road[1].x) && (road[1].y - road[0].y == 1)) { // right
            MoveRight();
        } else if ((road[0].x == road[1].x) && (road[1].y - road[0].y == -1)) { // left
            MoveLeft();
        } else if ((road[1].x - road[0].x == -1) && (road[0].y == road[1].y)) { // up
            MoveUp();
        } else if ((road[1].x - road[0].x == 1) && (road[0].y == road[1].y)) { // Down
            MoveDown();
        }
        road.erase(road.begin());
    }

    bool IsArrivePosition() {
        return road.empty();
    }

    const glm::vec2 &getTargetPosition() const {
        return targetPosition;
    }

    void SetTargetPosition(glm::vec2 position) {
        targetPosition = position;
    }

    void setJumpPoint(const std::vector<std::vector<glm::vec2>> &jumpPoint) {
        this->jumpPoint = jumpPoint;
    }

    void JumpPoint(){
        for(auto &jumpPoint : jumpPoint){
            if(GetPosition() == jumpPoint[0]){
                SetPosition(jumpPoint[1]);
                road.clear();
                return;
            }
        }
    }


private:

    glm::vec2 targetPosition = {0, 0};
    glm::vec2 initPosotion;

    std::vector<glm::vec2> road;
    std::vector<std::vector<int>> map;

    std::vector<std::vector<glm::vec2>> jumpPoint;

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
