#include "button.hpp"

std::vector<float> createButtonVertices(float x, float y, float r, float g, float b){
    const float buttonWidth=0.16f; 
    const float buttonHeight=0.12f;
    return {
        x, y, r, g, b,  x + buttonWidth, y, r, g, b, x, y - buttonHeight, r, g, b,
        x + buttonWidth, y, r, g, b,  x + buttonWidth, y - buttonHeight, r, g, b,  x, y - buttonHeight, r, g, b,
    };
}

bool Button::contains(float cx, float cy){
    return cx >= x && cx <= x + width && cy <= y && cy >= y - height; //cursor is inside the coordinates of the button
}