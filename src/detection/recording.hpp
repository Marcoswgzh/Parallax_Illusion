#ifndef RECORDER
#define RECORDER

#include <opencv2/opencv.hpp>

class Recorder {
    public:
        Recorder();
        void start();
        void update();
        cv::Mat get_frame();
        cv::Rect get_face();
        bool use_detection();
        void toggle();

    private:
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