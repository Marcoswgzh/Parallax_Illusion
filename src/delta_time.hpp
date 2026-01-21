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

        // Updator method
        void update();

        // Getter
        float get_delta_time();
        
    private:
        DeltaTime();
        static DeltaTime* instance;

        // Variables to track delta time
        float delta_time;
        float previous_time;
};

#endif