# OpenSiv3D for Linux


## Requirements
To build OpenSiv3D, CMake and C++ compiler like GCC are required.

The dependent libraries are as follows:
- X11, Xi, Xinerama, Xcursor, Xrandr
- OpenGL
- OpenCV4
- libpng, libjpeg-turbo, giflib, libwebp
- FreeType2, HarfBuzz
- OpenAL
- libogg, libvorbis
- Boost
- AngelScript
- GLib2
- udev
- libdl
- libavcode, libavformat, libavutil, libswresample

Supported display server is X11.
Wayland and Mir are not supported.


## Compiling OpenSiv3D
1. Clone source and change branch.
	1. `git clone https://github.com/Siv3D/OpenSiv3D.git`
	1. `cd OpenSiv3D`
	1. `git checkout linux`
1. Make a directory to Build. (In this example, make `Linux/Build`).
	1. `mkdir Linux/Build`
	1. `cd Linux/Build`
1. Compile OpenSiv3D. If build succeeds, `libSiv3D.a` is obtained.
	1. `cmake -DCMAKE_BUILD_TYPE=Release -GNinja ..`
	1. `ninja`

### Note
- Using `-DCMAKE_BUILD_TYPE=Debug`, it is compiled with `-g3 -O0`.
- The above example uses `ninja`, but you can also compile with `make`.
- Set `CC` and `CXX` before running `cmake` to specify the compiler.


## Compiling an application
Sample files required to compile an application are in `Linux/App` directory.
You can build the sample with `cmake` like OpenSiv3D.
- `Main.cpp`
	- Sample source of the application.
- `CMakeLists.txt`
	- Sample of `CMakeLists.txt` to build the application.
- `resources/` directory
	- It contains resource files required by the application.

### Note
- Change the path of `libSiv3D.a` and include directories in `CMakeLists.txt` properly, when you copy or move `App` directory.
- Make sure that the `resources/` directory is in the same directory as the executable file when runnning the application.
