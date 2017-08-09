# OpenSiv3D Linux版について
諸事情により実装を見送っている機能を除くと、現在のバージョンは0.15.0相当です。

## 導入手順
OpenSiv3D Linux版をビルドしてアプリケーションを作成するまでの手順を[こちら](INSTALL.md)にまとめてあります。

現状 Ubuntu 16.04 LTS での導入手順しかありませんが、今後他のディストリビューションの情報も追加予定です。

## サポート環境
サポートしているディスプレイサーバはX11のみです。
`CMakeLists.txt`にWaylandとMir向けにコンパイルするオプションがありますが、
サポートはしておりませんのでご注意ください。

## 依存ライブラリ・パッケージ
コンパイルと実行には以下のライブラリやパッケージが必要です。
- CMake 2.8 or newer
- GCC
  - バージョンの相性問題でClang, LLVMからGCCに移行しました
- boost
- boost-system
- boost-filesystem
- glib2
- OpenGL
- GLEW
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
「libSiv3D.a」というファイルができているはずです。

cmakeコマンドを実行するときに`-DCMAKE_BUILD_TYPE=Debug`もしくは`Release`を適用すると
それに対応したオプションがコンパイラに渡されるMakefileが生成されます。

「libSiv3D.a」をリンクしてSiv3Dを使ったプログラムをコンパイルする時には、
`-lSiv3D`オプションでOpenSiv3Dのライブラリをリンクする他に、依存ライブラリとして、
`-lboost_filesystem -lboost_system -lglib-2.0 -lgio-2.0 -lgobject-2.0 -lpthread -lGL -lGLEW -lpng -lturbojpeg -lgif -lX11 -lXi -lXrandr -lXinerama -lXcursor -ldl`を指定する必要があります。

## 現状のOpenSiv3D Windows/macOS版との相違点
- Cursor::sceenPos()とCursor::previousScreenPos()はそれぞれCursor::clientPos()とCursor::previsouClientPos()と同じ値を返します。(Linuxではディスプレイマネージャによって画面上のどこにカーソルがあるか取得する機能があったりなかったりするため。)
- Monitor::workAreaはMonitor::displayRectと同じ値になっています。(X11環境で各モニタのワークエリアを取得するのが難しいため。)
- Cursor::clip()は動作しますが、clipする領域が黒で塗りつぶされます。(clip領域として指定するのに使っているWindowを透明に描画するするコードが上手く動かないため。)対策が分かり次第修正予定です。
- リソースファイルは実行ファイルと同階層の「resource」ディレクトリ内に配置されます。

## テスト
テストコードは `Linux/Test` 以下にあります。
CMakeLists.txtでは、libSiv3D.aが `Linux/Debug` にあることを想定しているため、
`Linux/Debug` にlibSiv3D.aを配置するか、
別の場所にlibSiv3D.aを配置する場合はCMakeLists.txtを編集してください。

また、`MSVC`以下にある`example`ディレクトリのある階層でテストプログラムを実行する必要があります。
