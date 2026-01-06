#ifndef DELTA_TIME
#define DELTA_TIME

#include "gl.h"

class DeltaTime {
    public:
        static DeltaTime* get_instance();

        // Scene renderer should not be cloneable
        DeltaTime(DeltaTime& other) = delete;

        // Scene renderer should not be assignable
        void operator=(const DeltaTime&) = delete;

        float get_delta_time();
        void update();

    private:
        DeltaTime();
        static DeltaTime* instance;

        float delta_time;
        float previous_time;
};

#endif