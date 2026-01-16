#ifndef BUTTON
#define BUTTON

#include <vector>

std::vector<float> createButtonVertices(float x, float y, float r, float g, float b);
class Button
{   
    public:
        float x, y;
        float r, g ,b;
        float width;
        float height;
        bool contains(float cx, float cy);  
};

#endif
