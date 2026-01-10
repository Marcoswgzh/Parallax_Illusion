#ifndef FRAME
#define FRAME

#include <opencv2/opencv.hpp>

class Frame { 
    private: int x; int y; int width; int height; cv::Scalar color; cv::Rect visual;
    public: 
    //frame constructor
    Frame(int x, int y, int width, int height, const cv::Scalar& color);

    //getter methods
    int getX() const;
    int getY() const;
    int getWidth() const; 
    int getHeight() const;
    cv::Rect getVisual() const;
    cv::Scalar getColor() const;
};

#endif