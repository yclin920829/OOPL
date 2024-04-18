#ifndef REPLACE_WITH_YOUR_PROJECT_NAME_SCORE_HPP
#define REPLACE_WITH_YOUR_PROJECT_NAME_SCORE_HPP

#include "Util/GameObject.hpp"
#include "Util/Image.hpp"
#include "Number.hpp"
#include <vector>

class Score : public Util::GameObject {
public:
    explicit Score()=default;

    [[nodiscard]] bool GetVisibility() const { return m_Visible; }

    void SetImage(const std::string& ImagePath){
        //m_ImagePath = ImagePath;
        m_Drawable = std::make_shared<Util::Image>(ImagePath);
    };

    void SetPosition(const glm::vec2& Position) { m_Transform.translation = Position; };

    void SetScore(int score){
        this->score = score;
        SetNumbers();
    };

    void SetNumbers(){
        std::vector<int> digits = splitDigits(score);
        TenThousandDigit -> SetScore(digits[0]);
        ThousandDigit -> SetScore(digits[1]);
        HundredDigit ->SetScore(digits[2]);
        TenDigit -> SetScore(digits[3]);
        UnitDigit -> SetScore(digits[4]);
    }

    void NumberInitial(){

        score = 0;

        glm::vec2 Position_TenThousandDigit = m_Transform.translation;
        Position_TenThousandDigit.y = Position_TenThousandDigit.y - 53;
        TenThousandDigit = std::make_shared<Number>();
        TenThousandDigit -> SetPosition(Position_TenThousandDigit);
        TenThousandDigit -> SetImage((RESOURCE_DIR"/Image/Out_Map/0.png"));
        this->AddChild(TenThousandDigit);

        glm::vec2 Position_ThousandDigit = Position_TenThousandDigit;
        Position_ThousandDigit.y = Position_ThousandDigit.y - 28;
        ThousandDigit = std::make_shared<Number>();
        ThousandDigit -> SetPosition(Position_ThousandDigit);
        ThousandDigit -> SetImage((RESOURCE_DIR"/Image/Out_Map/0.png"));
        this->AddChild(ThousandDigit);

        glm::vec2 Position_HundredDigit = Position_ThousandDigit;
        Position_HundredDigit.y = Position_HundredDigit.y - 28;
        HundredDigit = std::make_shared<Number>();
        HundredDigit -> SetPosition(Position_HundredDigit);
        HundredDigit -> SetImage((RESOURCE_DIR"/Image/Out_Map/0.png"));
        this->AddChild(HundredDigit);

        glm::vec2 Position_TenDigit = Position_HundredDigit;
        Position_TenDigit.y = Position_TenDigit.y - 28;
        TenDigit = std::make_shared<Number>();
        TenDigit -> SetPosition(Position_TenDigit);
        TenDigit -> SetImage((RESOURCE_DIR"/Image/Out_Map/0.png"));
        this->AddChild(TenDigit);

        glm::vec2 Position_UnitDigit = Position_TenDigit;
        Position_UnitDigit.y = Position_UnitDigit.y - 28;
        UnitDigit = std::make_shared<Number>();
        UnitDigit -> SetPosition(Position_UnitDigit);
        UnitDigit -> SetImage((RESOURCE_DIR"/Image/Out_Map/0.png"));
        this->AddChild(UnitDigit);

    }

    std::vector<int> splitDigits(int input) {
        std::vector<int> digits;

        // 将输入的数字逐位拆解并存储到数组中
        while (input > 0) {
            // 取出最低位的数字
            int digit = input % 10;
            // 将数字存入数组
            digits.push_back(digit);
            // 去掉最低位的数字
            input /= 10;
        }

        // 如果数组长度不足五位，则填充零
        while (digits.size() < 5) {
            digits.push_back(0);
        }

        // 反转数组，使得数组中的数字按照从高位到低位的顺序排列
        std::reverse(digits.begin(), digits.end());

        return digits;
    }

private:

    int score;

    std::shared_ptr<Number> UnitDigit, TenDigit, HundredDigit, ThousandDigit, TenThousandDigit;

};

#endif //REPLACE_WITH_YOUR_PROJECT_NAME_SCORE_HPP
