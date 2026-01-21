#include "scene_handler.hpp"
#include "../shapes/model.hpp"
#include "../render/scene_renderer.hpp"

SceneHandler* SceneHandler::instance = nullptr;

/**
 * Gets the single scene handler instance.
 */
SceneHandler* SceneHandler::get_instance() {
    if (instance == nullptr) {
        instance = new SceneHandler();
    }
    return instance;
}

/**
 * Constructs the scene handler which contains methods to show different kinds of scenes.
 */
SceneHandler::SceneHandler() {}

/**
 * Shows scene 1.
 */
void SceneHandler::show_scene_1() {
    SceneRenderer::get_instance()->set_light_position(glm::vec3(1.0f, 3.0f, 1.0f));
    SceneRenderer::get_instance()->set_light_color(glm::vec3(1.0f, 1.0f, 1.0f));

    Model model("models/stars/stars.obj", glm::vec3(0.0, 0.0, 0.0));
}

/**
 * Shows scene 2.
 */
void SceneHandler::show_scene_2() {
    SceneRenderer::get_instance()->set_light_position(glm::vec3(-5.0f, 30.0f, 5.0f));
    SceneRenderer::get_instance()->set_light_color(glm::vec3(1.0f, 1.0f, 1.0f));

    Model model3("models/nature/nature.obj", glm::vec3(0.0, -2.0, 0.0));
}

/**
 * Shows scene 3.
 */
void SceneHandler::show_scene_3() {
    SceneRenderer::get_instance()->set_light_position(glm::vec3(1.0f, 3.0f, 1.0f));
    SceneRenderer::get_instance()->set_light_color(glm::vec3(1.0f, 1.0f, 1.0f));

    Model model3("models/table/table.obj", glm::vec3(-0.5, -0.5, 0.0));
}
