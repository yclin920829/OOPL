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
    explicit Ghost(const std::string &name, std::vector<std::vector<int>> map) : map(map){
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
    }

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

    void ReStart(){
        this->ghostState = normalGhost;
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

    int dx[4] = {-1, 1, 0, 0};
    int dy[4] = {0, 0, -1, 1};

    std::vector<glm::vec2> shortestPath(glm::vec2 start) {
        int n = map.size();
        int m = map[0].size();

        std::vector<std::vector<bool>> visited(n, std::vector<bool>(m, false));
        std::vector<std::vector<glm::vec2>> parent(n, std::vector<glm::vec2>(m, glm::vec2(-1, -1)));

        std::queue<glm::vec2> q;
        q.push(start);
        visited[start.x][start.y] = true;

        while (!q.empty()) {
            glm::vec2 curr = q.front();
            q.pop();

            if (curr.x == targetPosition.x && curr.y == targetPosition.y) {
                break; // 找到了目标点，停止搜索
            }

            for (int i = 0; i < 4; i++) {
                int nx = curr.x + dx[i];
                int ny = curr.y + dy[i];

                if (nx >= 0 && nx < n && ny >= 0 && ny < m && map[nx][ny] == 1 && !visited[nx][ny]) {
                    visited[nx][ny] = true;
                    parent[nx][ny] = curr;
                    q.push(glm::vec2(nx, ny));
                }
            }

        }

        // 从终点回溯到起点，构建路径
        std::vector<glm::vec2> path;
        glm::vec2 curr = targetPosition;
        while (!(curr.x == start.x && curr.y == start.y)) {
//            if(curr.x == -1 && curr.y == -1) break;
            path.push_back(curr);
            curr = parent[curr.x][curr.y];
        }
        path.push_back(start);

        // 将路径反转，使其从起点到终点
        reverse(path.begin(), path.end());
        road.clear();
        road = path;
        return path;
    }

    void move() {
        std::this_thread::sleep_for(std::chrono::milliseconds((125 / 8)));
        if(road.size() < 2) {
            road.clear();
            return;
        };
        if ((road[0].x == road[1].x) && (road[1].y - road[0].y == 1)) { // right
            MoveRight();
        } else if ((road[0].x == road[1].x) && (road[1].y - road[0].y == -1)) { // left
            MoveLeft();
        } else if ((road[1].x - road[0].x == -1) && (road[0].y == road[1].y)) { // left
            MoveUp();
        } else if ((road[1].x - road[0].x == 1) && (road[0].y == road[1].y)) { // Down
            MoveDown();
        }
        road.erase(road.begin());
    }

    bool IsArrivePosition() {
        return road.empty();
    }

    void SetTargetPosition(glm::vec2 position) {
        targetPosition = position;
    }


private:

    glm::vec2 targetPosition = {0, 0};

    std::vector<glm::vec2> road;
    std::vector<std::vector<int>> map;

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
