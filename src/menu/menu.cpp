#include "menu.hpp"

Menu::Menu(int x, int y, int width, int height, const cv::Scalar& color)
: Frame(x, y, width, height, color) {}

void Menu::add_button(Button* button){
    buttons.push_back(button);
}

const std::vector<Button*>& Menu::get_buttons() const{
    return buttons;
}