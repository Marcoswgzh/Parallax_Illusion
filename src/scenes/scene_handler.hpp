#ifndef SCENE_HANDLER
#define SCENE_HANDLER

#include <optional>

class SceneHandler {
    public:
        static SceneHandler* get_instance();

        // SceneHandler should not be cloneable
        SceneHandler(SceneHandler& other) = delete;

        // SceneHandler should not be assignable
        void operator=(const SceneHandler&) = delete;

        void show_scene_1();
        void show_scene_2();
        void show_scene_3();

        void remove_current_scene();

    private:
        SceneHandler();
        void show_apple_cube_scene();
        static SceneHandler* instance;
};

#endif