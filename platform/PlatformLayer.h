#ifndef PLATFORM_LAYER_H
#define PLATFORM_LAYER_H

#include <memory>
#include <vector>
#include "../game/Event.h"
#include "SPSCQueue.h"

class PlatformLayer{
public:
  virtual ~PlatformLayer() = default;

  virtual void createWindow(const char* title, int minWidth, int minHeight, int width, int height) = 0;
  virtual std::unique_ptr<Event> handleInput() = 0;
  virtual void render() = 0;
  virtual void shutdown() = 0;
  virtual void drawRectangle(int x, int y, int width, int height) = 0;
protected:
  PlatformLayer() = default;
  std::atomic_bool isRunning = false;
  SingleProducerSingleConsumerQueue<Event, 128> eventQueue;
};

#endif // PLATFORM_LAYER_H