#ifndef GAZE
#define GAZE

#include <opencv2/opencv.hpp>

struct Gaze {
        float x = 0.f;
        float y = 0.f;
        bool valid = false;
};

Gaze compute_gaze_from_frame(const cv::Mat& frame);

#endif