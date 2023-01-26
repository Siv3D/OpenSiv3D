# OpenSiv3D for Web

Project site: <https://siv3d.kamenokosoft.com/>

## Building

- OpenSiv3D for Web will be installed into emscripten sysroot.

### Windows

#### Prerequisites

- [Visual Studio 2019](https://visualstudio.microsoft.com/downloads/)
  - C++ Build Tools core features
  - C++ CMake tools for Windows
- [Git for Windows](https://gitforwindows.org)
- [emscripten](https://siv3d.kamenokosoft.com/building/get-emscripten)

#### Instructions

1. Clone OpenSiv3D Repository
  
  ```cmd
  git clone https://github.com/Siv3D/OpenSiv3D.git
  cd OpenSiv3D
  ```

2. Make a directory to Build. (In this example, make `Web/Build`)
  
  ```cmd
  mkdir Web/Build
  cd Web/Build
  ```
  
3. Build & Install OpenSiv3D for Web
  
  ```cmd
  emcmake cmake -GNinja -DCMAKE_BUILD_TYPE=Release ..
  ninja -j4 install
  ```

### macOS

#### Prerequisites

- [XCode CommandLine Tools](https://apps.apple.com/jp/app/xcode/id497799835)
  - git
  - make
  - python
- [HomeBrew](https://brew.sh/index)
  - CMake
- [emsdk](https://github.com/emscripten-core/emsdk)
  - [emscripten](https://github.com/emscripten-core/emscripten)

#### Instructions

1. Clone OpenSiv3D Repository
  
  ```sh
  git clone https://github.com/Siv3D/OpenSiv3D.git
  cd OpenSiv3D
  ```
  
2. Make a directory to Build. (In this example, make `Web/Build`)
  
  ```sh
  mkdir Web/Build
  cd Web/Build
  ```
  
3. Build & Install OpenSiv3D for Web
  
  ```sh
  emcmake cmake -DCMAKE_BUILD_TYPE=Release ..
  make -j4 install
  ```

### Linux

#### Prerequisites

- build-essential
  - make
  - CMake
- git-core
- python3
- [emsdk](https://github.com/emscripten-core/emsdk)
  - [emscripten](https://github.com/emscripten-core/emscripten)

#### Instructions

1. Clone OpenSiv3D Repository
  
  ```sh
  git clone https://github.com/Siv3D/OpenSiv3D.git
  cd OpenSiv3D
  ```
  
2. Make a directory to Build. (In this example, make `Web/Build`)
  
  ```sh
  mkdir Web/Build
  cd Web/Build
  ```
  
3. Build & Install OpenSiv3D for Web

  ```sh
  emcmake cmake -DCMAKE_BUILD_TYPE=Release ..
  make
  ```

## Building Third-Party Libraries

Third-Party libraries, which is stored in the `Siv3D/lib/Web` folder, are updated by the script [`UpdateWasmLib.sh`](./Utils/UpdateWasmLib.sh).

The update script uses **emlib package manager (emlib.sh)**, please refer to <https://github.com/nokotan/EmscriptenLibraries> for the details.

```sh
chmod +x Utils/UpdateWasmLib.sh
Utils/UpdateWasmLib.sh
```
