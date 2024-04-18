#ifndef REPLACE_WITH_YOUR_PROJECT_NAME_BLOCK_HPP
#define REPLACE_WITH_YOUR_PROJECT_NAME_BLOCK_HPP

#include <string>
#include <map>

#include "Util/GameObject.hpp"

class Block : public Util::GameObject {
public:
    explicit Block(int block_code_number);

    [[nodiscard]] const std::string &GetImagePath() const { return imagePath; }

    [[nodiscard]] const glm::vec2 &GetPosition() const { return m_Transform.translation; }

    [[nodiscard]] bool GetVisibility() const { return m_Visible; }

    void SetImage(const std::string &ImagePath);

    void SetPosition(const glm::vec2 &Position) { m_Transform.translation = Position; };

    std::string GetName() { return name; }

    void SetName(const std::string name) { this->name = name; }

    [[nodiscard]] int GetBlockNumber() const { return blockNumber; }

private:
    std::string name;
    int blockNumber;
    std::map<int, std::string> Mapper;
    std::string imagePath;

};

#endif //REPLACE_WITH_YOUR_PROJECT_NAME_BLOCK_HPP
