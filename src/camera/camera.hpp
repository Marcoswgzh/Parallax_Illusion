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
        Gaze compute_gaze_from_face(cv::Rect face, int columns, int rows);
        float interpolate(float a, float b, float t);
        void view();
        void update_position_from_face(const Gaze& gaze, float faceWidth);

    private:
        glm::vec3 cameraPosition;
        const glm::vec3 cameraUp = glm::vec3(0, 1, 0);  

        const float MOVEMENT_SCALE_X = 2.75f; // These two can be lowered
        const float MOVEMENT_SCALE_Y = 1.75f; // if you feel the figure moves too fast
        const float REFERENCE_FACE_WIDTH = 120.0f;
        const float DEPTH_SENSITIVITY = 0.02f;

        const float SMOOTHING_FACTOR = 0.15f;
        const glm::vec3 CENTER_POSITION = glm::vec3(0.0f, 0.7f, -2.5f);
};

#endif