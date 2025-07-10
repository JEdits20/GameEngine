// PlatformLayer.h
#ifndef PLATFORM_LAYER_H
#define PLATFORM_LAYER_H

#include <vector>
#include "../game/Event.h"
#include "Singelton.h"

class PlatformLayer : public Singleton<PlatformLayer> {
public:
  virtual ~PlatformLayer() = default;

  virtual void createWindow(const char* title, int minWidth, int minHeight, int width, int height) = 0;
  virtual std::vector<Event*>& handleInput() = 0;
  virtual void render() = 0;
  virtual void shutdown() = 0;
  virtual void drawRectangle(int x, int y, int width, int height) = 0;
protected:
  bool isRunning = false;
  std::vector<Event*> events;
};

#endif // PLATFORM_LAYER_H
