# OpenSiv3D Linux版について
諸事情により実装を見送っている機能を除くと、現在のバージョンは0.17.1900相当です。

## 導入手順
OpenSiv3D Linux版をビルドしてアプリケーションを作成するまでの手順を[こちら](INSTALL.md)にまとめてあります。

現状 Ubuntu 16.04 LTS での導入手順しかありませんが、今後他のディストリビューションの情報も追加予定です。
現在インストール方法が執筆されているディストリビューションは Ubuntu 16.04 LTS と Fedora 26 です。

## サポート環境
サポートしているディスプレイサーバはX11のみです。
`CMakeLists.txt`にWaylandとMir向けにコンパイルするオプションがありますが、
サポートはしておりませんのでご注意ください。

## 依存ライブラリ・パッケージ
コンパイルと実行には以下のライブラリやパッケージが必要です。
- CMake 2.8 以上
- Clang 5, LLVM ~~~または GCC 7.1 以上~~~
  - 開発にはClang 5とLLVMを使っています
  - CMakeLists.txt を編集すればGCCをコンパイラに指定できますが現時点ではエラーが出ます
- boost
- boost-system
- boost-filesystem
  - 必要なboostのバージョンについては `OpenSiv3D/Dependencies/README.md` を参照してください。
- glib2
- OpenGL
- GLU
- GLEW
- libpng
- libturbojpeg
- libgif
- X11
- X11 Input extension (Xi)
- X11 RandR extension (Xrandr)
- X11 Xinerama extension (Xinerama)
- X11 cursor management library (XCursor)
- FreeType2
- OpenAL


## 現状のOpenSiv3D Windows/macOS版との相違点
- Cursor::sceenPos()とCursor::previousScreenPos()はそれぞれCursor::clientPos()とCursor::previousClientPos()と同じ値を返します。(Linuxではディスプレイマネージャによって画面上のどこにカーソルがあるか取得する機能があったりなかったりするため。)
- Monitor::workAreaはMonitor::displayRectと同じ値になっています。(X11環境で各モニタのワークエリアを取得するのが難しいため。)
- Cursor::clip()は動作しますが、clipする領域が黒で塗りつぶされます。(clip領域として指定するのに使っているWindowを透明に描画するするコードが上手く動かないため。)対策が分かり次第修正予定です。
- リソースファイルは実行ファイルと同階層の「resource」ディレクトリ内に配置されます。

