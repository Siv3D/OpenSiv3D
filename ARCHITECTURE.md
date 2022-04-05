# Architecture

## Code Map

### `Siv3D/include/`
Contains public headers that are shipped with `OpenSiv3D SDK`.

### `Siv3D/src/`
Contains private source files used to build `OpenSiv3D library`.

### `Siv3D/lib/`
Contains dependent libraries used to build an OpenSiv3D application.

- `Siv3D/lib/Windows`
    -  Contains pre-built libraries that are shipped with `OpenSiv3D SDK for Windows`.
- `Siv3D/lib/macOS`
    -  Contains pre-built libraries that are shipped with `OpenSiv3D SDK for macOS`.

### `Dependencies/`
A directory to place extra dependent library used to build `OpenSiv3D library`.

- `Dependencies/boost_1_74_0/`
    - Place `boost` folder which is a part of [Boost 1.74.0](https://www.boost.org/users/history/version_1_74_0.html)
    - This directory is referenced when building `OpenSiv3D library` on Visual Studio or Xcode.

### `Test/`
Contains source files used to build the OpenSiv3D test application.

### `WindowsDesktop/`
Contains a Visual Studio solution used to build `OpenSiv3D library` and OpenSiv3D test application on Windows.

### `macOS/`
Contains a Xcode project used to build `OpenSiv3D library` and OpenSiv3D test application on macOS.

### `Linux/`
Contains files used to build `OpenSiv3D library` and OpenSiv3D test application on Linux.

### `Web/`
Contains files used to build `OpenSiv3D library` and OpenSiv3D test application that runs on a web browser.
