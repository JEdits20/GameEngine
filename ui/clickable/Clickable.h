//
// Created by Laplace on 10.07.2025.
//

#ifndef BUTTON_H
#define BUTTON_H
#include "../Drawable.h"

class Clickable : public Drawable {
public:
    ~Clickable() override = default;

    Clickable() = default;
    bool enabled = true;
    bool hovered = false;
    int buttonClicked = 0;
    void onClick();
    void draw() override;
    void onHover(bool active);
};



#endif //BUTTON_H
