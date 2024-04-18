#ifndef REPLACE_WITH_YOUR_PROJECT_NAME_SCORESYSTEM_HPP
#define REPLACE_WITH_YOUR_PROJECT_NAME_SCORESYSTEM_HPP

#include "Util/GameObject.hpp"
#include "EventManager.hpp"
#include "EventType.hpp"
#include "Score.hpp"
#include <vector>

class ScoreSystem : public Util::GameObject{
public:

    explicit ScoreSystem(EventManager& eventManager): eventManager(eventManager){
        eventManager.addListener(COLLISION_TO_ADD_SCORE, std::bind(&ScoreSystem::onEvent, this, std::placeholders::_1, std::placeholders::_2));
        this->eventManager = eventManager;
    };
    ~ScoreSystem() override = default;

    // 实现事件监听器接口
    void onEvent(EventType eventType, const EventData& eventData){
        if (eventType == COLLISION_TO_ADD_SCORE) {
            //
            HandleScoreLogic(eventData.quantity);
        }
    }

    [[nodiscard]] bool GetVisibility() const { return m_Visible; }


    void InitialScoreSystem() {

        this->nowScore = 0;
        this->highestScore = 0;
        //RemoveChild(NowScore);
        //RemoveChild(HighestScore);
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
            highScore[nowLevel] = highestScore;
        }

        this -> highestScore = 0;

    }//切換關卡後才使用


    void ScoreCreate() {
        glm::vec2 Position_nowScore;
        Position_nowScore.x = xMin - 70;
        Position_nowScore.y = yMax;
        NowScore = std::make_shared<Score>();
        NowScore -> SetPosition(Position_nowScore);
        NowScore -> SetImage((RESOURCE_DIR"/Image/Out_Map/game_score.png"));
        NowScore -> NumberInitial();
        //this->Life1;
        this->AddChild(NowScore);
        //life_list.push_back(Life1);
        //AddChild(Life1);

        glm::vec2 Position_highestScore;
        Position_highestScore.x = xMax + 20;
        Position_highestScore.y = yMax;
        HighestScore = std::make_shared<Score>();
        HighestScore -> SetPosition(Position_highestScore);
        HighestScore -> SetImage((RESOURCE_DIR"/Image/Out_Map/high_score.png"));
        HighestScore -> NumberInitial();
        //this->Life1;
        this->AddChild(HighestScore);
    }

    void SetNowXY(float xMin, float yMax, float xMax) {
        this->xMin = xMin;
        this->xMax = xMax;
        this->yMax = yMax;
    };


private:

    int nowLevel = 0;
    std::vector<int> highScore = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    float xMin, yMax, xMax;
    int highestScore = 0;
    int nowScore = 0;

    EventManager& eventManager; // 事件管理器对象
    //int nowLife;
    std::shared_ptr<Score> HighestScore,NowScore;
    //std::vector<std::shared_ptr<Life>>life_list;

};
//一次管兩種分數
#endif //REPLACE_WITH_YOUR_PROJECT_NAME_SCORESYSTEM_HPP
