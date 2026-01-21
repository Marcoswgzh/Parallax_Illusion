#ifndef RECORDER
#define RECORDER

#include <opencv2/opencv.hpp>
#include <deque>
#include <glm/glm.hpp>

class Recorder {
    public:
        static Recorder* get_instance();

        // Recorder should not be cloneable
        Recorder(Recorder& other) = delete;

        // Recorder should not be assignable
        void operator=(const Recorder&) = delete;

        // General
        void start();
        void update();
        void reset_deltas();

        // Getters
        float get_x_delta();
        float get_y_delta();
        float get_z_delta();
        glm::vec3 get_speed();
        
    private:
        Recorder();
        static Recorder* instance;

        // General
        void update_frame();
        void update_face();

        // Private getter
        cv::Point3f get_average_direction();

        // Opencv captures
        cv::VideoCapture capture;
        cv::Mat frame;
        cv::CascadeClassifier face_cascade;
        cv::Rect face;
        
        // Tracks if it is the first recorder frame
        bool first = true;

        // Contains the previous detected face position
        cv::Point3f previous;

        // Difference between current and previous face position
        cv::Point3f delta;

        // A queue of previous deltas to calculate average direction
        std::deque<cv::Point3f> previous_deltas;

        // Parallax configuration variables (these were found to be best)
        cv::Point3f small_delta = cv::Point3f(0.000007, 0.000009, 0.0000352);
        cv::Point3f small_average_direction = cv::Point3f(0.0000303, 0.0000303, 0.0000115);
        int n_previous = 10;

        // Speed determinded by deltas
        glm::vec3 speed = glm::vec3(0.0, 0.0, 0.0);
};

#endif