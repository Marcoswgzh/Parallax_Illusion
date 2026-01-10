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

int Frame::getHeight() const {
    return height;
}

cv::Rect Frame::getVisual() const {
    return visual; 
}

cv::Scalar Frame:getColor() const{
    return color;
}
