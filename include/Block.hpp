#ifndef REPLACE_WITH_YOUR_PROJECT_NAME_BLOCK_HPP
#define REPLACE_WITH_YOUR_PROJECT_NAME_BLOCK_HPP

#include "Util/GameObject.hpp"

class Block : public Util::GameObject {
public:
    explicit Block(std::string blockName, int codeNumber) : name(std::move(blockName)), codeNumber(codeNumber) {
        SetImage(RESOURCE_DIR"/Image/Map_Blocks/" + this->name + ".png");
        m_Transform.translation = {0, 0};
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

private:
    std::string name;
    int codeNumber;
    std::string imagePath;

};

#endif //REPLACE_WITH_YOUR_PROJECT_NAME_BLOCK_HPP
