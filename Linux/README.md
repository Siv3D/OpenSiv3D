# Linux版Siv3Dについて

Linuxへの移植は以下の環境で行っています。
- Arch Linux (カーネル 4.10.3)
- clang 3.9.1
- boost 1.63.0

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
その他リンクするライブラリとして、
`-lboost_filesystem -lboost_system -lglib-2.0 -lgio-2.0 -lgobject-2.0 -lpthread -lGL -lpng -lturbojpeg -lX11 -lXi -lXrandr -lXinerama -lXcursor -ldl`を指定する必要があります。

## 現状の本家OpenSiv3Dとの相違点
- Cursor::sceenPos()とCursor::previousScreenPos()はそれぞれCursor::clientPos()とCursor::previsouClientPos()と同じ値を返します。(Linuxではディスプレイマネージャによって画面上のどこにカーソルがあるか取得する機能があったりなかったりするため。)

## テスト
テストコードは `Linux/Test` 以下にあります。
CMakeLists.txtでは、libsiv3d.aが `Linux/Debug` にあることを想定しているため、
`Linux/Debug` にlibsiv3d.aを配置するか、
別の場所にlibsiv3d.aを配置する場合はCMakeLists.txtを編集してください。

