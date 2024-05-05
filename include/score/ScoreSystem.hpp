#ifndef REPLACE_WITH_YOUR_PROJECT_NAME_SCORESYSTEM_HPP
#define REPLACE_WITH_YOUR_PROJECT_NAME_SCORESYSTEM_HPP

#include "Util/GameObject.hpp"
#include "event/EventManager.hpp"
#include "event/EventType.hpp"
#include "Score.hpp"
#include <vector>

class ScoreSystem : public Util::GameObject{
public:

    explicit ScoreSystem(EventManager * eventManager): eventManager(eventManager){
        eventManager->addListener(COLLISION_TO_ADD_SCORE, std::bind(&ScoreSystem::onEvent, this, std::placeholders::_1, std::placeholders::_2));
    };

    void onEvent(EventType eventType, const EventData& eventData){
        if (eventType == COLLISION_TO_ADD_SCORE) {
            HandleScoreLogic(eventData.quantity);
        }
    }

    void InitialScoreSystem() {
        this->nowScore = 0;
        this->highestScore = 0;
        ScoreCreate();
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


    void ScoreCreate() {
        NowScore = std::make_shared<Score>();
        NowScore -> SetPosition({-294, 208});
        NowScore -> SetImage((RESOURCE_DIR"/Image/Out_Map/game_score.png"));
        NowScore -> NumberInitial();
        this->AddChild(NowScore);


        HighestScore = std::make_shared<Score>();
        HighestScore -> SetPosition({284,208});
        HighestScore -> SetImage((RESOURCE_DIR"/Image/Out_Map/high_score.png"));
        HighestScore -> NumberInitial();
        this->AddChild(HighestScore);
    }

    void SetNowXY(float xMin, float yMax, float xMax) {
        this->xMin = xMin;
        this->xMax = xMax;
        this->yMax = yMax;
    };


private:

    int nowLevel = 0;
    std::vector<int> highScore;
    float xMin, yMax, xMax;
    int highestScore = 0;
    int nowScore = 0;

    EventManager * eventManager;
    std::shared_ptr<Score> HighestScore,NowScore;

};

#endif //REPLACE_WITH_YOUR_PROJECT_NAME_SCORESYSTEM_HPP
