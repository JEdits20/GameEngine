#ifndef GAME_H
#define GAME_H
#include "Event.h"

class Game {
  public:
    static Game& getInstance() {
      static Game instance;
      return instance;
    }
    ~Game();
    void handleEvent(const Event& event);
  private:
    Game();
};

#endif //GAME_H
