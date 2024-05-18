#ifndef REPLACE_WITH_YOUR_PROJECT_NAME_STARTBUTTON_HPP
#define REPLACE_WITH_YOUR_PROJECT_NAME_STARTBUTTON_HPP

#include "Util/GameObject.hpp"
#include "Util/Image.hpp"



class StartButton : public Util::GameObject {
public:
    explicit StartButton() {
        SetImage(RESOURCE_DIR"/Image/UI/StartGame-removebg-preview.png");
        ResetPosition();
    };

    [[nodiscard]] const std::string& GetImagePath() const { return m_ImagePath; }

    [[nodiscard]] const glm::vec2& GetPosition() const { return m_Transform.translation; }

    [[nodiscard]] bool GetVisibility() const { return m_Visible; }

    void SetImage(const std::string& ImagePath) {
        m_ImagePath = ImagePath;
        m_Drawable = std::make_shared<Util::Image>(m_ImagePath);
    };

    bool IsOnMe(glm::vec2 nowCursorPosition){
        if((m_Transform.translation.x + HALFWIDTH) > nowCursorPosition.x && (m_Transform.translation.y + HALFHIDTH) > nowCursorPosition.y && (m_Transform.translation.x - HALFWIDTH) < nowCursorPosition.x && (m_Transform.translation.y - HALFHIDTH) < nowCursorPosition.y)
            return true;
        return false;
    }

    void SetPosition(const glm::vec2& Position) { m_Transform.translation = Position; }

private:
    void ResetPosition() { m_Transform.translation = {0, 0}; }
    std::string m_ImagePath;

    float HALFWIDTH = 150;
    float HALFHIDTH = 84;
};

#endif //REPLACE_WITH_YOUR_PROJECT_NAME_STARTBUTTON_HPP
