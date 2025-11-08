#ifndef DETECTION
#define DETECTION

#include <opencv2/opencv.hpp>

extern cv::VideoCapture cap;
extern cv::CascadeClassifier face_cascade;
extern cv::CascadeClassifier eye_cascade;
bool detect_and_show();

#endif