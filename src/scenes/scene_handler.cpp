#include "scene_handler.hpp"
#include "../shapes/cube.hpp"
#include "../shapes/apple_cube.hpp"
#include "../shapes/model.hpp"

SceneHandler* SceneHandler::instance = nullptr;

SceneHandler* SceneHandler::get_instance() {
    if (instance == nullptr) {
        instance = new SceneHandler();
    }
    return instance;
}

SceneHandler::SceneHandler() {}

void SceneHandler::show_scene_1() {
    Cube cube1(glm::vec3(2.0, 2.0, 2.0), glm::vec3(0.0, 0.0, 0.0), glm::vec3(0.2, 0.4, 0.8));
    Cube cube2(glm::vec3(2.0, 2.0, 2.0), glm::vec3(0.0, 4.0, 0.0), glm::vec3(0.2, 0.4, 0.8));
    Cube cube3(glm::vec3(2.0, 2.0, 2.0), glm::vec3(0.0, 0.0, 4.0), glm::vec3(0.2, 0.4, 0.8));
    Cube cube4(glm::vec3(2.0, 2.0, 2.0), glm::vec3(4.0, 0.0, 0.0), glm::vec3(0.2, 0.4, 0.8));
    AppleCube apple_cube(glm::vec3(2.0, 2.0, 2.0), glm::vec3(0.0, -4.0, 0.0));
}

void SceneHandler::show_scene_2() {
    Model model3("models/monkey/monke.obj", glm::vec3(0.0, 0.0, 0.0));
}

void SceneHandler::show_scene_3() {
    Model model3("models/nature/Nature.obj", glm::vec3(0.0, 0.0, 0.0));
}

void SceneHandler::remove_current_scene() {}