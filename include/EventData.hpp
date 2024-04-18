#ifndef EVENTDATA_HPP
#define EVENTDATA_HPP

// 基类，表示事件数据
class EventData {
public:
    virtual ~EventData() {} // 基类的虚析构函数
    int quantity;
};

// 派生类，表示特定类型的事件数据
class CollisionEventData : public EventData {
public:
    int damage;
    // 其他成员...
};

class CollisionToAddEventData : public EventData {
public:
    // 其他成员...
};

#endif // EVENTDATA_HPP
