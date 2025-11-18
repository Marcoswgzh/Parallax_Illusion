@echo off

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