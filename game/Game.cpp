#include "Game.h"

#include <iostream>
#include <ostream>

void Game::handleEvent(const Event& event) {
    std::cout << (event.getType() == EventType::MouseEvent) << std::endl;
}

Game::Game() = default;

Game::~Game() = default;


