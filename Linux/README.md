# OpenSiv3D Linux版について
このブランチは OpenSiv3D の u_update に追従するためのブランチです。

## 依存ライブラリ・パッケージ
コンパイルと実行には以下のライブラリやパッケージが必要です。
- CMake 2.8 以上
- Clang 5, LLVM または GCC 7.2.0 以上
  - 開発にはClang 5とLLVMを使っています
  - CMakeLists.txt を編集すればGCCをコンパイラに指定できます
  - C++17に対応しているGCC 7.1.0 でもコンパイルできるかもしれません（未確認）
- boost
  - 必要なboostのバージョンについては `OpenSiv3D/Dependencies/README.md` を参照してください。

