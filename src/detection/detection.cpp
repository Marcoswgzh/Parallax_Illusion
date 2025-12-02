#include <iostream>
#include <opencv2/opencv.hpp>

cv::VideoCapture cap;
cv::CascadeClassifier face_cascade;
cv::CascadeClassifier eye_cascade;

bool detect_and_show() {
    // Convert OpenCV path predefined macro to string
    std::string haarcascade_dir(HAARCASCADE_DIR);

    // Load face haarcascade classifier
    if (!face_cascade.load(haarcascade_dir + "haarcascade_frontalface_default.xml")) {
        std::cerr << "Error loading Haar cascade file." << std::endl;
        return false;
    }

    // Load eye haarcascade classifier
    if (!eye_cascade.load(haarcascade_dir + "haarcascade_eye_tree_eyeglasses.xml")) {
        std::cerr << "Error loading Haar cascade file." << std::endl;
        // exit(EXIT_FAILURE);
        return false;
    }

    // Open the camera
    cap.open(0);
    if (!cap.isOpened()) {
        std::cerr << "Error: Could not open camera" << std::endl;
        // exit(EXIT_FAILURE);
        return false;
    }

    cap.set(cv::CAP_PROP_FRAME_WIDTH, 640);
    cap.set(cv::CAP_PROP_FRAME_HEIGHT, 480);

    return true;
}