#ifndef REPLACE_WITH_YOUR_PROJECT_NAME_GHOSTSTATE_HPP
#define REPLACE_WITH_YOUR_PROJECT_NAME_GHOSTSTATE_HPP

#include "Util/Animation.hpp"

class GhostState {
public:
    GhostState() = default;

    virtual void GetState() = 0;

    void SetUpImages(const std::vector<std::string> &AnimationPaths) {
        UP = std::make_shared<Util::Animation>(AnimationPaths, true, 300, true, 0);
    }

    void SetDownImages(const std::vector<std::string> &AnimationPaths) {
        DOWN = std::make_shared<Util::Animation>(AnimationPaths, true, 300, true, 0);
    }

    void SetRightImages(const std::vector<std::string> &AnimationPaths) {
        RIGHT = std::make_shared<Util::Animation>(AnimationPaths, true, 300, true, 0);
    }

    void SetLeftImages(const std::vector<std::string> &AnimationPaths) {
        LEFT = std::make_shared<Util::Animation>(AnimationPaths, true, 300, true, 0);
    }

    const std::shared_ptr<Core::Drawable> &GetUpImages() const {
        return UP;
    }

    const std::shared_ptr<Core::Drawable> &GetDownImages() const {
        return DOWN;
    }

    const std::shared_ptr<Core::Drawable> &GetRightImages() const {
        return RIGHT;
    }

    const std::shared_ptr<Core::Drawable> &GetLeftImages() const {
        return LEFT;
    }

private:
    std::shared_ptr<Core::Drawable> UP;
    std::shared_ptr<Core::Drawable> DOWN;
    std::shared_ptr<Core::Drawable> RIGHT;
    std::shared_ptr<Core::Drawable> LEFT;
};

#endif //REPLACE_WITH_YOUR_PROJECT_NAME_GHOSTSTATE_HPP