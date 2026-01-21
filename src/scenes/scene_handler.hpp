#ifndef SCENE_HANDLER
#define SCENE_HANDLER

class SceneHandler {
    public:
        static SceneHandler* get_instance();

        // SceneHandler should not be cloneable
        SceneHandler(SceneHandler& other) = delete;

        // SceneHandler should not be assignable
        void operator=(const SceneHandler&) = delete;

        // General
        void show_scene_1();
        void show_scene_2();
        void show_scene_3();

    private:
        SceneHandler();
        static SceneHandler* instance;
};

#endif
