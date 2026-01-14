#ifndef BUTTON
#define BUTTON

#include "frame.hpp"
#include <opencv2/core.hpp>
#include <vector>
#include "../mouse.hpp"

class Button : public Frame {
private:
    Frame& parentFrame;
    int localX;
    int localY;
    int localWidth;
    int localHeight;
    cv::Scalar localColor;

    public:
    //constructor
    Button(Frame& frame, int x, int y, int width, int height, const cv::Scalar& color);

    static void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods);

    //checks if the mouse is in the area
    bool contains(float cx, float cy) const;
};

#endif