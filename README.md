# Setup
## On mac os
For mac install with homebrew:
```
brew install cmake
brew install make
brew install opencv
```

Find the opencv install location. This should be in:
/usr/local/Cellar/opencv

If it's not located there, try running:
```
brew --prefix opencv
```

Put the output of this in:
```
realpath previous-output
```

Now create a .env file in the root directory and add the following:
OPENCV_PATH="path-to-opencv-installation"

Now try building from the root directory with:
cmake .
make

Execute with:
parallax

## On windows
TODO

## On linux
TODO


# Code 'rules'
- Every header file should be in the same directory as it's corresponding .cpp file