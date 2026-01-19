#ifndef MENU
#define MENU

#include "container.hpp"

#include <optional>

class Menu {
    public:
        static Menu* get_instance();

        // Menu should not be cloneable
        Menu(Menu& other) = delete;

        // Menu should not be assignable
        void operator=(const Menu&) = delete;
        
        void handle_click_events(glm::vec2 position);

        void toggle();
        bool should_display();

    private:
        Menu();
        static Menu* instance;

        bool display = true;

        // Create menu container
        glm::vec3 container_color = glm::vec3(0.234, 0.246, 0.340);
        Container container = Container(std::nullopt, glm::vec2(-1.0), glm::vec2(2.0), container_color);

        // Menu text
        Texture menu_texture = Texture("textures/menu.png");
        Frame menu_title = Frame(glm::vec2(-0.5, 0.4), glm::vec2(1.0, 0.314), menu_texture, 1);

        // Create menu scene buttons
        glm::vec3 button_color = glm::vec3(0.164, 0.172, 0.238);
        Texture texture = Texture("textures/apple_skin.png");
        Button scene_1_button = Button(container, glm::vec2(0.2, 0.6), glm::vec2(0.4), texture);
        Button scene_2_button = Button(container, glm::vec2(0.8, 0.6), glm::vec2(0.4), button_color);
        Button scene_3_button = Button(container, glm::vec2(1.4, 0.6), glm::vec2(0.4), button_color);
};

#endif