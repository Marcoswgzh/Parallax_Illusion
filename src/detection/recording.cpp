#include "recording.hpp"

#include <iostream>
#include <opencv2/opencv.hpp>

Recorder* Recorder::instance = nullptr;

Recorder* Recorder::get_instance() {
    if (instance == nullptr) {
        instance = new Recorder();
    }
    return instance;
}

Recorder::Recorder() {
    // Convert OpenCV path predefined macro to string
    std::string haarcascade_dir(HAARCASCADE_DIR);

    // Load face haarcascade classifier
    if (!this->face_cascade.load(haarcascade_dir + "haarcascade_frontalface_default.xml")) {
        std::cerr << "Error loading Haar cascade file." << std::endl;
        exit(EXIT_FAILURE);
    }

    // Load eye haarcascade classifier
    if (!this->eye_cascade.load(haarcascade_dir + "haarcascade_eye_tree_eyeglasses.xml")) {
        std::cerr << "Error loading Haar cascade file." << std::endl;
        exit(EXIT_FAILURE);
    }
}

void Recorder::start() {
    // Open the camera
    cap.open(0);
    if (!cap.isOpened()) {
        std::cerr << "Error: Could not open camera" << std::endl;
        exit(EXIT_FAILURE);
    }

    cap.set(cv::CAP_PROP_FRAME_WIDTH, 640);
    cap.set(cv::CAP_PROP_FRAME_HEIGHT, 480);
}

void Recorder::update() {
    // Updates must be done in the correct order
    this->update_frame();
    this->update_face();
}

void Recorder::update_frame() {
    cv::Mat temp;
    this->cap >> temp;

    // Don't update frame if frame is empty
    if (!temp.empty()) {
        this->frame = temp;
    }
}

void Recorder::update_face() {
    cv::Mat gray;
    cv::cvtColor(this->frame, gray, cv::COLOR_BGR2GRAY);
    cv::equalizeHist(gray, gray);  // TODO: Check what this does

    std::vector<cv::Rect> faces;
    face_cascade.detectMultiScale(gray, faces, 1.1, 3, 0 | cv::CASCADE_SCALE_IMAGE, cv::Size(60, 60));

    // If there are no faces detected in the current frame, use the most recent detected face
    if (faces.empty()) return;

    // Deciding the best face based on size (distance from screen)
    cv::Rect closest_face = faces[0];
    for (auto& face : faces)
        if (face.area() > closest_face.area()) closest_face = face;

    // Update and return the detected face
    this->face = closest_face;
}

cv::Mat Recorder::get_frame() { return this->frame; }

cv::Rect Recorder::get_face() { return this->face; }

bool Recorder::use_detection() { return this->detection; }

void Recorder::toggle() { this->detection = !this->detection; }