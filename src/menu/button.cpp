#include "button.hpp"

std::vector<float> createButtonVertices(float x, float y){
    const float buttonWidth=0.16f; 
    const float buttonHeight=0.12f;
    const float gray=0.4f;
    return {
        x, y, gray, gray, gray,  x + buttonWidth, y, gray, gray, gray, x, y - buttonHeight, gray, gray, gray,
        x + buttonWidth, y, gray, gray, gray,  x + buttonWidth, y - buttonHeight, gray, gray, gray,  x, y - buttonHeight, gray, gray, gray,
    };
}