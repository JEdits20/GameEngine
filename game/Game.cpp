#include "Game.h"

#include <iostream>
#include <memory>
#include <ostream>

void Game::handleEvent(const std::unique_ptr<Event>& eventPtr) {
    if ((eventPtr->getType() == EventType::MouseEvent)) {
        exit(1);
    }
    std::cout << (eventPtr->getType() == EventType::MouseEvent) << std::endl;
}
void Game::update() {

}

Game::Game() = default;

Game::~Game() = default;


