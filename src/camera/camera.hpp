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
        glm::vec3 get_camera_position();
        glm::vec3 get_camera_target();
        float get_speed();

        void move(float x, float y, float z);
        void change_angle_x(float degree);
        void change_angle_y(float degree);
        void change_angle_z(float degree);

    private:
        const float speed = 0.02;
        glm::vec3 cameraPosition;
        glm::vec3 cameraViewOffset;
};

#endif