# Setup
## On Mac OS
For mac install with homebrew:
```
brew install cmake
brew install make
brew install opencv
```

Find the opencv install location, try running:
```
realpath "$(brew --prefix opencv)"
```

The build script `build.sh` can now be used to generate the required `.env` file and compile the program.

## On windows

1. Go to [this](https://visualstudio.microsoft.com/downloads/?q=build+tools) page, scroll down to "Tools for Visual Studio" and download "Build Tools for Visual Studio 2022" and launch the downloaded file.

2. Go to the `Individual Components` tab and check `MSVC v143 - VS 2022 C++ x64/x86 build tools (Latest)`, `C++ CMake Tools for Windows` and `Windows 11 SDK` (any version, it doesn't matter) checkboxes. This will require around 5 GB of free space.

3. Click Install to start the download.

4. Download [OpenCV](https://github.com/opencv/opencv/releases/download/4.12.0/opencv-4.12.0-windows.exe) and unzip it (it is a self-extracting archive) somewhere you will remember.

5. In the project directory (where this README is located), create a file and name it `.env`.

6. In this file, type `OPENCV_PATH=[Location of OpenCV from step 4]` (Note: You can right click on the folder and click "Copy as path")

7. Run the provided build.bat file which will run the necessary commands to compile the program. (See caveats for OpenCV related errors)

8. The final .exe is located in `[project directory]/build/release/parallax.exe`

### Caveats
In certain cases, some changes to the environment may be required to compile or run the application.

1. For CMake to work, `[OpenCV directory]/build` needs to be in the `PATH` environment variable.

2. Due to hardcoded shader location, parallax.exe must be run from the `build` directory in the project's root directory. This can be done by either copying `parallax.exe` to the build directory and running it from there, or by running `cd build && .\release\parallax.exe` from the terminal while the current working directory is the project's root directory.

3. The .exe is fully portable except the shaders need to be in the correct directory relative to the program. If Visual Studio build tools are not installed as above, computers require [Visual Studio C++ Redistributable](https://aka.ms/vs/17/release/vc_redist.x64.exe) to be installed.

## On linux
The steps for any Linux distribution is similar to the instructions for macOS above. If you do not have `brew` installed, then you may need to use your distribution's package manager such as `apt`.

# How to run
Build the program using the instructions above, and run the resulting program while the current working directory is the build directory, either by using `cd build` before running the program in the terminal or moving the executable to the build directory using your GUI.