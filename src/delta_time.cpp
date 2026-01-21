#include "delta_time.hpp"

DeltaTime* DeltaTime::instance = nullptr;

/**
 * Gets the single delta time instance.
 */
DeltaTime* DeltaTime::get_instance() {
    if (instance == nullptr) {
        instance = new DeltaTime();
    }
    return instance;
}

/**
 * Delta time constructor. The dalte time object tracks the delta's between two frames.
 */
DeltaTime::DeltaTime() {}

/**
 * Gets the delta time.
 */
float DeltaTime::get_delta_time() { return this->delta_time; }

/**
 * Updates the delta time by comparing the current frame time by the previous frame time.
 */
void DeltaTime::update() {
    float current_time = glfwGetTime();
    this->delta_time = current_time - this->previous_time;
    this->previous_time = current_time;
}
