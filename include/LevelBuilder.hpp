#ifndef REPLACE_WITH_YOUR_PROJECT_NAME_LEVELBUILDER_HPP
#define REPLACE_WITH_YOUR_PROJECT_NAME_LEVELBUILDER_HPP

#include "Util/Logger.hpp"
#include "Util/LoadTextFile.hpp"
#include "nlohmann/json.hpp"

using Json = nlohmann::json;

class LevelBuilder {
public:
    LevelBuilder() = default;

    explicit LevelBuilder(const std::string &path) {
        json = Json::parse(Util::LoadTextFile(path));
    };

    void Print() {
        LOG_DEBUG("mapSize: ({}, {})", json["mapSize"]["X"].get<int>(), json["mapSize"]["Y"].get<int>());
        LOG_DEBUG("lifeSystemPosition: ({}, {})", json["lifeSystemPosition"]["X"].get<int>(),
                  json["lifeSystemPosition"]["Y"].get<int>());
        LOG_DEBUG("lifeSystemHitPoint: {}", json["lifeSystemHitPoint"].get<int>());
        LOG_DEBUG("fruitSystemPosition: ({}, {})", json["fruitSystemPosition"]["X"].get<int>(),
                  json["fruitSystemPosition"]["Y"].get<int>());
    }

    std::string getLevelName() {
        return json["name"];
    }

    glm::vec2 getMapSize() {
        return glm::vec2{json["mapSize"]["X"].get<int>(), json["mapSize"]["Y"].get<int>()};
    }

    std::vector<std::vector<int>> getMap() {
        return json["map"].get<std::vector<std::vector<int>>>();
    }

    glm::vec2 getLifeSystemPosition() {
        return glm::vec2{json["lifeSystemPosition"]["X"].get<float>(), json["lifeSystemPosition"]["Y"].get<float>()};
    }

    int getLifeSystemHitPoint() {
        return json["lifeSystemHitPoint"].get<int>();
    }

    glm::vec2 getFruitSystemPosition() {
        return glm::vec2{json["fruitSystemPosition"]["X"].get<float>(), json["fruitSystemPosition"]["Y"].get<float>()};
    }

    glm::vec2 getGameScorePosition() {
        return glm::vec2{json["gameScorePosition"]["X"].get<float>(), json["gameScorePosition"]["Y"].get<float>()};
    }

    glm::vec2 getHightScorePosition() {
        return glm::vec2{json["hightScorePosition"]["X"].get<float>(), json["hightScorePosition"]["Y"].get<float>()};
    }

    std::vector<std::string> getGhostNames() {
        return json["ghostName"].get<std::vector<std::string>>();
    }

    std::vector<glm::vec2> getGhostInitialPosition() {
        std::vector<glm::vec2> positions;
        for (std::vector<float> position: json["ghostInitialPosition"].get<std::vector<std::vector<float>>>()) {
            positions.emplace_back(position.at(0), position.at(1));
        }
        return positions;
    }

    std::vector<std::vector<int>> getGhostBFSMap() {
        return json["ghostBFSMap"].get<std::vector<std::vector<int>>>();
    }

    std::vector<std::string> getPacmanDeadImages() {
        std::vector<std::string> paths;
        for (std::string path: json["pacmanDeadImages"].get<std::vector<std::string>>()) {
            paths.push_back(RESOURCE_DIR + path);
        }
        return paths;
    }

    std::vector<std::string> getPacmanUpImages() {
        std::vector<std::string> paths;
        for (std::string path: json["pacmanUpImages"].get<std::vector<std::string>>()) {
            paths.push_back(RESOURCE_DIR + path);
        }
        return paths;
    }

    std::vector<std::string> getPacmanDownImages() {
        std::vector<std::string> paths;
        for (std::string path: json["pacmanDownImages"].get<std::vector<std::string>>()) {
            paths.push_back(RESOURCE_DIR + path);
        }
        return paths;
    }

    std::vector<std::string> getPacmanRightImages() {
        std::vector<std::string> paths;
        for (std::string path: json["pacmanRightImages"].get<std::vector<std::string>>()) {
            paths.push_back(RESOURCE_DIR + path);
        }
        return paths;
    }

    std::vector<std::string> getPacmanLeftImages() {
        std::vector<std::string> paths;
        for (std::string path: json["pacmanLeftImages"].get<std::vector<std::string>>()) {
            paths.push_back(RESOURCE_DIR + path);
        }
        return paths;
    }

    glm::vec2 getPacmanPosition() {
        return glm::vec2{json["pacmanPosition"]["X"].get<float>(), json["pacmanPosition"]["Y"].get<float>()};
    }

    glm::vec2 getBlinkyVulnerableMax() {
        return glm::vec2{json["Vulnerable"]["blinky"]["max"][0].get<float>(),
                         json["Vulnerable"]["blinky"]["max"][1].get<float>()};
    }

    glm::vec2 getBlinkyVulnerableMin() {
        return glm::vec2{json["Vulnerable"]["blinky"]["min"][0].get<float>(),
                         json["Vulnerable"]["blinky"]["min"][1].get<float>()};
    }

    glm::vec2 getPinkyVulnerableMax() {
        return glm::vec2{json["Vulnerable"]["pinky"]["max"][0].get<float>(),
                         json["Vulnerable"]["pinky"]["max"][1].get<float>()};
    }

    glm::vec2 getPinkyVulnerableMin() {
        return glm::vec2{json["Vulnerable"]["pinky"]["min"][0].get<float>(),
                         json["Vulnerable"]["pinky"]["min"][1].get<float>()};
    }

    glm::vec2 getInkyVulnerableMax() {
        return glm::vec2{json["Vulnerable"]["inky"]["max"][0].get<float>(),
                         json["Vulnerable"]["inky"]["max"][1].get<float>()};
    }

    glm::vec2 getInkyVulnerableMin() {
        return glm::vec2{json["Vulnerable"]["inky"]["min"][0].get<float>(),
                         json["Vulnerable"]["inky"]["min"][1].get<float>()};
    }

    glm::vec2 getClydeVulnerableMax() {
        return glm::vec2{json["Vulnerable"]["clyde"]["max"][0].get<float>(),
                         json["Vulnerable"]["clyde"]["max"][1].get<float>()};
    }

    glm::vec2 getClydeVulnerableMin() {
        return glm::vec2{json["Vulnerable"]["clyde"]["min"][0].get<float>(),
                         json["Vulnerable"]["clyde"]["min"][1].get<float>()};
    }

    std::vector<std::vector<glm::vec2>> getJumpPoints() {
        if (json.contains("jumpPoint")) {
            std::vector<std::vector<glm::vec2>> jumpPoints;
            for (auto &jumpPoint: json["jumpPoint"]) {
                jumpPoints.push_back({glm::vec2(jumpPoint[0][0].get<float>(), jumpPoint[0][1].get<float>()),
                                      glm::vec2(jumpPoint[1][0].get<float>(), jumpPoint[1][1].get<float>())});
            }
            return jumpPoints;
        }
        return {};
    }

private:
    Json json;
};

#endif //REPLACE_WITH_YOUR_PROJECT_NAME_LEVELBUILDER_HPP
