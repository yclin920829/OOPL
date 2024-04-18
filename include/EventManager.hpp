#ifndef EVENT_MANAGER_HPP
#define EVENT_MANAGER_HPP

#include <iostream>
#include <unordered_map>
#include <vector>
#include <functional>
#include "EventType.hpp"
#include "EventData.hpp"

// 定义事件类型
using EventType = int;

// 定义事件监听器类型
using EventListener = std::function<void(EventType, const EventData&)>;


// 事件管理器类
class EventManager {
public:
    explicit EventManager(){};
private:
    std::unordered_map<EventType, std::vector<EventListener>> listeners;

public:
    // 添加监听器
    void addListener(EventType eventType, const EventListener& listener);

    // 移除监听器
    void removeListener(EventType eventType, const EventListener& listener);

    // 通知监听器
    void notify(EventType eventType, const EventData& eventData);
};

#endif
