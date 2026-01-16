#ifndef MOUSE
#define MOUSE

#include "gl.h"

class Mouse {
    public:
        static Mouse* get_instance();

        void mouse_callback(GLFWwindow* window, double x_pos, double y_pos);
        
        // Scene renderer should not be cloneable
        Mouse(Mouse& other) = delete;

        // Scene renderer should not be assignable
        void operator=(const Mouse&) = delete;

        float previous_x;
        float previous_y;

        float x_delta;
        float y_delta;

    private:
        Mouse();
        static Mouse* instance;
};

#endif