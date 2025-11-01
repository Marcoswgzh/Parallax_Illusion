@echo off

"C:\Program Files (x86)\Microsoft Visual Studio\2022\BuildTools\Common7\IDE\CommonExtensions\Microsoft\CMake\CMake\bin\cmake.exe" -S . -B build -G "Visual Studio 17 2022" -A x64

if NOT %errorlevel%==0 (
    PAUSE
    exit %errorlevel%
)

"C:\Program Files (x86)\Microsoft Visual Studio\2022\BuildTools\MSBuild\Current\Bin\amd64\MSBuild.exe" build\parallax.vcxproj

if %errorlevel%==0 (
    echo Build complete. The program is located in build/debug/parallax.exe
    PAUSE
    exit 0
)

PAUSE