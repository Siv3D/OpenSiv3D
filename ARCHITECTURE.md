# Architecture

## Code Map

### `Siv3D/include/`
Contains public headers that are shipped with `OpenSiv3D SDK`.

### `Siv3D/src/`
Contains sources files to build `OpenSiv3D library`.

### `Siv3D/lib/`
Contains dependent libraries to build an OpenSiv3D application.

- `Siv3D/lib/Windows`
    -  Contains pre-built libraries that are shipped with `OpenSiv3D SDK for Windows`.
- `Siv3D/lib/macOS`
    -  Contains pre-built libraries that are shipped with `OpenSiv3D SDK for macOS`.

### `Dependencies/`
A directory to place extra dependent library source files.

- `Dependencies/boost_1_73_0/`
    - Place `boost` folder that is a part of the Boost 1.73.0
    - This directory is referenced when building `OpenSiv3D library` in Visual Studio or Xcode.

### `Test/`
Contains source files for the OpenSiv3D test application.

### `WindowsDesktop/`
Contains a Visual Studio solution to build `OpenSiv3D library` and OpenSiv3D test application on Windows.

### `macOS/`
Contains a Xcode project to build `OpenSiv3D library` and OpenSiv3D test application on macOS.

### `Linux/`
Contains files to build `OpenSiv3D library` and OpenSiv3D test application on Linux.

### `Web/`
Contains files to build `OpenSiv3D library` and OpenSiv3D test application that runs on a web browser.
