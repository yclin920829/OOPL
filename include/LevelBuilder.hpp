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
        LOG_DEBUG("lifeSystemPosition: ({}, {})", json["lifeSystemPosition"]["X"].get<int>(), json["lifeSystemPosition"]["Y"].get<int>());
        LOG_DEBUG("lifeSystemHitPoint: {}", json["lifeSystemHitPoint"].get<int>());
        LOG_DEBUG("fruitSystemPosition: ({}, {})", json["fruitSystemPosition"]["X"].get<int>(), json["fruitSystemPosition"]["Y"].get<int>());
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
        return glm::vec2{json["lifeSystemPosition"]["X"].get<int>(), json["lifeSystemPosition"]["Y"].get<int>()};
    }

    int getLifeSystemHitPoint() {
        return json["lifeSystemHitPoint"].get<int>();
    }

    glm::vec2 getFruitSystemPosition() {
        return glm::vec2{json["fruitSystemPosition"]["X"].get<int>(), json["fruitSystemPosition"]["Y"].get<int>()};
    }

    glm::vec2 getGameScorePosition() {
        return glm::vec2{json["gameScorePosition"]["X"].get<int>(), json["gameScorePosition"]["Y"].get<int>()};
    }

    glm::vec2 getHightScorePosition() {
        return glm::vec2{json["hightScorePosition"]["X"].get<int>(), json["hightScorePosition"]["Y"].get<int>()};
    }

private:
    Json json;
};

#endif //REPLACE_WITH_YOUR_PROJECT_NAME_LEVELBUILDER_HPP
