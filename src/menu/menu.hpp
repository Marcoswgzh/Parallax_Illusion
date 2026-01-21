#ifndef MENU
#define MENU

#include <optional>

#include "container.hpp"

class Menu {
    public:
        static Menu* get_instance();

        // Menu should not be cloneable
        Menu(Menu& other) = delete;

        // Menu should not be assignable
        void operator=(const Menu&) = delete;
        
        void handle_click_events(glm::vec2 position);

        // Toggle
        void toggle();

        // Getter
        bool should_display();

    private:
        Menu();
        static Menu* instance;

        // Create menu container
        glm::vec3 container_color = glm::vec3(0.234, 0.246, 0.340);
        Container container = Container(std::nullopt, glm::vec2(-1.0), glm::vec2(2.0), container_color);

        // Menu text
        Texture menu_texture = Texture("textures/menu.png");
        Frame menu_title = Frame(glm::vec2(-0.5, 0.4), glm::vec2(1.0, 0.314), menu_texture, 1);

        // Create menu scene buttons
        Texture stars_texture = Texture("textures/stars.jpg");
        Texture nature_texture = Texture("textures/nature.jpg");
        Texture table_texture = Texture("textures/table.jpg");
        Button scene_1_button = Button(container, glm::vec2(0.2, 0.6), glm::vec2(0.4), stars_texture);
        Button scene_2_button = Button(container, glm::vec2(0.8, 0.6), glm::vec2(0.4), nature_texture);
        Button scene_3_button = Button(container, glm::vec2(1.4, 0.6), glm::vec2(0.4), table_texture);

        // Toggle state
        bool display = true;
};

#endif
