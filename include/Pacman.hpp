#ifndef REPLACE_WITH_YOUR_PROJECT_NAME_PACMAN_HPP
#define REPLACE_WITH_YOUR_PROJECT_NAME_PACMAN_HPP

#include "Util/GameObject.hpp"
#include "Util/Animation.hpp"
#include "Block.hpp"
#include "ghost/Ghost.hpp"
#include "event/EventManager.hpp"
#include "fruit/Fruit.hpp"

class Pacman : public Util::GameObject {
public:
    explicit Pacman() {
        SetZIndex(20);
        SetVisible(true);
        dead= false;
    };

    void AddEventManager(EventManager *eventManager){
        this->eventManager = eventManager;
    }

    enum Direction { up, down, right, left, none };

    void HandleCollision(int damage = 1){
        CollisionEventData eventData{};
        eventData.damage = damage;
        eventManager->notify(COLLISION_WITH_GHOST_EVENT_NOT_INVINCIBLE, eventData);
    }//處理扣血

    void HandleScoreUpCollision(int score =  15){
        CollisionToAddEventData eventData;
        eventData.quantity = score;
        eventManager->notify(COLLISION_TO_ADD_SCORE, eventData);
    }//處理加分


    void SetUpImages(const std::vector<std::string> &images) {
        UP = std::make_shared<Util::Animation>(images, true, 100, true, 0);
    }

    void SetDownImages(const std::vector<std::string> &images) {
        DOWN = std::make_shared<Util::Animation>(images, true, 100, true, 0);
    }

    void SetRightImages(const std::vector<std::string> &images) {
        RIGHT = std::make_shared<Util::Animation>(images, true, 100, true, 0);
    }

    void SetLeftImages(const std::vector<std::string> &images) {
        LEFT = std::make_shared<Util::Animation>(images, true, 100, true, 0);
    }

    void SetDeadImages(const std::vector<std::string> &images) {
        DEAD = std::make_shared<Util::Animation>(images, true, 400, false, 0);
    }

    void Start() {
        SetDrawable(LEFT);
    }

    void MoveUp() {
        if (dead) return;
        SetDrawable(UP);
        auto position = GetPosition();
        SetPosition({position.x, position.y + 16.0f});
    }

    void MoveDown() {
        if (dead) return;
        SetDrawable(DOWN);
        auto position = GetPosition();
        SetPosition({position.x, position.y - 16.0f});
    }

    void MoveRight() {
        if (dead) return;
        SetDrawable(RIGHT);
        auto position = GetPosition();
        SetPosition({position.x + 16.0f, position.y});
    }

    void MoveLeft() {
        if (dead) return;
        SetDrawable(LEFT);
        auto position = GetPosition();
        SetPosition({position.x - 16.0f, position.y});
    }

    void Move(glm::vec2 &position) {
        SetPosition(position);
    }

    void Dead() {
        SetDrawable(DEAD);
        auto animation = std::dynamic_pointer_cast<Util::Animation>(m_Drawable);
        animation->SetCurrentFrame(0);
        dead = true;
    }

    [[nodiscard]] bool IfAnimationEnds() const {
        auto animation = std::dynamic_pointer_cast<Util::Animation>(m_Drawable);
        return animation->GetCurrentFrameIndex() == animation->GetFrameCount() - 1;
    };

    void ReStart() {
        HandleCollision();
        dead = false;
        SetPosition({-0.0f, -88.0f});
        SetDrawable(LEFT);
    }

    [[nodiscard]] const glm::vec2 &GetPosition() const { return m_Transform.translation; }

    void SetPosition(const glm::vec2 &Position) { m_Transform.translation = Position; }

    [[nodiscard]] bool eatBean(const std::shared_ptr<Block> &bean) const {
        return (GetPosition() == bean->GetPosition());
    }

    [[nodiscard]] bool IsDead() const {
        return dead;
    }

    [[nodiscard]] bool IfCollidesGhost(const std::shared_ptr<Ghost> &other) const {
        float thisHalfWidth = this->GetScaledSize().x / 2;
        float thisHalfHeight = this->GetScaledSize().y / 2;
        float otherHalfWidth = other->GetScaledSize().x / 2;
        float otherHalfHeight = other->GetScaledSize().y / 2;

        float thisMinX = this->GetPosition().x - thisHalfWidth;
        float thisMaxX = this->GetPosition().x + thisHalfWidth;
        float thisMinY = this->GetPosition().y - thisHalfHeight;
        float thisMaxY = this->GetPosition().y + thisHalfHeight;

        float otherMinX = other->GetPosition().x - otherHalfWidth;
        float otherMaxX = other->GetPosition().x + otherHalfWidth;
        float otherMinY = other->GetPosition().y - otherHalfHeight;
        float otherMaxY = other->GetPosition().y + otherHalfHeight;

        bool collisionX = (thisMinX <= otherMaxX) && (thisMaxX >= otherMinX);
        bool collisionY = (thisMinY <= otherMaxY) && (thisMaxY >= otherMinY);

        return collisionX && collisionY;
    }

    [[nodiscard]] bool IsCollidesFruit(const std::shared_ptr<Fruit> &other) const {
        float thisHalfWidth = this->GetScaledSize().x / 2;
        float thisHalfHeight = this->GetScaledSize().y / 2;
        float otherHalfWidth = other->GetScaledSize().x / 2;
        float otherHalfHeight = other->GetScaledSize().y / 2;

        float thisMinX = this->GetPosition().x - thisHalfWidth;
        float thisMaxX = this->GetPosition().x + thisHalfWidth;
        float thisMinY = this->GetPosition().y - thisHalfHeight;
        float thisMaxY = this->GetPosition().y + thisHalfHeight;

        float otherMinX = other->GetPosition().x - otherHalfWidth;
        float otherMaxX = other->GetPosition().x + otherHalfWidth;
        float otherMinY = other->GetPosition().y - otherHalfHeight;
        float otherMaxY = other->GetPosition().y + otherHalfHeight;

        bool collisionX = (thisMinX <= otherMaxX) && (thisMaxX >= otherMinX);
        bool collisionY = (thisMinY <= otherMaxY) && (thisMaxY >= otherMinY);

        return collisionX && collisionY;
    }

    Direction getCurrentDirection() const {
        return currentDirection;
    }

    void setCurrentDirection(Direction currentDirection) {
        Pacman::currentDirection = currentDirection;
    }

    Direction getNextDirection() const {
        return nextDirection;
    }

    void setNextDirection(Direction nextDirection) {
        Pacman::nextDirection = nextDirection;
    }

private:
    EventManager * eventManager{};
    std::shared_ptr<Core::Drawable> UP;
    std::shared_ptr<Core::Drawable> DOWN;
    std::shared_ptr<Core::Drawable> RIGHT;
    std::shared_ptr<Core::Drawable> LEFT;
    std::shared_ptr<Core::Drawable> DEAD;


    Direction currentDirection = left;
    Direction nextDirection = none;

    bool dead;
};

#endif //REPLACE_WITH_YOUR_PROJECT_NAME_PACMAN_HPP
