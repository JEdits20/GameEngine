//
// Created by Laplace on 10.07.2025.
//

#ifndef TEXTBOX_H
#define TEXTBOX_H
#include "../Drawable.h"
#include <string>
inline extern bool boxed = false;

class TextBox : public Drawable {
public:
    std::string text;
    void setBoxed();
};



#endif //TEXTBOX_H
