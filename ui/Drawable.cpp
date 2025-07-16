//
// Created by Laplace on 10.07.2025.
//

#include "Drawable.h"

#include "../platform/PlatformLayer.h"

class PlatformLayer;

void Drawable::draw(const PlatformLayer &platform) {
    platform.drawRectangle(10,10,10,10);
}

void Drawable::setPosition(int x, int y) {
    this->x = x;
    this->y = y;
}