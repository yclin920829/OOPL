#ifndef REPLACE_WITH_YOUR_PROJECT_NAME_SCORE_HPP
#define REPLACE_WITH_YOUR_PROJECT_NAME_SCORE_HPP

#include "Util/GameObject.hpp"
#include "score/Number.hpp"
#include <vector>

class Score : public Util::GameObject {
public:
    explicit Score(const glm::vec2& Position) {
        m_Transform.translation = Position;
        digits.resize(5);
        for (int i = 0; i < digits.size(); ++i) {
            digits[i] = std::make_shared<Number>();
            digits[i]->SetPosition({GetPosition().x, GetPosition().y - float(i + 1) * 28 - 25});
            digits[i]->SetImage((RESOURCE_DIR"/Image/Out_Map/0.png"));
            this->AddChild(digits[i]);
        }
    };

    void SetImage(const std::string& ImagePath){
        m_Drawable = std::make_shared<Util::Image>(ImagePath);
    };

    [[nodiscard]] const glm::vec2& GetPosition() const { return m_Transform.translation; }

    void SetScore(int score){
        std::vector<int> nums(5, 0);

        for (int i = 4; i >= 0 && score > 0; i--) {
            nums[i] = score % 10;
            score /= 10;
            digits.at(i) -> SetScore(nums[i]);
        }
    };

private:
    std::vector<std::shared_ptr<Number>> digits;
};

#endif //REPLACE_WITH_YOUR_PROJECT_NAME_SCORE_HPP
