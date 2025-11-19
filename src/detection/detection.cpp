#include <iostream>
#include <opencv2/opencv.hpp>

void detect_and_show() {
    // Convert OpenCV path predefined macro to string
    std::string haarcascade_dir(HAARCASCADE_DIR);

    // Load face haarcascade classifier
    cv::CascadeClassifier face_cascade;
    if (!face_cascade.load(haarcascade_dir + "haarcascade_frontalface_default.xml")) {
        std::cerr << "Error loading Haar cascade file." << std::endl;
        exit(EXIT_FAILURE);
    }

    // Load eye haarcascade classifier
    cv::CascadeClassifier eye_cascade;
    if (!eye_cascade.load(haarcascade_dir + "haarcascade_eye_tree_eyeglasses.xml")) {
        std::cerr << "Error loading Haar cascade file." << std::endl;
        exit(EXIT_FAILURE);
    }

    // Open the camera
    cv::VideoCapture cap(0);
    if (!cap.isOpened()) {
        std::cerr << "Error: Could not open camera" << std::endl;
        exit(EXIT_FAILURE);
    }

    // Define colors
    cv::Scalar blue(255, 0, 0);
    cv::Scalar green(0, 255, 0);

    cv::Mat frame, gray_frame, roi_gray, roi_color;
    while (true) {
        // Read the next frame
        cap.read(frame);
        if (frame.empty()) break;

        // Transform frame to grey frame for processing
        cv::cvtColor(frame, gray_frame, cv::COLOR_BGR2GRAY);

        // Detect faces
        std::vector<cv::Rect> faces;
        face_cascade.detectMultiScale(gray_frame, faces, 1.3, 5);

        // TODO: Drawing this isn't necessary for the final product (so only use
        // coordinates calculated by this)
        // Draw a rectangle around each face
        for (cv::Rect face : faces) {
            cv::Point point1(face.x, face.y);
            cv::Point point2(face.x + face.width, face.y + face.height);
            cv::rectangle(frame, point1, point2, blue, 2);

            // Set the face region as the roi
            roi_gray = gray_frame(face);
            roi_color = frame(face);

            // Detect eyes in the face region
            std::vector<cv::Rect> eyes;
            eye_cascade.detectMultiScale(roi_gray, eyes);
            for (cv::Rect eye : eyes) {
                cv::Point eye_point1(eye.x, eye.y);
                cv::Point eye_point2(eye.x + eye.width, eye.y + eye.height);
                cv::rectangle(roi_color, eye_point1, eye_point2, green, 2);
            }
        }

        // Display the captured frame
        cv::imshow("Eye Tracking", frame);

        // Exit on q key pressed
        if (cv::waitKey(1) == 'q') break;
    }

    // Free the camera capture
    cap.release();
    cv::destroyAllWindows();
}