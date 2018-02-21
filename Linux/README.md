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
- udev
  - ジョイスティックの情報取得のため
- UPower
  - D-Bus越しに電源情報を取得します

アプリケーションのコンパイル時のオプション等は`Linux/Test/CMakeLists.txt`を参考にしてください。

# 注意点・留意点
- Cursor::ScreenPos()とCursor::PreviousScreenPos()はそれぞれCursor::Pos()とCursor::PreviousPos()と同じ値を返します。(Linuxではディスプレイマネージャによって画面上のどこにカーソルがあるか取得する機能があったりなかったりするため。)
- Monitor::workAreaはMonitor::displayRectと同じ値になっています。(X11環境で各モニタのワークエリアを取得するのが難しいため。)
- リソースファイルは実行ファイルと同階層の「resource」ディレクトリ内に配置されます。
- ライセンス等の問題によりAACエンコーダ/デコーダが実装されていません。音声ファイルを再生する場合は別のフォーマットを使ってください。
- ジョイスティックのハットスイッチの情報は取得できませんが、追ってサポートする予定です。
- その他未実装の機能等については [こちら](https://github.com/wynd2608/OpenSiv3D/issues) を参照ください。
