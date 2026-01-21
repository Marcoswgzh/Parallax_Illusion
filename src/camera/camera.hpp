#ifndef CAMERA
#define CAMERA

#include <glm/glm.hpp>
#include <opencv2/opencv.hpp>

class Camera {
    public:
        Camera();

        // General
        void reset();
        void update();

        // Move methods
        void move_forward();
        void move_backward();
        void move_left();
        void move_right();
        void move_up();
        void move_down();

        // Toggles
        void toggle_key_movement();
        void toggle_movement();  

        // Getters
        glm::vec3 get_camera_position();

    private:
        // General
        void process_input();

        // View methods
        void update_mouse_view();
        void update_recorder_view();
        void set_view();

        // Getters (only to be used privately)
        float get_speed();
        float get_sensitivity();
        
        // Key-based movement constants
        const float speed = 3.0;
        const float sensitivity = 5.0;

        // Camera positioning
        float yaw;
        float pitch;
        glm::vec3 camera_position;
        glm::vec3 camera_front;
        const glm::vec3 camera_up = glm::vec3(0, 1, 0);

        // Toggle states
        bool key_movement = false;
        bool movement = false;
};

#endif