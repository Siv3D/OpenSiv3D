# OpenSiv3D Linux版 インストール方法

OpenSiv3D Linux版をコンパイルして実行ファイルを作成するまでの手順を説明します。


## Linux版において描画がされない問題への対処

OpenSiv3D Linux版には画面に何も描画されないという問題がありましたが原因が判明して一応解決済みです。
この不具合を解決するための修正は[本家リポジトリ(Siv3D/OpenSiv3D.git)](https://github.com/Siv3D/OpenSiv3D.git)で行われましたが、
[移植作業を行っているリポジトリ(wynd2608/OpenSiv3D.git)](https://github.com/wynd2608/OpenSiv3D.git)にはまだ取り込まれていません。
そのため、最新の移植済みコードを利用する場合には `git clone` で取ってきたソースコードに
以下の修正を行う必要があります。

- `OpenSiv3D/Siv3D/Source/Siv3D/Shader/GL/CShader_GL.cpp` で宣言されている文字列 `const String vsCode` 内にある「`out vec4 gl_Position;`」の行を削除する。
- `OpenSiv3D/Siv3D/Source/Siv3D/Renderer2D/GL/GLSpriteBatch.hpp` 内の `setBuffers` 関数内、 `void* pDst  ...` で始まる行を含むブロック冒頭に `if (vertexSize)` と付け足す(該当箇所は2箇所あります)。


## インストール方法

現在、以下のディストリビューションでのインストール方法が執筆済みです。

- [Ubuntu 16.04 LTS](#user-content-ubunt16.04lts)
- [Fedora 26](#user-content-fedora26)


## <a name="ubuntu16.04lts"> Ubuntu 16.04 LTS でのインストール方法 (最終更新 : 2017/08/09)
### 必要なパッケージのインストール
    $ sudo apt install git cmake libx11-dev libxi-dev libxinerama-dev libxcursor-dev libxrandr-dev libjpeg-dev libpng16-dev libgl1-mesa-dev libglu1-mesa-dev libglib2.0-dev libfreetype6-dev

### GCC 7.1のインストール
	$ sudo add-apt-repository ppa:jonathonf/gcc-7.1
	$ sudo apt update
	$ sudo apt install gcc-7 g++-7

外部のリポジトリを追加してインストールします。
これで `gcc-7` 及び `g++-7` コマンドでGCC 7.1を使えます。
(ソースは[こちら](https://askubuntu.com/questions/914885/installing-gcc-7-and-newer-packages-in-ubuntu-16-04)。)

### boostのインストール
バージョン 0.15.0 ではboost 1.64.0が必要なのでコンパイルしてインストールします。

	1.64.0のソースコードをダウンロードして解凍した階層で
	$ cd boost_1_64_0
	$ ./bootstrap
	$ sudo ./b2 install --prefix=/usr

上の例ではインストールprefixが `/usr` になっていますが、既に別バージョンのboostがインストールされている等の場合は適宜変更してください。

### OpenSiv3D Linux版のビルド
ソースコードをクローンします。
`https://github.com/Siv3D/OpenSiv3D.git` からもcloneできますが、最新のLinux版のソースコードは `wynd2608` の方に置いてあります。

	$ git clone https://github.com/wynd2608/OpenSiv3D.git
	$ cd OpenSiv3D/Linux

コンパイル時に `g++-7` を使うようにCMakeLists.txtを書き換えます。
適当なエディタでCMakeLists.txtを開き、最初の方にある `(i)` の内容の行を `(ii)` の内容に置き換えます。

	(i)  set(CMAKE_CXX_COMPILER "g++")
	(ii) set(CMAKE_CXX_COMPILER "g++-7")

また、boost 1.64.0のインストール先を変更した場合はCMakeLists.txtの `include_directories` にインストール先のヘッダファイルのあるディレクトリを追加する必要があります。

デバッグビルドの場合は以下のような感じでOKです。

	$ mkdir Debug
	$ cd Debug
	$ cmake -DCMAKE_BUILD_TYPE=Debug ..
	$ make

リリースビルドの場合もほぼ同様です。

	$ mkdir Release
	$ cd Release
	$ cmake -DCMAKE_BUILD_TYPE=Release ..
	$ make

ビルドが成功すると、ビルドを行ったディレクトリに `libSiv3D.a` ができます。
これがOpenSiv3Dのスタティックライブラリになります。


## <a name="fedora26"> Fedora 26 でのインストール方法 (最終更新 : 2017/08/14)

### 必要なパッケージのインストール
```sh
$ sudo dnf install git cmake gcc-c++ libX11-devel libXi-devel libXinerama-devel libXcursor-devel libXrandr-devel turbojpeg-devel libpng-devel glib2-devel mesa-libGL-devel mesa-libGLU-devel freetype-devel
```

### boostのインストール
バージョン 0.15.0 ではboost 1.64.0が必要なのでコンパイルしてインストールします。

	1.64.0のソースコードをダウンロードして解凍した階層で
	$ cd boost_1_64_0
	$ ./bootstrap
	$ sudo ./b2 install --prefix=/usr

上の例ではインストールprefixが `/usr` になっていますが、既に別バージョンのboostがインストールされている等の場合は適宜変更してください。

また、Fedora Rawhide向けですがboost 1.64.0のRPM自体は存在します。
直接インストールすることも可能かもしれませんがうまく動作するかは未確認です。

### OpenSiv3D Linux版のビルド
ソースコードをクローンします。
`https://github.com/Siv3D/OpenSiv3D.git` からもcloneできますが、最新のLinux版のソースコードは `wynd2608` の方に置いてあります。

	$ git clone https://github.com/wynd2608/OpenSiv3D.git
	$ cd OpenSiv3D/Linux

また、boost 1.64.0のインストール先を変更した場合はCMakeLists.txtの `include_directories` にインストール先のヘッダファイルのあるディレクトリを追加する必要があります。

デバッグビルドの場合は以下のような感じでOKです。

	$ mkdir Debug
	$ cd Debug
	$ cmake -DCMAKE_BUILD_TYPE=Debug ..
	$ make

リリースビルドの場合もほぼ同様です。

	$ mkdir Release
	$ cd Release
	$ cmake -DCMAKE_BUILD_TYPE=Release ..
	$ make

ビルドが成功すると、ビルドを行ったディレクトリに `libSiv3D.a` ができます。
これがOpenSiv3Dのスタティックライブラリになります。


## アプリケーションのコンパイル
依存ライブラリが多いのでコンパイルオプションがだいぶ長くなります。
`Linux/make_debug.sh` と `Linux/make_release.sh` が1つの.cppファイルからアプリケーションをコンパイルするシェルスクリプトの例としてリポジトリに含まれているので使い回したり参考にしたり等してもらえればと思います。
