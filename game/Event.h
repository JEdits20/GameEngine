#ifndef EVENT_H
#define EVENT_H

enum class EventType {
  KeyEvent,
  QuitEvent,
  MouseEvent
};

class Event {
public:
  virtual ~Event() = default;
  virtual EventType getType() const = 0;
};

class KeyPressEvent : public Event {
  public:
    explicit KeyPressEvent(int key) : key(key) {}
    [[nodiscard]] EventType getType() const override {
        return EventType::KeyEvent;
    }
  private:
    int key;
};

class QuitEvent : public Event {
  public:
    QuitEvent() = default;
    [[nodiscard]] EventType getType() const override {
        return EventType::QuitEvent;
    }
};

class MouseClickEvent : public Event {
  public:
    MouseClickEvent(int x, int y) : x(x), y(y) {}
    [[nodiscard]] EventType getType() const override {
        return EventType::MouseEvent;
    }
  private:
    int x, y;
};
#endif // EVENT_H