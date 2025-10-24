#!/usr/bin/env sh

# if .env doesn't exist, attempt to generate it, otherwise fail
if [ ! -f .env ]
then
    echo "Could not locate .env file."

    # if brew exists, use it to locate opencv, otherwise fail
    if command -v brew > /dev/null 2>&1
    then
        OPENCV_PATH=$(brew --prefix opencv)

        # if the output of brew is correct, then we will generate the .env file for the user, otherwise fail.
        if ls "$OPENCV_PATH" > /dev/null 2>&1
        then
            printf "Located OpenCV at %s, automatically generating .env file.\n" "$OPENCV_PATH"

            printf "OPENCV_PATH=%s\n" "$OPENCV_PATH" > .env
        else
            # probably not a good idea to automatically install packages
            echo "Please use 'brew install opencv' to install OpenCV."
            exit 1
        fi
    else
        echo "Please create a .env file including an OPENCV_PATH variable pointing to the location of OpenCV."
        exit 1
    fi

fi

cmake -S . -B build
make -C build