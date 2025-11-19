@echo off
SET /P CONFIRMATION="Would you like to automatically install OpenCV? (y/n): "

REM Case insensitive comparison with /I
IF /I %CONFIRMATION% NEQ Y (
    exit 1
)

curl -Lo opencv.exe "https://github.com/opencv/opencv/releases/download/4.12.0/opencv-4.12.0-windows.exe"

if NOT %errorlevel%==0 (
    PAUSE
    exit %errorlevel%
)

opencv -o opencv -y

if NOT %errorlevel%==0 (
    PAUSE
    exit %errorlevel%
)

SET OPENCV_ROOT_PATH=%cd:\=/%

:: important that these paths do not have a space before the redirection `>`, otherwise it messes up the paths!
echo OPENCV_PATH=%OPENCV_ROOT_PATH%/opencv/build/> .env
echo HAARCASCADE_DIR=%OPENCV_ROOT_PATH%/opencv/build/etc/haarcascades/>> .env

echo Success!
PAUSE
exit 0