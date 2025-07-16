//
// Created by Laplace on 10.07.2025.
//

#ifndef DRAWABLE_H
#define DRAWABLE_H


class PlatformLayer;

class Drawable {
public:
    virtual ~Drawable() = default;
    virtual void draw(const PlatformLayer &platform);

    void setPosition(int x, int y);

    int x = 0,y = 0;
};



#endif //DRAWABLE_H
