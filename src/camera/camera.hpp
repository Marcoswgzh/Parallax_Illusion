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
        Gaze compute_gaze_from_facial(cv::Rect face, int columns, int rows);
        void update_camera_gaze(const Gaze& gaze, float gazeScaleX, float gazeScaleY, float smoothing);
        float interpolate(float a, float b, float t);
        void view();

        void move_forward();
        void move_backward();
        void move_left();
        void move_right();
        void move_up();
        void move_down();

        void change_angle_x(float degree);
        void change_angle_y(float degree);
        void change_angle_z(float degree);

    private:
        const float speed = 0.02;
        glm::vec3 cameraPosition;
        glm::vec3 cameraFront;
        const glm::vec3 cameraUp = glm::vec3(0, 1, 0);  // This will stay the same
};

#endif