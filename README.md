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

Now create a .env file in the root directory and add the following:
```
OPENCV_PATH="path-to-opencv-installation"
```
NOTE: On Mac OS Intel you might need to remove the version from the end of the path to make it work for the next steps.

## On windows

1. Go to [this](https://visualstudio.microsoft.com/downloads/?q=build+tools) page, scroll down to "Tools for Visual Studio" and download "Build Tools for Visual Studio 2022" and launch the downloaded file.

2. Go to the `Individual Components` tab and check `MSVC v143 - VS 2022 C++ x64/x86 build tools (Latest)`, `C++ CMake Tools for Windows` and `Windows 11 SDK` (any version, it doesn't matter) checkboxes. This will require around 5 GB of free space.

3. Click Install to start the download.

4. Download [OpenCV](https://github.com/opencv/opencv/releases/download/4.12.0/opencv-4.12.0-windows.exe) and unzip it (it is a self-extracting archive) somewhere you will remember.

5. In the project directory (where this README is located), create a file and name it `.env`.

6. In this file, type `OPENCV_PATH=[Location of OpenCV from step 4]` (Note: You can right click on the folder and click "Copy as path")

7. Run the provided build.bat file which will run the necessary commands to compile the program. (See caveats for OpenCV related errors)

8. The final .exe is located in `[project directory]/build/debug/parallax.exe`

### Caveats
This is stuff we should probably fix/change, so ideally we will remove these before submission.

1. For CMake to work, `[OpenCV directory]/build` needs to be in the `PATH` environment variable.

2. To run the application, `[OpenCV directory]/build/x64/vc16/bin` needs to be either in the same directory as `parallax.exe` or in `PATH`. (More specifically `opencv_world4120.dll`/`opencv_world4120d.dll` depending on whether debug mode is enabled or not)

3. Due to hardcoded shader location, parallax.exe must be run from the project's root directory. This can be done by either copying `parallax.exe` to the project's root directory and running it from there, or by running `.\build\debug\parallax.exe` from the terminal while the PWD is the project's root directory.

4. If you are still having shader location related issues, see [this merge request](https://gitlab.maastrichtuniversity.nl/project-2-1-25-26/cs-ii/team_02/-/merge_requests/3).

## On linux
TODO


# How to run
Create a build directory in the root of the project. This is only necessary if it doesn't exist yet. 
It could be that vscode creates one for you, then you only have to go into it (don't worry about the files already in it).
```
mkdir build
cd build
```

Then inside of the build directory run the following to compile and run:
```
cmake ..
make
./parallax
```


# Code 'rules'
- Every header file should be in the same directory as it's corresponding .cpp file and should have the same name as that .cpp file.

## Git Flow

- Never commit or merge to main
- Work from the dev branch, only merge to the dev branch with feature branches (so generally no commits to the dev branch)
- Creating a feature branch:
    - git checkout dev (make sure you branch from dev)
    - git pull origin dev (make sure you have the latest changes before branching)
    - git checkout -b feature/your-feature-name (create and go to the branch)
- Using a feature branch:
    - when on the feature branch you can commit all your changes here:
        - git add .
        - git commit -m "your-commit-message"
        - git push origin feature/your-feature-name
    - PLEASE, commit tiny changes at a time, this will make merging easier