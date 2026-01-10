#ifndef BUTTON
#define BUTTON

#include "frame.hpp"
#include <GLFW/glfw3.h>

class Button: public Frame{
    private: Frame& parentFrame; int localX; int localY; int localWidth; int localHeight; cv::Scalar localColor;
    public: Button(Frame& frame, int x, int y, int width, int height, const cv::Scalar& color);

    static void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods);
};

#endif