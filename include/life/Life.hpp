#ifndef REPLACE_WITH_YOUR_PROJECT_NAME_LIFE_HPP
#define REPLACE_WITH_YOUR_PROJECT_NAME_LIFE_HPP

#include "Util/GameObject.hpp"
#include "Util/Image.hpp"

class Life : public Util::GameObject {
public:
    explicit Life(){
        SetImage(RESOURCE_DIR"/Image/Character/Pacman/Pacman_R_01.png");
    };

    void SetImage(const std::string& ImagePath){
        m_Drawable = std::make_shared<Util::Image>(ImagePath);
    };

    void SetPosition(const glm::vec2& Position) { m_Transform.translation = Position; };
};

#endif //REPLACE_WITH_YOUR_PROJECT_NAME_LIFE_HPP
