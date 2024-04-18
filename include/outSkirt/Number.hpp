#ifndef REPLACE_WITH_YOUR_PROJECT_NAME_NUMBER_HPP
#define REPLACE_WITH_YOUR_PROJECT_NAME_NUMBER_HPP

#include <string>
#include <map>
#include "Util/GameObject.hpp"
#include "Util/Image.hpp"


class Number : public Util::GameObject {
public:
    explicit Number() = default;

    [[nodiscard]] bool GetVisibility() const { return m_Visible; }

    void SetImage(const std::string &ImagePath) {
        //m_ImagePath = ImagePath;
        m_Drawable = std::make_shared<Util::Image>(ImagePath);
    };

    void SetPosition(const glm::vec2 &Position) { m_Transform.translation = Position; };

    void SetScore(int score) {
        this->score = score;
        Mapping(this->score);
    };

    void Mapping(int digit_code_number){
        Mapper[0] = "0";
        Mapper[1] = "1";
        Mapper[2] = "2";
        Mapper[3] = "3";
        Mapper[4] = "4";
        Mapper[5] = "5";
        Mapper[6] = "6";
        Mapper[7] = "7";
        Mapper[8] = "8";
        Mapper[9] = "9";
        SetImage(RESOURCE_DIR"/Image/Out_Map/" + Mapper[digit_code_number] + ".png");
    }

private:
    //void ResetPosition() { m_Transform.translation = {0, 0}; }
    int score;
    int digit_code_number;
    std::map<int, std::string> Mapper;

};

#endif //REPLACE_WITH_YOUR_PROJECT_NAME_NUMBER_HPP
