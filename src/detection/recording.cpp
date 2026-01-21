#include <iostream>
#include <opencv2/opencv.hpp>

#include "recording.hpp"

Recorder* Recorder::instance = nullptr;

/**
 * Gets the single recorder instance.
 */
Recorder* Recorder::get_instance() {
    if (instance == nullptr) {
        instance = new Recorder();
    }

    return instance;
}

/**
 * The recorder class records and tracks the face of the user.
 */
Recorder::Recorder() {
    // Convert OpenCV path predefined macro to string
    std::string haarcascade_dir(HAARCASCADE_DIR);

    // Load face haarcascade classifier
    if (!this->face_cascade.load(haarcascade_dir + "/haarcascade_frontalface_default.xml")) {
        std::cerr << "Error loading Haar cascade file." << std::endl;
        exit(EXIT_FAILURE);
    }
}

/**
 * Start the recorder camera capture.
 */
void Recorder::start() {
    // Open the camera
    capture.open(0);
    if (!capture.isOpened()) {
        std::cerr << "Error: Could not open camera" << std::endl;
        exit(EXIT_FAILURE);
    }
}

/**
 * Updates the recorder, it get the frame then the face, then the stabilization methods are 
 * executed to get stable tracking.
 */
void Recorder::update() {
    // Updates must be done in the correct order
    this->update_frame();
    this->update_face();

    // Calculate the center of the face and adjust face center with camera resolution
    cv::Point3f face_center(this->face.x + this->face.width / 2.0, this->face.y + this->face.height / 2.0, this->face.width);
    face_center.x /= this->frame.cols;
    face_center.y /= this->frame.rows;
    face_center.z /= this->frame.cols;

    if (this->first) {
        this->previous = face_center;
        this->first = false;
    }

    // Recalculate the deltas
    this->delta = face_center - this->previous;

    // Shift the previous deltas with the new one (FIFO)
    this->previous_deltas.push_back(this->delta);
    if (this->previous_deltas.size() > this->n_previous) {
        this->previous_deltas.pop_front();
    }

    // If the delta is too small and the average direction vector is short (i.e. random short jitters) then set the delta's to 0
    cv::Point3f average_direction = this->get_average_direction();
    if (abs(this->delta.x) < this->small_delta.x * this->face.width && abs(average_direction.x) < this->small_average_direction.x * this->face.width) {
        this->delta.x = 0.0;
    }
    
    if (abs(this->delta.y) < this->small_delta.y * this->face.width && abs(average_direction.y) < this->small_average_direction.y * this->face.width) {
        this->delta.y = 0.0;
    }
    
    if (abs(this->delta.z) < this->small_delta.z * this->face.width  && abs(average_direction.z) < this->small_average_direction.z * this->face.width) {
        this->delta.z = 0.0;
    }

    // Deltas should be between these values (found by experimenting)
    this->delta.x = fmax(fmin(this->delta.x, 0.01), -0.01);
    this->delta.y = fmax(fmin(this->delta.y, 0.01), -0.01);
    this->delta.z = fmax(fmin(this->delta.z, 0.01), -0.01);

    // Caculate a speed vector and reduce speed by every frame to create a smooth slow down
    this->speed += glm::vec3(delta.x, delta.y, delta.z);
    this->speed /= 2.0;

    // Update the previous coordinates
    this->previous = face_center;
}

/**
 * This resets the deltas to zero.
 */
void Recorder::reset_deltas() {
    this->delta = cv::Point3f(0.0, 0.0, 0.0);
}

/**
 * This gets the average direction of the previous delta's. 
 */
cv::Point3f Recorder::get_average_direction() {
    cv::Point3f sum = cv::Point3f(0.0, 0.0, 0.0);
    for (cv::Point3f point : this->previous_deltas) {
        sum += point;
    }

    return sum / this->n_previous;
}

/**
 * Updates the current frame, it uses the previous frame if the current frame can't be found.
 */
void Recorder::update_frame() {
    cv::Mat temp;
    this->capture >> temp;

    // Don't update frame if frame is empty
    if (!temp.empty()) {
        this->frame = temp;
    }
}

/**
 * Finds a face in the current frame. It will not set a new face if no faces are found (so the previous face will be used) 
 * and if there are multiple faces the biggest (the closest) face will be used.
 */
void Recorder::update_face() {
    cv::Mat gray;
    cv::cvtColor(this->frame, gray, cv::COLOR_BGR2GRAY);
    cv::equalizeHist(gray, gray);  // TODO: Check what this does

    std::vector<cv::Rect> faces;
    face_cascade.detectMultiScale(gray, faces, 1.1, 3, 0 | cv::CASCADE_SCALE_IMAGE, cv::Size(60, 60));

    // If there are no faces detected in the current frame, use the most recent detected face
    if (faces.empty()) {
        return;
    }

    // Deciding the best face based on size (distance from screen)
    cv::Rect closest_face = faces[0];
    for (auto& face : faces)
        if (face.area() > closest_face.area()) closest_face = face;

    // Update and return the detected face
    this->face = closest_face;
}

/**
 * Gets the x-component of the delta.
 */
float Recorder::get_x_delta() {
    return this->delta.x;
}

/**
 * Gets the y-component of the delta.
 */
float Recorder::get_y_delta() {
    return this->delta.y;
}

/**
 * Gets the z-component of the delta.
 */
float Recorder::get_z_delta() {
    return this->delta.z;
}

/**
 * Gets the speed calculated based on the delta's.
 */
glm::vec3 Recorder::get_speed() {
    return this->speed;
}
