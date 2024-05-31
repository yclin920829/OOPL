#ifndef REPLACE_WITH_YOUR_PROJECT_NAME_LEVELMANAGER_HPP
#define REPLACE_WITH_YOUR_PROJECT_NAME_LEVELMANAGER_HPP

#include "Level.hpp"

class LevelManager : public Util::GameObject {
public:
    explicit LevelManager(){//暫定存有20個關卡的vector且都只有資訊而無產生實體物件，以防不好換關卡的時候刪除

    };

    void ConstructLevel(int nowLevel){
        this->nowLevel = nowLevel - 1;
        Levels[nowLevel] -> Initialized(nowLevel);
        this -> AddChild(Levels[nowLevel]);
    }

    void LeaveLevel(){//導出需儲存的data然後刪除

    }




private:

    int nowLevel = 0;
    std::vector<std::shared_ptr<Level>> Levels;
};

#endif //REPLACE_WITH_YOUR_PROJECT_NAME_LEVELMANAGER_HPP
