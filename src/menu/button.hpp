#ifndef BUTTON
#define BUTTON

#include <vector>

std::vector<float> createButtonVertices(float x, float y);
class Button
{   
    public:
        float x, y;
        float width;
        float height;
        bool contains(float cx, float cy);  
};

#endif
