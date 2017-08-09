# OpenSiv3D Linux版 インストール方法

OpenSiv3D Linux版をコンパイルして実行ファイルを作成するまでの手順を説明します。

現状 Ubuntu 16.04 LTS での導入手順しかありませんが、今後他のディストリビューションの情報も追加予定です。

## Ubuntu 16.04 LTS (最終更新 : 2017/08/09)
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

	1.64.0のソースコードをダウンロードして解答した階層で
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

### アプリケーションのコンパイル
依存ライブラリが多いのでコンパイルオプションがだいぶ長くなります。
`Linux/make_debug.sh` と `Linux/make_release.sh` が1つの.cppファイルからアプリケーションをコンパイルするシェルスクリプトの例としてリポジトリに含まれているので使い回したり参考にしたり等してもらえればと思います。
