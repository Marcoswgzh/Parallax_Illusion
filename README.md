# Setup
## On mac os
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
NOTE: On mac os intel you might need to remove the version from the end of the path to make it work for the next steps.

Now try building from the root directory with:
cmake .
make

Execute with:
./parallax

## On windows
TODO

## On linux
TODO


# Code 'rules'
- Every header file should be in the same directory as it's corresponding .cpp file


# Git Flow

- Never commit or merge to main
- Work from the dev branch, only merge to the dev branch with feature branches (so generally no commits to the dev branch)
- Creating a feature branch:
    - git checkout dev (make sure you branch from dev)
    - git checkout -b feature/your-feature-name (create and go to the branch)
- Using a feature branch:
    - when on the feature branch you can commit all your changes here:
        - git add .
        - git commit -m "your-commit-message"
        - git push origin feature/your-feature-name
    - PLEASE, commit tiny changes at a time, this will make merging easier