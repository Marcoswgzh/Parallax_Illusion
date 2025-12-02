#include "gaze.hpp"

#include <iostream>
#include <opencv2/opencv.hpp>

#include "../detection/detection.hpp"

static float clamp_value(float v, float lo, float hi) { return v < lo ? lo : (v > hi ? hi : v); }

Gaze compute_gaze_from_frame(const cv::Mat& frame) {
    Gaze result{0.f, 0.f, false};
    if (frame.empty()) return result;

    cv::Mat gray;
    cv::cvtColor(frame, gray, cv::COLOR_BGR2GRAY);
    cv::equalizeHist(gray, gray);

    std::vector<cv::Rect> faces;
    face_cascade.detectMultiScale(gray, faces, 1.1, 3, 0 | cv::CASCADE_SCALE_IMAGE, cv::Size(60, 60));
    if (faces.empty()) return result;

    cv::Rect best = faces[0];
    for (auto& f : faces)
        if (f.area() > best.area()) best = f;

    cv::Point face_center(best.x + best.width / 2, best.y + best.height / 2);
    cv::Mat roi_gray = gray(best);

    std::vector<cv::Rect> eyes;
    eye_cascade.detectMultiScale(roi_gray, eyes, 1.05, 3, 0 | cv::CASCADE_SCALE_IMAGE, cv::Size(10, 10));

    if (eyes.empty()) {
        float nx = (face_center.x - frame.cols / 2.f) / (frame.cols / 2.f);
        float ny = -(face_center.y - frame.rows / 2.f) / (frame.rows / 2.f);
        // result.x = clamp_value(nx, -1.f, 1.f);
        // result.y = clamp_value(ny, -1.f, 1.f);
        result.x = nx;
        result.y = ny;
        result.valid = true;
        return result;
    }

    float sum_x = 0.f, sum_y = 0.f;
    for (auto& e : eyes) {
        sum_x += e.x + e.width / 2.f;
        sum_y += e.y + e.height / 2.f;
    }
    sum_x /= eyes.size();
    sum_y /= eyes.size();

    float eye_cx = best.x + sum_x;
    float eye_cy = best.y + sum_y;

    float nx = (eye_cx - frame.cols / 2.f) / (frame.cols / 2.f);
    float ny = -(eye_cy - frame.rows / 2.f) / (frame.rows / 2.f);

    result.x = clamp_value(nx, -1.f, 1.f);
    result.y = clamp_value(ny, -1.f, 1.f);
    result.valid = true;
    return result;
}