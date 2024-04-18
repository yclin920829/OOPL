#include <iostream>
#include <unordered_map>
#include <vector>
#include <functional>
#include "EventManager.hpp"



// 添加监听器
void EventManager::addListener(EventType eventType, const EventListener &listener) {
    listeners[eventType].push_back(listener);
}

// 移除监听器
void EventManager::removeListener(EventType eventType, const EventListener& listener) {
    auto& eventListeners = listeners[eventType];
    auto it = std::find_if(eventListeners.begin(), eventListeners.end(), [&listener](const EventListener& func) {
        // 使用 Lambda 表达式自定义比较操作
        return func.target<void(int, const EventData&)>() == listener.target<void(int, const EventData&)>();
    });
    if (it != eventListeners.end()) {
        eventListeners.erase(it);
    }
}

// 通知监听器，eventType決定哪種event，EventData可以決定量
void EventManager::notify(EventType eventType, const EventData& eventData) {
    auto& eventListeners = listeners[eventType];
    for (const auto& listener : eventListeners) {
        listener(eventType, eventData);
    }
}


