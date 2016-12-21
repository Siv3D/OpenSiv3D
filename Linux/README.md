# Linux版Siv3Dについて

Linuxへの移植は以下の環境で行っています。
- Arch Linux (カーネル 4.8.13)
- clang 3.9.0
- boost 1.62.0
- glib 2.50.1

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
`-lboost_filesystem -lboost_system -lglib-2.0 -lpthread -lglfw -lGL`を指定する必要があります。

