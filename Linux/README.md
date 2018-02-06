# OpenSiv3D Linux版について
OpenSiv3D Linux版は基本的にOpenSiv3DのmacOS版をベースに手を加えてLinuxに移植したものです。

## 依存ライブラリ・パッケージ
コンパイルと実行には以下のライブラリやパッケージが必要です。
- CMake 2.8 以上
- Clang 5, LLVM または GCC 7.2.0 以上
  - 開発にはClang 5とLLVMを使っています
  - CMakeLists.txt を編集すればGCCをコンパイラに指定できます
  - C++17に対応しているGCC 7.1.0 でもコンパイルできるかもしれません（未確認）
- boost
  - 必要なboostのバージョンについては `OpenSiv3D/Dependencies/README.md` を参照してください。
- OpenGL
- GLEW
- glib2
- libpng
- turbojpeg
- X11
- X11 Input extension (Xi)
- X11 RandR extension (Xrandr)
- X11 Xinerama extension (Xinerama)
- X11 cursor management library (XCursor)
- FreeType2
- HarfBuzz
- OpenAL

# 注意点
- ライセンス等の問題によりAACエンコーダ/デコーダが実装されていません。音声ファイルを再生する場合は別のフォーマットを使ってください。
