#ifndef EVENTDATA_HPP
#define EVENTDATA_HPP

class EventData {
public:
    int quantity;
};

class CollisionEventData : public EventData {
public:
    int damage;
};

class CollisionToAddEventData : public EventData {};

#endif // EVENTDATA_HPP
