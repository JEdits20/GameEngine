//
// Created by Laplace on 10.07.2025.
//

#include "Clickable.h"

void Clickable::onClick() {
    buttonClicked++;
}

void Clickable::onHover(bool active) {
    this->hovered = active;
}

void Clickable::draw() override {

}


