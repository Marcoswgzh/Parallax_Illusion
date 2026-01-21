#ifndef MANAGER
#define MANAGER

#include "gl.h"

class WindowManager {
    public:
        static WindowManager* get_instance();

        // WindowManager not be cloneable
        WindowManager(WindowManager& other) = delete;

        // WindowManager should not be assignable
        void operator=(const WindowManager&) = delete;

        // Getter
        GLFWwindow* get_window();

    private:
        WindowManager();
        static WindowManager* instance;

        // Window which is wrapped
        GLFWwindow* window;
};

#endif
