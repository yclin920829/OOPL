#ifndef REPLACE_WITH_YOUR_PROJECT_NAME_BLOCK_HPP
#define REPLACE_WITH_YOUR_PROJECT_NAME_BLOCK_HPP

#include "Util/GameObject.hpp"

class Block : public Util::GameObject {
public:
    explicit Block(std::string blockName, int codeNumber, int positionInVectorX, int positionInVectorY) : name(std::move(blockName)), codeNumber(codeNumber) {
        SetImage(RESOURCE_DIR"/Image/Map_Blocks/" + this->name + ".png");
        m_Transform.translation = {0, 0};
        positionInVector = {positionInVectorX, positionInVectorY};
    }

    explicit Block(const std::vector<std::string> blockNames, int codeNumber, int positionInVectorX, int positionInVectorY) : name(std::move(blockNames[0])), codeNumber(codeNumber) {
        std::shared_ptr<Core::Drawable> DEAD = std::make_shared<Util::Animation>(
            std::vector<std::string>{RESOURCE_DIR"/Image/Map_Blocks/" + blockNames.at(0) + ".png" , RESOURCE_DIR"/Image/Map_Blocks/" + blockNames.at(1) + ".png"},
            true, 400, true, 0);
        SetDrawable(DEAD);
        m_Transform.translation = {0, 0};
        positionInVector = {positionInVectorX, positionInVectorY};
    }

    [[nodiscard]] const std::string &GetImagePath() const { return imagePath; }

    [[nodiscard]] const glm::vec2 &GetPosition() const { return m_Transform.translation; }

    [[nodiscard]] bool GetVisibility() const { return m_Visible; }

    void SetImage(const std::string &ImagePath) {
        imagePath = ImagePath;
        m_Drawable = std::make_shared<Util::Image>(imagePath);
    };

    void SetPosition(const glm::vec2 &Position) { m_Transform.translation = Position; };

    std::string GetName() { return name; }

    void SetName(const std::string name) { this->name = name; }

    [[nodiscard]] int GetCodeNumber() const { return codeNumber; }

    const glm::vec2 &getPositionInVector() const {
        return positionInVector;
    }

private:
    std::string name;
    int codeNumber;
    std::string imagePath;
    glm::vec2 positionInVector = {0, 0};

};

#endif //REPLACE_WITH_YOUR_PROJECT_NAME_BLOCK_HPP
