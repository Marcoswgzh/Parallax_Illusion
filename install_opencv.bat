@echo off
SET /P CONFIRMATION="Would you like to automatically install OpenCV? (y/n): "

REM Case insensitive comparison with /I
IF /I %CONFIRMATION% NEQ Y (
    exit 1
)

curl -o opencv.exe "https://release-assets.githubusercontent.com/github-production-release-asset/5108051/cbfb55ee-c3b6-4f31-ac5d-4aaddf6f657e?sp=r&sv=2018-11-09&sr=b&spr=https&se=2025-11-18T17%3A31%3A17Z&rscd=attachment%3B+filename%3Dopencv-4.12.0-windows.exe&rsct=application%2Foctet-stream&skoid=96c2d410-5711-43a1-aedd-ab1947aa7ab0&sktid=398a6654-997b-47e9-b12b-9515b896b4de&skt=2025-11-18T16%3A30%3A56Z&ske=2025-11-18T17%3A31%3A17Z&sks=b&skv=2018-11-09&sig=Of7VvCgvhUp3nQI0tt%2F8C7EO1lW%2FxLoVhSgOzACB81A%3D&jwt=eyJ0eXAiOiJKV1QiLCJhbGciOiJIUzI1NiJ9.eyJpc3MiOiJnaXRodWIuY29tIiwiYXVkIjoicmVsZWFzZS1hc3NldHMuZ2l0aHVidXNlcmNvbnRlbnQuY29tIiwia2V5Ijoia2V5MSIsImV4cCI6MTc2MzQ4NzA5OCwibmJmIjoxNzYzNDgzNDk4LCJwYXRoIjoicmVsZWFzZWFzc2V0cHJvZHVjdGlvbi5ibG9iLmNvcmUud2luZG93cy5uZXQifQ.2pmBiMlT4d22MrEBUAn5hcplVVXTAqqTIJqYTlXzIlk&response-content-disposition=attachment%3B%20filename%3Dopencv-4.12.0-windows.exe&response-content-type=application%2Foctet-stream"

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