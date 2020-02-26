dev tool

install dependencies:

`sudo apt install freeglut3 freeglut3-dev g++-8 libglu1-mesa-dev mesa-common-dev build-essential"

Ensure OpenGL has been installed via `glxinfo | grep "OpenGL version"` (Ideally this is a version > 4.0)

Building the tool:

`cmake .`

`cmake --build .`
