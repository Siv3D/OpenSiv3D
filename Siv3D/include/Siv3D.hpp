//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2021 Ryo Suzuki
//	Copyright (c) 2016-2021 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//	Permission is hereby granted, free of charge, to any person obtaining a copy
//	of this software and associated documentation files(the "Software"), to deal
//	in the Software without restriction, including without limitation the rights
//	to use, copy, modify, merge, publish, distribute, sublicense, and / or sell
//	copies of the Software, and to permit persons to whom the Software is
//	furnished to do so, subject to the following conditions :
//	
//	The above copyright notice and this permission notice shall be included in
//	all copies or substantial portions of the Software.
//	
//	THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
//	IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
//	FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL THE
//	AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
//	LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
//	OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
//	THE SOFTWARE.
//
//----------------------------------------------------------------------------------------

# pragma once 
// ^^^ include guard

# define SIV3D_INCLUDED
// ^^^ This macro is NOT an include guard

//////////////////////////////////////////////////
//
//	ユーティリティ | Utilities
//
//////////////////////////////////////////////////

// プラットフォーム | Platform
# include <Siv3D/Platform.hpp>

// ライブラリのバージョン | Library version
# include <Siv3D/Version.hpp>

// 基本型 | Types
# include <Siv3D/Types.hpp>

// 前方宣言 | Forward declarations
# include <Siv3D/Fwd.hpp>

// プレースホルダー | Place holder
# include <Siv3D/PlaceHolder.hpp>

// コピー禁止 Mixin | Non-copyable mixin
# include <Siv3D/Uncopyable.hpp>

// YesNo タグ | Yes/No tag
# include <Siv3D/YesNo.hpp>

// 定義済み YesNo タグ | Predefined Yes/No tag
# include <Siv3D/PredefinedYesNo.hpp>

// 名前付き引数 | Named parameter
# include <Siv3D/NamedParameter.hpp>

// 定義済み名前付き引数 | Predefined named parameters
# include <Siv3D/PredefinedNamedParameter.hpp>

// 範囲をインデックス値とセットで列挙するユーティリティー | Indexed iterator
# include <Siv3D/Indexed.hpp>

// メタ関数 | Meta
# include <Siv3D/Meta.hpp>

// ユーティリティー | Utilities
# include <Siv3D/Utility.hpp>

// ファンクター | Functor
# include <Siv3D/Functor.hpp>

// エンディアン | Endian
# include <Siv3D/Endian.hpp>

// バイト | Byte
# include <Siv3D/Byte.hpp>

// ハッシュ | Hash
# include <Siv3D/Hash.hpp>

// 範囲 | Range
# include <Siv3D/Step.hpp>

// 2D 範囲 | 2D range
# include <Siv3D/Step2D.hpp>

// 無限リスト | Infinite list
# include <Siv3D/InfiniteList.hpp>

// イテレータによる範囲の表現 | Range iterator
//# include <Siv3D/RangeIterator.hpp> // [Siv3D ToDo]

// スコープ・ガード | Scope guard
# include <Siv3D/ScopeGuard.hpp>

// ユニーク・リソース | Unique resource
# include <Siv3D/UniqueResource.hpp>

// エラー | Error
# include <Siv3D/Error.hpp>

// デマングル | Demangle
# include <Siv3D/Demangle.hpp>

// Kahan の加算アルゴリズム | Kahan summation algorithm
# include <Siv3D/KahanSummation.hpp>

// SIMD | SIMD
# include <Siv3D/SIMD.hpp>

//////////////////////////////////////////////////
//
//	メモリ | Memory
//
//////////////////////////////////////////////////

// Null でないポインタ | Non-null pointer
# include <Siv3D/NonNull.hpp>

// メモリアロケーション | Memory allocation
# include <Siv3D/Memory.hpp>

// メモリアライメント対応アロケーター | Aligned allocator
# include <Siv3D/Allocator.hpp>

//////////////////////////////////////////////////
//
//	Optional クラス | Optional
//
//////////////////////////////////////////////////

// 無効値 | None_t
# include <Siv3D/None.hpp>

// 無効値を持つ値 | Optional
# include <Siv3D/Optional.hpp>

// 特に指定しないことを表す無効値 | Representation of an unspecified value
# include <Siv3D/Unspecified.hpp>

//////////////////////////////////////////////////
//
//	データ構造 | Data Structures
//
//////////////////////////////////////////////////

// 動的配列（一次元）| Array
# include <Siv3D/Array.hpp>

// 動的配列（二次元）| 2D array
# include <Siv3D/Grid.hpp>

// 文字列ルックアップヘルパー | Heterogeneous lookup helper
# include <Siv3D/HeterogeneousLookupHelper.hpp>

// ハッシュテーブル | Hash table
# include <Siv3D/HashTable.hpp>

// ハッシュセット | Hash set
# include <Siv3D/HashSet.hpp>

// kd 木 | kd-tree
# include <Siv3D/KDTree.hpp>

//////////////////////////////////////////////////
//
//	並列・並行処理 | Parallel and Concurrent
//
//////////////////////////////////////////////////

// スレッド | Thread
# include <Siv3D/Threading.hpp>

// 非同期タスク | Asynchronous task
# include <Siv3D/AsyncTask.hpp>

//////////////////////////////////////////////////
//
//	文字と文字列 | Characters and String
//
//////////////////////////////////////////////////

// 文字 | Character
# include <Siv3D/Char.hpp>

// 文字列ビュー | String view
# include <Siv3D/StringView.hpp>

// 文字列 | String
# include <Siv3D/String.hpp>

// Unicode | Unicode
# include <Siv3D/Unicode.hpp>

// Unicode の逐次変換 | Unicode converter
# include <Siv3D/UnicodeConverter.hpp>

// アルファベットの大文字・小文字 | Letter case
# include <Siv3D/LetterCase.hpp>

// 正規表現のマッチ結果 | Regular expression matching
# include <Siv3D/MatchResults.hpp>

// 正規表現 | Regular expression
# include <Siv3D/RegExp.hpp>

// 絵文字リスト | Emoji list
//# include <Siv3D/EmojiList.hpp> // [Siv3D ToDo]

//////////////////////////////////////////////////
//
//	文字列フォーマット | Formatting
//
//////////////////////////////////////////////////

// フォーマット (bool 型) | Format (bool)
# include <Siv3D/FormatBool.hpp>

// フォーマット (整数型) | Format (integer)
# include <Siv3D/FormatInt.hpp>

// フォーマット (浮動小数点数型) | Format (floating point)
# include <Siv3D/FormatFloat.hpp>

// フォーマット用オブジェクト | Formatting object
# include <Siv3D/FormatData.hpp>

// フォーマット関数 | Formatter
# include <Siv3D/Formatter.hpp> // [Siv3D ToDo]

// 文字列フォーマット | Format
# include <Siv3D/Format.hpp>

// 文字列フォーマットリテラル | Formatting literal
# include <Siv3D/FormatLiteral.hpp>

// 文字列ユーティリティ | Formatting utilities
# include <Siv3D/FormatUtility.hpp>

//////////////////////////////////////////////////
//
//	文字列パーサ | Parser
//
//////////////////////////////////////////////////

// 文字列 → bool 変換 | Text-to-bool conversion
# include <Siv3D/ParseBool.hpp>

// 文字列 → 整数 変換 | Text-to-integer conversion
# include <Siv3D/ParseInt.hpp>

// 文字列 → 浮動小数点数 変換 | Text-to-float conversion
# include <Siv3D/ParseFloat.hpp>

// 文字列 → 値 変換 | Text-to-value conversion
# include <Siv3D/Parse.hpp>

//////////////////////////////////////////////////
//
//	数値 | Number
//
//////////////////////////////////////////////////

// 数値 | Number
# include <Siv3D/Number.hpp>

// 浮動小数点数 | Floating point
# include <Siv3D/FloatingPoint.hpp>

// 128-bit 整数型 | 128-bit integer type
# include <Siv3D/Int128.hpp>

// 多倍長整数 | Arbitrary precision integer type
# include <Siv3D/BigInt.hpp>

// 多倍長浮動小数点数 | 100 decimal digits precision floating point type
# include <Siv3D/BigFloat.hpp>

// 浮動小数点数型の共通型 | Common Float
# include <Siv3D/CommonFloat.hpp>

//////////////////////////////////////////////////
//
//	時間と時刻 | Date and Time
//
//////////////////////////////////////////////////

// 時間の表現 | Duration
# include <Siv3D/Duration.hpp>

// 曜日 | Day of week
# include <Siv3D/DayOfWeek.hpp>

// 日付 | Date
# include <Siv3D/Date.hpp>

// 日付と時刻 | Date and time
# include <Siv3D/DateTime.hpp>

// 時間 | Time
# include <Siv3D/Time.hpp>

//////////////////////////////////////////////////
//
//	タイマー | Timer
//
//////////////////////////////////////////////////

// 時刻提供インタフェース | Clock function interface
# include <Siv3D/ISteadyClock.hpp>

// 経過時間の計測 | Stopwatch
# include <Siv3D/Stopwatch.hpp>

// スピードを変更可能なストップウォッチ | Stopwatch with variable speed
# include <Siv3D/VariableSpeedStopwatch.hpp>

// カウントダウンタイマー | Countdown timer
# include <Siv3D/Timer.hpp>

//////////////////////////////////////////////////
//
//	プロファイラー | Profiler
//
//////////////////////////////////////////////////

// プロファイラー | Profiler
# include <Siv3D/Profiler.hpp>

// 時間の測定 | Time profiler
//# include <Siv3D/TimeProfiler.hpp> // [Siv3D ToDo]

// 処理にかかった時間の測定 | Clock counter in milliseconds
# include <Siv3D/MillisecClock.hpp>

// 処理にかかった時間の測定 | Clock counter in microseconds
# include <Siv3D/MicrosecClock.hpp>

// Clock counter in CPU clocks | 処理にかかった CPU サイクル数の測定
# include <Siv3D/RDTSCClock.hpp>

//////////////////////////////////////////////////
//
//	ファイル I/O | File I/O
//
//////////////////////////////////////////////////

// IReader インタフェース | IReader interface
# include <Siv3D/IReader.hpp>

// IWriter インタフェース | IWriter interface
# include <Siv3D/IWriter.hpp>

// 特殊フォルダ | Special folders
# include <Siv3D/SpecialFolder.hpp>

// ファイルコピーオプション | File copy option
# include <Siv3D/CopyOption.hpp>

// ファイルとディレクトリ | Files and directories
# include <Siv3D/FileSystem.hpp> // [Siv3D ToDo]

// リソースファイルの設定 | Resource file option
# include <Siv3D/ResourceOption.hpp>

// リソースファイルの管理 | Resource files
# include <Siv3D/Resource.hpp>

// ファイル操作のイベント | File action
# include <Siv3D/FileAction.hpp>

// ファイルとディレクトリの変更の監視 | Directory watcher
# include <Siv3D/DirectoryWatcher.hpp>

// メモリ範囲への IReader インタフェース | Memory Range IReader Wrapper
//# include <Siv3D/ReaderView.hpp>

// メモリマップトファイル | Memory mapped file
//# include <Siv3D/MemoryMapping.hpp>

// 書き込み可能なメモリマップトファイル | Writable memory mapped file
//# include <Siv3D/WritableMemoryMapping.hpp>

// 読み込み用バッファ | Binary Large Object (reader)
//# include <Siv3D/ByteArray.hpp>

// 書き込み用バッファ | Binary Large Object (writer)
//# include <Siv3D/MemoryWriter.hpp>

// ファイルオープンモード / File open mode
# include <Siv3D/OpenMode.hpp>

// 読み込み専用バイナリファイル | Binary file reader
# include <Siv3D/BinaryReader.hpp>

// 書き込み専用バイナリファイル | Binary file writer
# include <Siv3D/BinaryWriter.hpp>

// Base64 | Base64
# include <Siv3D/Base64.hpp>

// MD5 ハッシュ値 | MD5 hash value
# include <Siv3D/MD5Value.hpp>

// MD5 エンコード | MD5 Encode 
# include <Siv3D/MD5.hpp>

// 暗号化 | Encryption
//# include <Siv3D/Crypto.hpp>

// zlib 方式による可逆圧縮 | Lossless compression with zlib format
//# include <Siv3D/Zlib.hpp>

// Zstandard 方式による可逆圧縮 | Lossless compression with Zstandard algorithm
# include <Siv3D/Compression.hpp>

// アーカイブファイルからの読み込み | Archived file reader
//# include <Siv3D/ArchivedFileReader.hpp>

// アーカイブファイル | File archive
//# include <Siv3D/FileArchive.hpp>

// ZIP 圧縮ファイルの読み込み | ZIP reader
//# include <Siv3D/ZIPReader.hpp>

// ZIP 圧縮ファイルの書き出し | ZIP writer
//# include <Siv3D/ZIPWriter.hpp>

//////////////////////////////////////////////////
//
//	テキストファイルと設定ファイル | Text Files and Configuration Files
//
//////////////////////////////////////////////////

// 文字列エンコード | Text encoding
# include <Siv3D/TextEncoding.hpp>

// 読み込み専用テキストファイル | Text file reader
# include <Siv3D/TextReader.hpp>

// 書き込み専用テキストファイル | Text file writer
# include <Siv3D/TextWriter.hpp>

// CSV データの読み書き | CSV reader/writer
# include <Siv3D/CSV.hpp>

// INI データの読み書き | INI reader/writer
# include <Siv3D/INI.hpp>

// JSON データの書き出し | JSON reader/writer
# include <Siv3D/JSON.hpp>

// XML ファイルの読み込み | XML parser
//# include <Siv3D/XMLReader.hpp>

// TOML ファイルの読み込み | TOML parser
//# include <Siv3D/TOMLReader.hpp>

// HTML ファイルの書き出し | HTML document writer
//# include <Siv3D/HTMLWriter.hpp>

//////////////////////////////////////////////////
//
//	ログ出力 | Logging
//
//////////////////////////////////////////////////

// ログ出力レベル | Log output level
# include <Siv3D/LogLevel.hpp>

// ログの種類 | Log type
# include <Siv3D/LogType.hpp>

// ロガー | Logger
# include <Siv3D/Logger.hpp>

// ライセンス情報 | License information
# include <Siv3D/LicenseInfo.hpp>

// ライセンス出力の管理 | License management
# include <Siv3D/LicenseManager.hpp>

//////////////////////////////////////////////////
//
//	数学 | Math
//
//////////////////////////////////////////////////

// 数学定数 | Math constants
# include <Siv3D/MathConstants.hpp>

// 数学関数 | Math functions
# include <Siv3D/Math.hpp>

// 精度を落とした高速な数学関数 | Fast math functions
# include <Siv3D/FastMath.hpp>

// 線形補間 | Interpolation
# include <Siv3D/Interpolation.hpp>

// イージング関数 | Easing
# include <Siv3D/Easing.hpp>

// イージング ユーティリティ | Easing utility
//# include <Siv3D/EasingController.hpp>

// トランジション | Transition
# include <Siv3D/Transition.hpp>

// 周期関数 | Periodic functions
# include <Siv3D/Periodic.hpp>

// Poisson Disk 2D | Poisson disk 2D
# include <Siv3D/PoissonDisk2D.hpp>

// スプライン | Spline
# include <Siv3D/Spline.hpp>

// SIMD 演算 | SIMD
//# include <Siv3D/SIMDMath.hpp>

// 半精度浮動小数点数 | Half-precision floating-point
# include <Siv3D/HalfFloat.hpp>

// SIMD 対応 Float4 | SIMD Float4
//# include <Siv3D/SIMD_Float4.hpp>

// 数式パーサ | Math parser
# include <Siv3D/MathParser.hpp>

// 統計 | Statistics
# include <Siv3D/Statistics.hpp>

// 素数判定 | Primality test
# include <Siv3D/PrimeNumber.hpp>

//////////////////////////////////////////////////
//
//	ノイズ | Noise
//
//////////////////////////////////////////////////

// ノイズアダプター | Noise adapter
# include <Siv3D/Noise.hpp>

// Gradient ノイズ (クラシック Perlin Noise) | Gradient noise (Classic Perlin Noise)
# include <Siv3D/GradientNoise.hpp> // [Siv3D ToDo]

// 改良型 Gradient ノイズ | Better gradient noise
# include <Siv3D/BetterGradientNoise.hpp> // [Siv3D ToDo]

// Improved Perlin ノイズ | Improved Perlin noise
# include <Siv3D/PerlinNoise.hpp>

// Gabor ノイズ | Gabor noise
# include <Siv3D/GaborNoise.hpp> // [Siv3D ToDo]

// ノイズ生成 | Noise
//# include <Siv3D/NoiseGenerator.hpp>

//////////////////////////////////////////////////
//
//	色 | Color
//
//////////////////////////////////////////////////

// 色 | Colors
# include <Siv3D/ColorHSV.hpp>

// カラーマップ | Colormap
# include <Siv3D/Colormap.hpp>

//////////////////////////////////////////////////
//
//	2D 図形 | 2D Geometry
//
//////////////////////////////////////////////////

// ベクトル | Vectors
# include <Siv3D/PointVector.hpp>

# include <Siv3D/Point.hpp>

# include <Siv3D/Vector2D.hpp>

# include <Siv3D/Vector3D.hpp>

# include <Siv3D/Vector4D.hpp>

# include <Siv3D/CommonFloat.hpp>

# include <Siv3D/CommonVector.hpp>

# include <Siv3D/Vertex2D.hpp>

// 円座標
# include <Siv3D/Circular.hpp>

// オフセット付き円座標
# include <Siv3D/OffsetCircular.hpp>

// 円柱座標
# include <Siv3D/Cylindrical.hpp> // [Siv3D ToDo]

// 球面座標
# include <Siv3D/Spherical.hpp> // [Siv3D ToDo]

// 3x2 行列 | 3x2 matrix
# include <Siv3D/Mat3x2.hpp>

# include <Siv3D/2DShapes.hpp>

// 線のスタイル | Line style
# include <Siv3D/LineStyle.hpp>

// 線分 | Line segment
# include <Siv3D/Line.hpp> // [Siv3D ToDo]

// 長方形 (int32) | Rectangle (int32)
# include <Siv3D/Rect.hpp> // [Siv3D ToDo]

// 長方形 (double) | Rectangle (double)
# include <Siv3D/RectF.hpp> // [Siv3D ToDo]

// 円 | Circle
# include <Siv3D/Circle.hpp> // [Siv3D ToDo]

// 楕円 | Ellipse
# include <Siv3D/Ellipse.hpp> // [Siv3D ToDo]

// 三角形 | Triangle
# include <Siv3D/Triangle.hpp> // [Siv3D ToDo]

// 凸四角形 | Convex quadrilateral
# include <Siv3D/Quad.hpp> // [Siv3D ToDo]

// 角丸長方形 | Rounded rectangle
# include <Siv3D/RoundRect.hpp> // [Siv3D ToDo]

// 点の集合（とそれをつないで表現される線分） | A sequence of points (and the line segments connecting them)
# include <Siv3D/LineString.hpp> // [Siv3D ToDo]

// 多角形 | Polygon
# include <Siv3D/Polygon.hpp> // [Siv3D ToDo]

// 複数の多角形 | Multi-polygon
# include <Siv3D/MultiPolygon.hpp> // [Siv3D ToDo]

// 2 次ベジェ曲線 | Quadratic Bézier curve
# include <Siv3D/Bezier2.hpp> // [Siv3D ToDo]

// 3 次ベジェ曲線 | Cubic Bézier curve
# include <Siv3D/Bezier3.hpp> // [Siv3D ToDo]

// Catmull-Rom スプライン曲線 | Catmull-Rom spline curves
# include <Siv3D/Spline2D.hpp> // [Siv3D ToDo]

// float 型の長方形 | Rectangle (float)
# include <Siv3D/FloatRect.hpp>

// float 型の四角形 | Quad (float)
# include <Siv3D/FloatQuad.hpp>

// 2D 形状コレクション | 2D shapes collection
# include <Siv3D/Shape2D.hpp>

// 2D 幾何 | 2D geometry processing
# include <Siv3D/Geometry2D.hpp>

// 長方形詰込み | Rectangle packing
# include <Siv3D/RectanglePacking.hpp>

// 平面分割 | Planar subdivisions
# include <Siv3D/Subdivision2D.hpp>

//////////////////////////////////////////////////
//
//	乱数と分布 | Random and Distribution
//
//////////////////////////////////////////////////

// 非決定的乱数生成器 | Non-deterministic Random Number Generator
# include <Siv3D/HardwareRNG.hpp>

// 擬似乱数発生器 | Pseudorandom Number Generator
# include <Siv3D/PRNG.hpp>

// 乱数の分布 | Random Number Distribution
# include <Siv3D/Distribution.hpp>

// 離散確率分布 | Discrete Probability Distribution
# include <Siv3D/DiscreteDistribution.hpp>

// 乱数 | Random Number
# include <Siv3D/Random.hpp>

// シャッフル | Random Shuffle
# include <Siv3D/Shuffle.hpp>

// ランダムな Point の作成 | Random Point generation
# include <Siv3D/RandomPoint.hpp>

// ランダムな Vec2 の作成 | Random Vec2 generation
# include <Siv3D/RandomVec2.hpp>

// ランダムな Vec3 の作成 | Random Vec3 generation
//# include <Siv3D/RandomVec3.hpp>

// ランダムな Vec4 の作成 | Random Vec4 generation
//# include <Siv3D/RandomVec4.hpp>

// ランダムな色の作成 | Random Color generation
# include <Siv3D/RandomColor.hpp>

// ランダムなサンプリング | Random sampling
//# include <Siv3D/Sample.hpp>

//////////////////////////////////////////////////
//
//	システム | System
//
//////////////////////////////////////////////////

// 環境変数 | Environment Variable
# include <Siv3D/EnvironmentVariable.hpp>

// コマンドライン引数 | Command-line arguments
# include <Siv3D/CommandLine.hpp>

// CPU 情報 | CPU information
# include <Siv3D/CPUInfo.hpp>

// 画面解像度の定数 | Display resolution constants
# include <Siv3D/DisplayResolution.hpp>

// モニター | Monitor
# include <Siv3D/Monitor.hpp>

// ユーザアクション | User action
# include <Siv3D/UserAction.hpp>

// システム | System
# include <Siv3D/System.hpp>

// コンソール入出力 | Console input/output
# include <Siv3D/Console.hpp>

//////////////////////////////////////////////////
//
//	ネットワーク | Network
//
//////////////////////////////////////////////////

// Twitter | Twitter
# include <Siv3D/Twitter.hpp>

//////////////////////////////////////////////////
//
//	ウィンドウ | Window
//
//////////////////////////////////////////////////

// ウィンドウスタイル | Window Style
# include <Siv3D/WindowStyle.hpp>

// ウィンドウステート | Window State
# include <Siv3D/WindowState.hpp>

// ウィンドウ | Window
# include <Siv3D/Window.hpp>

//////////////////////////////////////////////////
//
//	画像処理 | Image processing
//
//////////////////////////////////////////////////

// 画像のフォーマット | Image format
# include <Siv3D/ImageFormat.hpp>

// ピクセルフォーマット | Pixel format
# include <Siv3D/ImagePixelFormat.hpp>

// 画像の情報 | Image information
# include <Siv3D/ImageInfo.hpp>

# include <Siv3D/ImageAddressMode.hpp>

// 画像 | Image
# include <Siv3D/Image.hpp>

# include <Siv3D/IImageDecoder.hpp>

# include <Siv3D/ImageDecoder.hpp>

# include <Siv3D/ImageFormat/BMPDecoder.hpp>

# include <Siv3D/ImageFormat/PNGDecoder.hpp>

# include <Siv3D/IImageEncoder.hpp>

# include <Siv3D/ImageEncoder.hpp>

// SVG 画像 | SVG image
# include <Siv3D/SVG.hpp>

// QR コードの誤り訂正レベル | QR error correction
# include <Siv3D/QRErrorCorrection.hpp>

// QR コードのモード | QR mode
# include <Siv3D/QRMode.hpp>

// QR コード | QR code
# include <Siv3D/QR.hpp>

//////////////////////////////////////////////////
//
//	入力デバイス | Input device
//
//////////////////////////////////////////////////

// マウスカーソルのスタイル | Mouse Cursor Style
# include <Siv3D/CursorStyle.hpp>

// マウスカーソル | Mouse Cursor
# include <Siv3D/Cursor.hpp>

# include <Siv3D/InputDevice.hpp>

# include <Siv3D/InputGroups.hpp>

# include <Siv3D/Keyboard.hpp>

// マウス | Mouse
# include <Siv3D/Mouse.hpp>

//////////////////////////////////////////////////
//
//	アセット管理 | Asset management
//
//////////////////////////////////////////////////

# include <Siv3D/AssetID.hpp>

# include <Siv3D/AssetIDWrapper.hpp>

# include <Siv3D/AssetHandle.hpp>

//////////////////////////////////////////////////
//
//	ナビメッシュ | Navigation mesh
//
//////////////////////////////////////////////////

# include <Siv3D/NavMeshConfig.hpp>

# include <Siv3D/NavMesh.hpp>

//////////////////////////////////////////////////
//
//	シーン | Scene
//
//////////////////////////////////////////////////

# include <Siv3D/ResizeMode.hpp>

# include <Siv3D/Scene.hpp>

//////////////////////////////////////////////////
//
//	レンダーステート | Render states
//
//////////////////////////////////////////////////

# include <Siv3D/Graphics.hpp>

# include <Siv3D/Graphics2D.hpp>

// ブレンドステート | Blend State
# include <Siv3D/BlendState.hpp>

// ラスタライザーステート | Rasterizer State
# include <Siv3D/RasterizerState.hpp>

// 深度ステンシルステート | Depth Stencil State
# include <Siv3D/DepthStencilState.hpp>

// サンプラーステート | Sampler State
# include <Siv3D/SamplerState.hpp>

// 色乗算スコープ | Color Multiplication Scope
# include <Siv3D/ScopedColorMul2D.hpp>

// 色加算スコープ | Color Addition Scope
# include <Siv3D/ScopedColorAdd2D.hpp>

// レンダーステートスコープ | Render States Scope
# include <Siv3D/ScopedRenderStates2D.hpp>

// 2D 座標変換スコープ | 2D Transformation Scope
# include <Siv3D/Transformer2D.hpp>

# include <Siv3D/BasicCamera2D.hpp>

# include <Siv3D/Camera2D.hpp>

//////////////////////////////////////////////////
//
//	シェーダー | Shader
//
//////////////////////////////////////////////////

// シェーダ | Shader
# include <Siv3D/Shader.hpp>

// シェーダステージ | Shader Stage
# include <Siv3D/ShaderStage.hpp>

// 定数バッファバインディング | Constant Buffer Binding
# include <Siv3D/ConstantBufferBinding.hpp>

// 頂点シェーダ | Vertex Shader
# include <Siv3D/VertexShader.hpp>

// ピクセルシェーダ | Pixel/Fragment Shader
# include <Siv3D/PixelShader.hpp>

// シェーダユーティリティ | Shader Utilities
# include <Siv3D/ShaderCommon.hpp>

// 定数バッファ | Constant Buffer
# include <Siv3D/ConstantBuffer.hpp>

// 2D シェーダスコープ | 2D Shader Scope
# include <Siv3D/ScopedCustomShader2D.hpp>

//////////////////////////////////////////////////
//
//	テクスチャ| Texture
//
//////////////////////////////////////////////////

# include <Siv3D/TexturePixelFormat.hpp>

# include <Siv3D/TextureFormat.hpp>

# include <Siv3D/TextureDesc.hpp>

# include <Siv3D/Texture.hpp>

# include <Siv3D/TextureRegion.hpp>

// 円に貼り付けたテクスチャ
# include <Siv3D/TexturedCircle.hpp>

// 四角形に貼り付けたテクスチャ
# include <Siv3D/TexturedQuad.hpp>

// 角丸長方形に貼り付けたテクスチャ
# include <Siv3D/TexturedRoundRect.hpp>

# include <Siv3D/DynamicTexture.hpp>




//////////////////////////////////////////////////
//
//	未分類
//
//////////////////////////////////////////////////

# include <Siv3D/IEffect.hpp>

# include <Siv3D/Effect.hpp>

# include <Siv3D/FontStyle.hpp>
# include <Siv3D/GlyphInfo.hpp>
# include <Siv3D/GlyphCluster.hpp>
# include <Siv3D/OutlineGlyph.hpp>
# include <Siv3D/BitmapGlyph.hpp>
# include <Siv3D/SDFGlyph.hpp>
# include <Siv3D/MSDFGlyph.hpp>
# include <Siv3D/FontMethod.hpp>
# include <Siv3D/Typeface.hpp>
# include <Siv3D/Font.hpp>
# include <Siv3D/TextStyle.hpp>
# include <Siv3D/DrawableText.hpp>
# include <Siv3D/Print.hpp>
# include <Siv3D/PutText.hpp>
# include <Siv3D/Icon.hpp>
# include <Siv3D/Emoji.hpp>

# include <Siv3D/Buffer2D.hpp>

# include <Siv3D/SceneManager.hpp>
# include <Siv3D/ScreenCapture.hpp>

# include <Siv3D/SimpleGUI.hpp>


//////////////////////////////////////////////////
//
//	Lua スクリプト | Lua Script
//
//////////////////////////////////////////////////

# include <Siv3D/LuaScript.hpp>

//////////////////////////////////////////////////
//
//	アドオン | Add-on
//
//////////////////////////////////////////////////

// アドオンインタフェース | Add-on Interface
# include <Siv3D/IAddon.hpp>

// アドオン | Add-on
# include <Siv3D/Addon.hpp>

//////////////////////////////////////////////////
//
//	アプリケーション設定 | Application configuration
//
//////////////////////////////////////////////////

// アプリケーションの設定 | Application configuration
# include <Siv3D/ApplicationOptions.hpp>

//////////////////////////////////////////////////
//
//	プラットフォーム | Platforms
//
//////////////////////////////////////////////////

# if !defined(SIV3D_LIBRARY_BUILD) && SIV3D_PLATFORM(WINDOWS)

	// Windows + MSVC 用の静的リンクライブラリ | Static link libraries for Windows + MSVC 
	# include <Siv3D/Windows/Libraries.hpp>

# endif

//////////////////////////////////////////////////
//
//	名前空間 | Name space
//
//////////////////////////////////////////////////

# if !defined(SIV3D_LIBRARY_BUILD) && !defined(NO_S3D_USING)

using namespace s3d;
using namespace std::literals;

# endif
