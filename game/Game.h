#ifndef GAME_H
#define GAME_H
#include <memory>

#include "Event.h"

class Game {
  public:
    static Game& getInstance() {
      static Game instance;
      return instance;
    }
    void update();
    ~Game();
    void handleEvent(const std::unique_ptr<Event>& eventPtr);
  private:
    Game();
};

#endif //GAME_H
