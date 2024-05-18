#ifndef REPLACE_WITH_YOUR_PROJECT_NAME_UISYSTEM_HPP
#define REPLACE_WITH_YOUR_PROJECT_NAME_UISYSTEM_HPP

#include "Util/GameObject.hpp"
#include "Util/Image.hpp"
#include "GameOver.hpp"
#include "StartButton.hpp"
#include "PacmanSign.hpp"

class UISystem : public Util::GameObject {
public:
    explicit UISystem() {
        //SetImage(ImagePath);
        //ResetPosition();
        Initialize();
    };

    //[[nodiscard]] const std::string& GetImagePath() const { return m_ImagePath; }

    [[nodiscard]] const glm::vec2& GetPosition() const { return m_Transform.translation; }

    [[nodiscard]] bool GetVisibility() const { return m_Visible; }

    void Initialize(){
        this -> GameOverButton = std::make_shared<GameOver>();
        GameOverButton->SetPosition({0, -150});
        this->AddChild(GameOverButton);

        this -> StartGameButton = std::make_shared<StartButton>();
        StartGameButton->SetPosition({0, 0});
        this->AddChild(StartGameButton);

        this -> PacmanButton = std::make_shared<PacmanSign>();
        PacmanButton->SetPosition({0, 100});
        this->AddChild(PacmanButton);
    };

    int CheckOnButton(glm::vec2 nowCursorPosition){
        if(StartGameButton -> IsOnMe(nowCursorPosition))
            return 1;
        if(GameOverButton -> IsOnMe(nowCursorPosition))
            return 2;
        return 0;
    }

    glm::vec2 GetCursorPosition(glm::vec2 nowCursorPosition){

    }

    /*void SetImage(const std::string& ImagePath) {
        m_ImagePath = ImagePath;
        m_Drawable = std::make_shared<Util::Image>(m_ImagePath);
    };*/

    void SetPosition(const glm::vec2& Position) { m_Transform.translation = Position; }

private:
    void ResetPosition() { m_Transform.translation = {0, 0}; }
    std::shared_ptr<GameOver> GameOverButton;
    std::shared_ptr<StartButton> StartGameButton;
    std::shared_ptr<PacmanSign> PacmanButton;
    //std::string m_ImagePath;
};

#endif //REPLACE_WITH_YOUR_PROJECT_NAME_UISYSTEM_HPP
