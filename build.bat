@echo off

REM Set environment variables
FOR /F "tokens=* USEBACKQ" %%I IN (`type .env`) DO (
    set %%I
    SET ENV_FILE_FOUND=TRUE
)

IF NOT DEFINED ENV_FILE_FOUND (
    REM The type command above already produced a "File not found" or similar error, prompt to install opencv
    goto INSTALL_OPENCV
)

IF NOT DEFINED OPENCV_PATH (
    echo OPENCV_PATH variable not found.
    goto INSTALL_OPENCV
)

IF NOT DEFINED HAARCASCADE_DIR (
    echo HAARCASCADE_DIR variable not found.
    goto INSTALL_OPENCV
)

IF NOT EXIST "%OPENCV_PATH%" (
    REM oh my god to escape closing paranteses you need a ^ character instead of \ what is this nonsense

    echo OPENCV_PATH (%OPENCV_PATH%^)" does not exist.
    goto INSTALL_OPENCV
)

IF NOT EXIST "%HAARCASCADE_DIR%" (
    echo HAARCASCADE_DIR (%HAARCASCADE_DIR%^) does not exist.
    goto INSTALL_OPENCV
)

echo Setting %OPENCV_PATH%
REM Automatically adds OpenCV directory to path
SET PATH=%PATH%;%OPENCV_PATH%

REM All OpenCV related variables are set correctly.
goto AFTER_INSTALL


:INSTALL_OPENCV

REM Maybe a better idea to have the install logic in another file
cmd /c install_opencv

if NOT %errorlevel%==0 (
    PAUSE
    exit %errorlevel%
)

REM Workaround for cmake not being able to find the OpenCV cmake file
SET PATH=%PATH%;.\opencv\build

:AFTER_INSTALL

REM Find location of CMake to execute regardless of the VS Build Tools version
REM The command below gets the location of CMake using vswhere.exe, sets it to block-scoped variable %%F, then assigns it to the global-scoped variable %CMAKE_PATH%
FOR /F "tokens=* USEBACKQ" %%F IN (`"C:\Program Files (x86)\Microsoft Visual Studio\Installer\vswhere.exe" -products * -find Common7\IDE\CommonExtensions\Microsoft\CMake\CMake\bin\cmake.exe`) DO (
    SET CMAKE_PATH=%%F
)

"%CMAKE_PATH%" -S . -B build -G "Visual Studio 17 2022" -A x64

if NOT %errorlevel%==0 (
    PAUSE
    exit %errorlevel%
)

"%CMAKE_PATH%" --build build --config release

if %errorlevel%==0 (
    echo Build complete. The program is located in build/release/parallax.exe
    PAUSE
    exit 0
)

PAUSE