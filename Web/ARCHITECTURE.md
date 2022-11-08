# Architecture

## Code Map

### `App`

* Includes a sample source file with CMake
  * OpenSiv3D for Web should be [installed into emscripten sysroot](./README.md#building)
* You can copy this folder to create new project

### `CI`

* Includes apps which used in CI checks

### `CMake`

* Unmaintained
* Will be used in future release.

### `VisualStudioTemplate`

* Includes assets which will be bundled in Siv3D project template
* Modify *.tpl files and run `UpdateTemplate.sh`

### `WindowsInstaller`

* Includes Siv3D installer generation script
