#ifndef EVENT_MANAGER_HPP
#define EVENT_MANAGER_HPP

#include <map>
#include <functional>

#include "EventType.hpp"
#include "EventData.hpp"

using EventType = int;
using EventListener = std::function<void(EventType, const EventData&)>;

class EventManager {
public:
    explicit EventManager() = default;

    void addListener(EventType eventType, const EventListener& listener){
        listeners[eventType].push_back(listener);
    };

    void notify(EventType eventType, const EventData& eventData){
        auto& eventListeners = listeners[eventType];
        for (const auto& listener : eventListeners) {
            listener(eventType, eventData);
        }
    };

private:
    std::map<EventType, std::vector<EventListener>> listeners;
};

#endif
