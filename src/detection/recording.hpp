#ifndef RECORDER
#define RECORDER

#include <opencv2/opencv.hpp>

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

    private:
        Recorder();

        static Recorder* instance;

        bool detection = true;
        cv::VideoCapture cap;
        cv::Mat frame;
        cv::CascadeClassifier face_cascade;
        cv::Rect face;
        cv::CascadeClassifier eye_cascade;

        void update_frame();
        void update_face();
};

#endif