#!/usr/bin/env sh

# if .env doesn't exist, attempt to generate it, otherwise fail
if [ ! -f .env ]
then
    echo "Could not locate .env file."

    # if brew exists, use it to locate opencv, otherwise fail
    if command -v brew > /dev/null 2>&1
    then
        OPENCV_PATH=$(realpath "$(brew --prefix opencv)")

        # if the output of brew is correct, then we will generate the .env file for the user, otherwise fail.
        if ls "$OPENCV_PATH" > /dev/null 2>&1
        then
            printf "Located OpenCV at %s, automatically generating .env file.\n" "$OPENCV_PATH"

            printf "OPENCV_PATH=%s\n" "$OPENCV_PATH/lib/cmake/opencv4" > .env
            printf "HAARCASCADE_DIR=%s\n" "$OPENCV_PATH/share/opencv4/haarcascades" >> .env
        else
            # 'read' records the user's next input in the variable $REPLY
            read -p "It appears you do not have OpenCV installed. Would you like to install it now? (y/n): " -n 1 -r

            # Accept lowercase or uppercase letter y
            if [[ $REPLY =~ ^[Yy]$ ]]
            then
                echo # Insert empty newline since 'read' does not do that.
                brew install opencv
                OPENCV_PATH=$(realpath "$(brew --prefix opencv)")
                printf "OPENCV_PATH=%s\n" "$OPENCV_PATH/lib/cmake/opencv4" > .env
                printf "HAARCASCADE_DIR=%s\n" "$OPENCV_PATH/share/opencv4/haarcascades" >> .env
            else
                echo "Please use 'brew install opencv' to install OpenCV."
                exit 1
            fi
        fi
    else
        echo "Please create a .env file including an OPENCV_PATH variable pointing to the location of OpenCV."
        exit 1
    fi

fi

cmake -S . -B build
make -C build