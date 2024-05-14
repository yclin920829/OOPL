#ifndef REPLACE_WITH_YOUR_PROJECT_NAME_SCORESYSTEM_HPP
#define REPLACE_WITH_YOUR_PROJECT_NAME_SCORESYSTEM_HPP

#include "Util/GameObject.hpp"
#include "event/EventManager.hpp"
#include "event/EventType.hpp"
#include "Score.hpp"
#include <vector>

class ScoreSystem : public Util::GameObject{
public:

    explicit ScoreSystem(glm::vec2 gameScorePosition, glm::vec2 hightScorePosition){
        NowScore = std::make_shared<Score>(gameScorePosition);
        NowScore -> SetImage((RESOURCE_DIR"/Image/Out_Map/game_score.png"));
        this->AddChild(NowScore);

        HighestScore = std::make_shared<Score>(hightScorePosition);
        HighestScore -> SetImage((RESOURCE_DIR"/Image/Out_Map/high_score.png"));
        this->AddChild(HighestScore);
    }

    void AddEventManager(EventManager *eventManager) {
        eventManager->addListener(COLLISION_TO_ADD_SCORE, std::bind(&ScoreSystem::onEvent, this, std::placeholders::_1, std::placeholders::_2));
    }

    void onEvent(EventType eventType, const EventData& eventData){
        if (eventType == COLLISION_TO_ADD_SCORE) {
            HandleScoreLogic(eventData.quantity);
        }
    }

    void HandleScoreLogic(int quantity){
        nowScore += quantity;
        if(nowScore >= highestScore){
            highestScore = nowScore;
            HighestScore ->SetScore(highestScore);
        }

        NowScore ->SetScore(nowScore);

    }

    void ClearScore(){
        this -> nowScore = 0;
        if(this -> highestScore != 0){
//            highScore[nowLevel] = highestScore;
            highScore.push_back(highestScore);
        }
        this -> highestScore = 0;
    }

private:

    std::vector<int> highScore;
    int highestScore = 0;
    int nowScore = 0;

    std::shared_ptr<Score> NowScore, HighestScore;

};

#endif //REPLACE_WITH_YOUR_PROJECT_NAME_SCORESYSTEM_HPP
