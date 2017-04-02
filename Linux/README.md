# OpenSiv3D Linux版について

## サポート環境
サポートしているディスプレイサーバはX11のみです。
`CMakeLists.txt`にWaylandとMir向けにコンパイルするオプションがありますが、
サポートはしておりませんのでご注意ください。

## 依存ライブラリ・パッケージ
コンパイルと実行には以下のライブラリやパッケージが必要です。
- CMake 2.8 or newer
- Clang
- LLVM
- boost
- boost-system
- boost-filesystem
- glib2
- OpenGL
- libpng
- libjpeg (turbojpeg)
- libgif
- X11
- X11 Input extension (Xi)
- X11 RandR extension (Xrandr)
- X11 Xinerama extension (Xinerama)
- X11 cursor management library (XCursor)


## コンパイル
以下のコマンドで行なえます。
```
cd [適当な作業ディレクトリ]
cmake [CMakeLists.txtのあるディレクトリへのパス]
make
```

正常にコンパイルが終了すると作業ディレクトリに
「libsiv3d.a」というファイルができているはずです。

cmakeコマンドを実行するときに`-DCMAKE_BUILD_TYPE=Debug`もしくは`Release`を適用すると
それに対応したオプションがコンパイラに渡されるMakefileが生成されます。

「libsiv3d.a」をリンクしてSiv3Dを使ったプログラムをコンパイルする時には、
`-lsiv3d`オプションでOpenSiv3Dのライブラリをリンクする他に、依存ライブラリとして、
`-lboost_filesystem -lboost_system -lglib-2.0 -lgio-2.0 -lgobject-2.0 -lpthread -lGL -lpng -lturbojpeg -lgif -lX11 -lXi -lXrandr -lXinerama -lXcursor -ldl`を指定する必要があります。

## 現状のOpenSiv3D Windows/macOS版との相違点
- Cursor::sceenPos()とCursor::previousScreenPos()はそれぞれCursor::clientPos()とCursor::previsouClientPos()と同じ値を返します。(Linuxではディスプレイマネージャによって画面上のどこにカーソルがあるか取得する機能があったりなかったりするため。)
- Monitor::workAreaはMonitor::displayRectと同じ値になっています。(X11環境で各モニタのワークエリアを取得するのが難しいため。)

## テスト
テストコードは `Linux/Test` 以下にあります。
CMakeLists.txtでは、libsiv3d.aが `Linux/Debug` にあることを想定しているため、
`Linux/Debug` にlibsiv3d.aを配置するか、
別の場所にlibsiv3d.aを配置する場合はCMakeLists.txtを編集してください。

また、`MSVC`以下にある`example`ディレクトリのある階層でテストプログラムを実行する必要があります。
