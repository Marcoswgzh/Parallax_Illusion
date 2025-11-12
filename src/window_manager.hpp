#ifndef MANAGER
#define MANAGER

#include "gl.h"

/// Has the window reference
/// Devides the window into scene and menu
class WindowManager {
    public:
        static WindowManager* get_instance();

        // Scene renderer should not be cloneable
        WindowManager(WindowManager& other) = delete;

        // Scene renderer should not be assignable
        void operator=(const WindowManager&) = delete;

        GLFWwindow* get_window();

    private:
        WindowManager();

        static WindowManager* instance;
        GLFWwindow* window;
};

#endif