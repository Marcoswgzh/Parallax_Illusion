#ifndef SHAPE3D
#define SHAPE3D

#include "../gl.h"

/**
 * Interface for 3D shapes.
 */
class Shape3D {
    protected:
        int id;

    public:
        // Avoid leaks
        virtual ~Shape3D() = default;

        float get_x();
        float get_y();
        float get_z();

        virtual float get_width() = 0;
        virtual float get_height() = 0;
        virtual float get_depth() = 0;

    private:
};

#endif