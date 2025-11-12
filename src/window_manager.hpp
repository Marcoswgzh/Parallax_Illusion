#ifndef MANAGER
#define MANAGER

#include "gl.h"

/// Has the window reference
/// Devides the window into scene and menu
class WindowManager {
    public:
        WindowManager();
        GLFWwindow* get_window();

    private:
        GLFWwindow* window;
};

#endif