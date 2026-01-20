#ifndef RECORDER
#define RECORDER

#include <opencv2/opencv.hpp>
#include <deque>
#include <glm/glm.hpp>

class Recorder {
    public:
        static Recorder* get_instance();

        // Should not be cloneable
        Recorder(Recorder& other) = delete;

        // Should not be assignable
        void operator=(const Recorder&) = delete;

        void start();
        void update();
        cv::Mat get_frame();
        cv::Rect get_face();
        bool use_detection();
        void toggle();

        // Getters
        float get_x_delta();
        float get_y_delta();
        float get_z_delta();
        glm::vec3 get_speed();
        void reset_deltas();

    private:
        Recorder();
        static Recorder* instance;

        bool detection = true;
        cv::VideoCapture cap;
        cv::Mat frame;
        cv::CascadeClassifier face_cascade;
        cv::Rect face;
        cv::CascadeClassifier eye_cascade;
        
        bool first = true;
        cv::Point3f previous;
        cv::Point3f delta;
        std::deque<cv::Point3f> previous_deltas;

        // Parallax configuration variables (these were found to be best)
        cv::Point3f small_delta = cv::Point3f(0.000007, 0.000009, 0.0000352);
        cv::Point3f small_average_direction = cv::Point3f(0.0000303, 0.0000303, 0.0000115);
        int n_previous = 10;

        glm::vec3 speed = glm::vec3(0.0, 0.0, 0.0);

        void update_frame();
        void update_face();
        cv::Point3f get_average_direction();
};

#endif