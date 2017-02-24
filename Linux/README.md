# Linux版Siv3Dについて

Linuxへの移植は以下の環境で行っています。
- Arch Linux (カーネル 4.9.11)
- clang 3.9.1
- boost 1.63.0

コンパイルは以下のコマンドで行なえます。
```
cd (適当な作業ディレクトリ)
cmake (CMakeLists.txtのあるディレクトリへのパス)
make
```

正常にコンパイルが終了すると作業ディレクトリに
「libsiv3d.a」というファイルができているはずです。

cmakeコマンドを実行するときに`-DCMAKE_BUILD_TYPE=Debug`もしくは`Release`を適用すると
それに対応したオプションがコンパイラに渡されるMakefileが生成されます。

「libsiv3d.a」をリンクしてSiv3Dを使ったプログラムをコンパイルする時には、
その他リンクするライブラリとして、
`-lboost_filesystem -lboost_system -lglib-2.0 -lgio-2.0 -lgobject-2.0 -lpthread -lglfw -lGL`を指定する必要があります。

現状の本家OpenSiv3Dとの相違点は以下のとおりです。
- Cursor::sceenPos()とCursor::previousScreenPos()はそれぞれCursor::clientPos()とCursor::previsouClientPos()と同じ値を返します。(Linuxではディスプレイマネージャによって画面上のどこにカーソルがあるか取得する機能があったりなかったりするため。)

