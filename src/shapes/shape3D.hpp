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

        int get_id();

    private:
};

#endif