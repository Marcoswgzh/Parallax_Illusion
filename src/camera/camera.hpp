#ifndef CAMERA
#define CAMERA

#include <glm/glm.hpp>
#include <opencv2/opencv.hpp>

struct Gaze {
    float x = 0.f;
    float y = 0.f;
};

class Camera {
    public:
        Camera();
        void update();

        Gaze compute_gaze_from_face(cv::Rect face, int columns, int rows);
        void update_position_from_face(const Gaze& gaze, float faceWidth);
        float interpolate(float a, float b, float t);

        void view();
        void update_mouse_view();

        void move_forward();
        void move_backward();
        void move_left();
        void move_right();
        void move_up();
        void move_down();

        glm::vec3 get_camera_position();

    private:
        void process_input();

        const float speed = 2.0f;
        const float sensitivity = 0.1f;

        float get_speed();
        float get_sensitivity();

        float yaw = 90.0f;
        float pitch = 0.0f;

        glm::vec3 camera_position;
        glm::vec3 camera_front;

        const glm::vec3 camera_up = glm::vec3(0, 1, 0);  

        const float MOVEMENT_SCALE_X = 2.75f; // These two can be lowered
        const float MOVEMENT_SCALE_Y = 1.75f; // if you feel the figure moves too fast
        const float REFERENCE_FACE_WIDTH = 120.0f;
        const float DEPTH_SENSITIVITY = 0.02f;

        const float SMOOTHING_FACTOR = 0.15f;
        const glm::vec3 CENTER_POSITION = glm::vec3(0.0f, 0.7f, -3.0f);
};

#endif