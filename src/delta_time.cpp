#include "delta_time.hpp"

DeltaTime* DeltaTime::instance = nullptr;

DeltaTime* DeltaTime::get_instance() {
    if (instance == nullptr) {
        instance = new DeltaTime();
    }
    return instance;
}

DeltaTime::DeltaTime() {}

float DeltaTime::get_delta_time() { return this->delta_time; }

void DeltaTime::update() {
    float current_time = glfwGetTime();
    this->delta_time = current_time - this->previous_time;
    this->previous_time = current_time;
}
