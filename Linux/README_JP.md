# OpenSiv3D Linux版


## ビルド要件
ビルドにはCMake、GCCやClangなどのC++コンパイラが必要です。

依存しているライブラリは以下の通りです。
- X11, Xi, Xinerama, Xcursor, Xrandr
- OpenGL
- OpenCV4
- libpng, libjpeg-turbo, giflib, libwebp
- FreeType2, HarfBuzz
- OpenAL
- libogg, libvorbis
- Boost
- GLib2
- udev
- libdl
- libavcode, libavformat, libavutil, libswresample

ディスプレイサーバにはX11のみをサポートしています。
Wayland及びMirはサポートしていません。


## OpenSiv3Dのビルド
1. ソースコードのクローンとブランチ変更。
	1. `git clone https://github.com/Siv3D/OpenSiv3D.git`
	1. `cd OpenSiv3D`
	1. `git checkout linux`
1. ビルド用のディレクトリを作ります。ここでは`Linux/Build`とします。
	1. `mkdir Linux/Build`
	1. `cd Linux/Build`
1. ビルドを行います。ビルドに成功すると`libSiv3D.a`が得られます。
	1. `cmake -DCMAKE_BUILD_TYPE=Release -GNinja ..`
	1. `ninja`

### 補足
- `-DCMAKE_BUILD_TYPE=Debug`とすると、`-g3 -O0`オプションでコンパイルされます。
- 上記の例では`ninja`を使っていますが、`make`でもコンパイルできます。
- コンパイラを指定する場合は`cmake`を実行する前に環境変数`CC`と`CXX`を設定してください。


## アプリケーションのビルド
`Linux/App`ディレクトリにアプリケーションに必要なファイルの例があります。
OpenSiv3Dと同様に`cmake`を使ってビルドできます。
- `Main.cpp`
	- アプリケーションのソースコードのサンプル。
- `CMakeLists.txt`
	- アプリケーションビルド用の`CMakeLists.txt`のサンプル。
- `resources/`ディレクトリ
	- アプリケーションの実行に必要なリソースを配置したディレクトリ。

### 注意点
- `App`ディレクトリを移動やコピーする場合は`CMakeLists.txt`内に書かれている`libSiv3D.a`のパスとインクルードディレクトリのパスを適切なパスに書き換えてください。
- アプリケーションの実行時には`resources/`ディレクトリが実行ファイルと同階層のディレクトリにあるようにしてください。
