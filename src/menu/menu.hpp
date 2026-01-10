#ifndef MENU
#define MENU

#include "frame.hpp"
#include "button.hpp"
#include <vector>

class Menu: public Frame{
    private: std::vector<Button*> buttons;
    public: Menu(int x, int y, int width, const cv::Scalar& color);

    void add_button(Button* button);
    const std::vector<Button*>& get_buttons() const;
};

#endif