#include "button.hpp"
#include "mouse.hpp"
#include "window_manager.hpp"
#include <iostream>

static Button* active_button = nullptr;

Button::Button (Frame& frame, int x, int y, int width, int height, const cv::Scalar& color)
    : Frame(frame.getX() + x, frame.getY() + y, width, height, color),
    parent_frame(frame),
    local_x(x),
    local_y(y),
    local_width(width),
    local_height(height),
    local_color(color)
{
    active_button = this;
}

void Button::mouseButtonCallback(GLFWwindow* window, int button, int action, int mods){
    if(button != GLFW_MOUSE_BUTTON_LEFT || action != GLFW_PRESS)
        return;

    if(!active_button)
        return;
    
    Mouse* mouse = Mouse::get_instance();

    cv::Point click_point(
        static_cast<int>(mouse->get_x()),
        static_cast<int>(mouse->get_y())
    );

    if(active_button->getVisual().contains(click_point)){
        std::cout<<"Button clicked" << std:endl;

        // action
    }
}