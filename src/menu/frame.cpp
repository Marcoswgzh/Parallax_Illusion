#include "frame.hpp"

Frame::Frame(int x, int y, int width, int height, const cv::Scalar& color) {
    this->x = x;
    this->y = y;
    this->width = width;
    this->height = height;
    this->color = color;
    this->visual = cv::Rect(x, y, width, height);
}

//getter methods
int Frame::getX() const {
    return x;
}
int Frame::getY() const {
    return y;
}
int Frame::getWidth() const { 
    return width;
}
int Frame::getHeight() const {
    return height;
}
cv::Rect Frame::getVisual() const {
    return visual; 
}
cv::Scalar Frame::getColor() const{
    return color;
}

std::vector<float> Frame::getVertices() const {
    float x1 = static_cast<float>(x);
    float y1 = static_cast<float>(y);
    float x2 = x1 + static_cast<float>(width);
    float y2 = y1 - static_cast<float>(height);
    
    float color = 0.4f;
    
    return {
        x1,y1,color,color,color,  x2,y1,color,color,color,  x1,y2,color,color,color,
        x2,y1,color,color,color,  x2,y2,color,color,color,  x1,y2,color,color,color
    };
}
