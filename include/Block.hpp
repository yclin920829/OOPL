#ifndef REPLACE_WITH_YOUR_PROJECT_NAME_BLOCK_HPP
#define REPLACE_WITH_YOUR_PROJECT_NAME_BLOCK_HPP

#include <string>
#include <map>

#include "Util/GameObject.hpp"

class Block : public Util::GameObject {
public:
    explicit Block(int block_code_number);

    Block(const Block&) = delete;

    Block(Block&&) = delete;

    Block& operator=(const Block&) = delete;

    Block& operator=(Block&&) = delete;

    [[nodiscard]] const std::string& GetImagePath() const { return m_ImagePath; }

    [[nodiscard]] const glm::vec2& GetPosition() const { return m_Transform.translation; }

    [[nodiscard]] bool GetVisibility() const { return m_Visible; }

    int GetBlockNumber();

    void SetImage(const std::string& ImagePath);

    void SetPosition(const glm::vec2& Position) { m_Transform.translation = Position; };

private:
    //void ResetPosition() { m_Transform.translation = {0, 0}; }

    int map_code_number;
    std::map<int, std::string> Mapper;

    std::string m_ImagePath;
};

#endif //REPLACE_WITH_YOUR_PROJECT_NAME_BLOCK_HPP
