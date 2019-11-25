//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2019 Ryo Suzuki
//	Copyright (c) 2016-2019 OpenSiv3D Project
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
# ifndef SIV3D_INCLUDED
#	define SIV3D_INCLUDED
# endif

//////////////////////////////////////////////////
//
// Utilities
//
//////////////////////////////////////////////////

// プラットフォーム
// Platform
# include <Siv3D/Platform.hpp>

// ライブラリのバージョン
// Library version
# include <Siv3D/Version.hpp>

// 基本型
// Types
# include <Siv3D/Types.hpp>

// 前方宣言
// Forward declarations
# include <Siv3D/Fwd.hpp>

// プレースホルダー
// Place holder
# include <Siv3D/PlaceHolder.hpp>

// コピー禁止 Mixin
// Non-copyable mixin
# include <Siv3D/Uncopyable.hpp>

// 名前付き引数
// Named parameter
# include <Siv3D/NamedParameter.hpp>

// 定義済み名前付き引数
// Predefined named parameters
# include <Siv3D/PredefinedNamedParameter.hpp>

// 範囲をインデックス値とセットで列挙するユーティリティー
// Indexed iterator
# include <Siv3D/Indexed.hpp>

// メタ関数
// Meta
# include <Siv3D/Meta.hpp>

// 型特性
// Type traits
# include <Siv3D/TypeTraits.hpp>

// ユーティリティー
// Utilities
# include <Siv3D/Utility.hpp>

// ファンクター
// Functor
# include <Siv3D/Functor.hpp>

// エンディアン
// Endian
# include <Siv3D/Endian.hpp>

// バイト
// Byte
# include <Siv3D/Byte.hpp>

// バイト配列ビュー形式への変換アダプター
// Adapter for byte array view
# include <Siv3D/ByteArrayViewAdapter.hpp>

// バイト配列ビュー
// Byte array view
# include <Siv3D/ByteArrayView.hpp>

// スレッド
// Thread
# include <Siv3D/Threading.hpp>

// 並列実行タスク
// Concurrent task
# include <Siv3D/ConcurrentTask.hpp>

// メモリアライメント
// Memory alignment
# include <Siv3D/AlignedMemory.hpp>	

// メモリアライメント対応アロケーター
// Aligned allocator
# include <Siv3D/AlignedAllocator.hpp>

// 動的配列（一次元）
// Array
# include <Siv3D/Array.hpp>

// 動的配列（二次元）
// 2D array
# include <Siv3D/Grid.hpp>

// ハッシュテーブル
// Hash table
# include <Siv3D/HashTable.hpp>

// ハッシュセット
// Hash set
# include <Siv3D/HashSet.hpp>

// kd 木
// kd-tree
# include <Siv3D/KDTree.hpp>

// 範囲
// Range
# include <Siv3D/Step.hpp>

// 2D 範囲
// 2D range
# include <Siv3D/Step2D.hpp>

// 無限リスト
// Infinite list
# include <Siv3D/InfiniteList.hpp>

// 無効値を持つ値
// Optional
# include <Siv3D/Optional.hpp>

// 特に指定しないことを表す無効値
// Representation of an unspecified value
# include <Siv3D/Unspecified.hpp>

// ハッシュ
// Hash
# include <Siv3D/Hash.hpp>

// イテレータによる範囲の表現
// Range iterator
# include <Siv3D/RangeIterator.hpp>

// map と each の省略表記
// simple each and map
# include <Siv3D/Evaluater.hpp>

// スコープ・ガード
// Scope guard
# include <Siv3D/ScopeGuard.hpp>

// エラー
// Error
# include <Siv3D/Error.hpp>

//////////////////////////////////////////////////
//
//	String and Number
//
//////////////////////////////////////////////////

// 文字
// Character
# include <Siv3D/Char.hpp>

// 文字列ビュー
// String view
# include <Siv3D/StringView.hpp>

// 文字列
// String
# include <Siv3D/String.hpp>

// Unicode
// Unicode
# include <Siv3D/Unicode.hpp>

// アルファベットの大文字・小文字
// Letter case
# include <Siv3D/LetterCase.hpp>

// 数値
// Number
# include <Siv3D/Number.hpp>

// 多倍長整数
// Arbitrary precision integer type
# include <Siv3D/BigInt.hpp>

// 多倍長浮動小数点数
// 100 decimal digits precision floating point type
# include <Siv3D/BigFloat.hpp>

// フォーマット (bool 型)
// Format (bool)
# include <Siv3D/FormatBool.hpp>

// フォーマット (整数型)
// Format (integer)
# include <Siv3D/FormatInt.hpp>

// フォーマット (浮動小数点数型)
// Format
# include <Siv3D/FormatFloat.hpp>

// 文字列フォーマット
// Format
# include <Siv3D/Format.hpp>

// 文字列フォーマットリテラル
// Formatting literal
# include <Siv3D/FormatLiteral.hpp>

// 文字列フォーマットユーティリティ
// Format
# include <Siv3D/FormatUtility.hpp>

// 文字列 → bool 変換
// Text to bool conversion
# include <Siv3D/ParseBool.hpp>

// 文字列 → 整数 変換
// Text to integer conversion
# include <Siv3D/ParseInt.hpp>

// 文字列 → 浮動小数点数 変換
// Text to float conversion
# include <Siv3D/ParseFloat.hpp>

// 文字列 → 値 変換
// Text to value conversion
# include <Siv3D/Parse.hpp>

// 正規表現
// Regular expression
//# include <Siv3D/Regex.hpp>

// 絵文字リスト
// Emoji list
# include <Siv3D/EmojiList.hpp>

//////////////////////////////////////////////////
//
//	Time and Date
//
//////////////////////////////////////////////////

// 時間の表現
// Duration
# include <Siv3D/Duration.hpp>

// 曜日
// Day of week
# include <Siv3D/DayOfWeek.hpp>

// 日付
// Date
# include <Siv3D/Date.hpp>

// 日付と時刻
// Date and time
# include <Siv3D/DateTime.hpp>

// 時間
// Time
# include <Siv3D/Time.hpp>

// 経過時間の計測
// Stopwatch
# include <Siv3D/Stopwatch.hpp>

// スピードを変更可能なストップウォッチ
// Stopwatch with Variable Speed
# include <Siv3D/CustomStopwatch.hpp>

// カウントダウンタイマー
// Countdown timer
# include <Siv3D/Timer.hpp>

// プロファイラー
// Profiler
# include <Siv3D/TimeProfiler.hpp>

// Clock Counter in Milliseconds
// 処理にかかった時間の測定
# include <Siv3D/MillisecClock.hpp>

// Clock Counter in Microseconds
// 処理にかかった時間の測定
# include <Siv3D/MicrosecClock.hpp>

// Clock Counter in CPU Clocks
// 処理にかかった CPU サイクル数の測定
# include <Siv3D/RDTSCClock.hpp>

//////////////////////////////////////////////////
//
//	File I/O and Encryption
//
//////////////////////////////////////////////////

// ファイルとディレクトリ
// Files and directories
# include <Siv3D/FileSystem.hpp>

// リソースファイルの管理
// Resource files
# include <Siv3D/Resource.hpp>

// ファイルとディレクトリの変更の監視
// Directory Watcher
# include <Siv3D/DirectoryWatcher.hpp>

// IReader インタフェース
// IReader interface
# include <Siv3D/IReader.hpp>

// IReader インタフェース
// IWriter interface
# include <Siv3D/IWriter.hpp>

// メモリ範囲への IReader インタフェース
// Memory Range IReader Wrapper
# include <Siv3D/ReaderView.hpp>

// メモリマップトファイル
// Memory mapped file
# include <Siv3D/MemoryMapping.hpp>

// 書き込み可能なメモリマップトファイル
// Writable memory mapped file
# include <Siv3D/WritableMemoryMapping.hpp>

// 読み込み用バッファ
// Binary Large Object (reader)
# include <Siv3D/ByteArray.hpp>

// 書き込み用バッファ
// Binary Large Object (writer)
# include <Siv3D/MemoryWriter.hpp>

// 読み込み専用バイナリファイル
// Binary file reader
# include <Siv3D/BinaryReader.hpp>

// 書き込み専用バイナリファイル
// Binary file writer
# include <Siv3D/BinaryWriter.hpp>

// 文字列エンコード
// Text encoding
# include <Siv3D/TextEncoding.hpp>

// 読み込み専用テキストファイル
//Text file reader
# include <Siv3D/TextReader.hpp>

// 書き込み専用テキストファイル
// Text file writer
# include <Siv3D/TextWriter.hpp>

// Base64
// Base64
# include <Siv3D/Base64.hpp>

// MD5
// MD5
# include <Siv3D/MD5.hpp>

// xxHash
// xxHash
# include <Siv3D/XXHash.hpp>

// ライセンス出力の管理
// License management
# include <Siv3D/LicenseManager.hpp>

// ログ出力
// Logger
# include <Siv3D/Logger.hpp>

//// AES128 による暗号化
//# include <Siv3D/Crypto.hpp>

// Zstandard 方式による可逆圧縮
// Lossless compression with Zstandard algorithm
# include <Siv3D/Compression.hpp>

//// アーカイブファイルからの読み込み
//# include <Siv3D/ArchivedFileReader.hpp>

//// アーカイブファイル
//# include <Siv3D/FileArchive.hpp>

// CSV ファイルデータの読み書き
// CSV File Reader/Writer
# include <Siv3D/CSVData.hpp>

// INI ファイルデータの読み書き
// INI File Reader/Writer
# include <Siv3D/INIData.hpp>

// XML ファイルの読み込み
// XML Parser
# include <Siv3D/XMLReader.hpp>

// JSON ファイルの読み込み
// JSON Parser
# include <Siv3D/JSONReader.hpp>

// JSON データの書き出し
// JSON Writer
# include <Siv3D/JSONWriter.hpp>

// TOML ファイルの読み込み
// TOML Parser
# include <Siv3D/TOMLReader.hpp>

//// ZIP 圧縮ファイルの読み込み
//# include <Siv3D/ZIPReader.hpp>

//// ZIP 圧縮ファイルの書き出し
//# include <Siv3D/ZIPWriter.hpp>

// HTML ファイルの書き出し
// HTML Document Writer
# include <Siv3D/HTMLWriter.hpp>

//////////////////////////////////////////////////
//
//	Color
//
//////////////////////////////////////////////////

// RGB カラー
// RGB color
# include <Siv3D/Color.hpp>

// HSV カラー
// HSV color
# include <Siv3D/HSV.hpp>

//////////////////////////////////////////////////
//
//	2D Shape
//
//////////////////////////////////////////////////

// 二次元座標と 2D/3D/4D ベクトル
// 2D point and 2D/3D/4D vectors
# include <Siv3D/PointVector.hpp>

// 円座標
# include <Siv3D/Circular.hpp>

// オフセット付き円座標
# include <Siv3D/OffsetCircular.hpp>

// 円柱座標
# include <Siv3D/Cylindrical.hpp>

// 球面座標
# include <Siv3D/Spherical.hpp>

// 3x2 行列
// 3x2 matrix
# include <Siv3D/Mat3x2.hpp>

// 線分
// Line Segment
# include <Siv3D/Line.hpp>

// 長方形
// Rectangle
# include <Siv3D/Rectangle.hpp>

// 円
// Circle
# include <Siv3D/Circle.hpp>

// 楕円
// Ellipse
# include <Siv3D/Ellipse.hpp>

// 三角形
// Triangle
# include <Siv3D/Triangle.hpp>

// 凸四角形
// Convex quadrilateral
# include <Siv3D/Quad.hpp>

// 角丸長方形
// Rounded rectangle
# include <Siv3D/RoundRect.hpp>

// 点の集合（とそれをつないで表現される線分）
// A sequence of points (and the line segments connecting them)
# include <Siv3D/LineString.hpp>

// 多角形
// Polygon
# include <Siv3D/Polygon.hpp>

// 複数の多角形
# include <Siv3D/MultiPolygon.hpp>

// 2 次ベジェ曲線
# include <Siv3D/Bezier2.hpp>

// 3 次ベジェ曲線
# include <Siv3D/Bezier3.hpp>

// Float 型の長方形
# include <Siv3D/FloatRect.hpp>

// Float 型の四角形
# include <Siv3D/FloatQuad.hpp>

// 2D 形状コレクション
// 2D Shapes Collection
# include <Siv3D/Shape2D.hpp>

//// 2D 図形の Variant
//# include <Siv3D/ShapeVariant2D.hpp>

// 2D 交差判定
// 2D Shaoe Intersection
# include <Siv3D/Intersection.hpp>

// 2D 幾何
// 2D Geometry Processing
# include <Siv3D/Geometry2D.hpp>

//////////////////////////////////////////////////
//
//	Random Number
//
//////////////////////////////////////////////////

// 乱数の分布
// Distribution
# include <Siv3D/Distribution.hpp>

// ハードウェア乱数生成器
// Hardware RNG
# include <Siv3D/HardwareRNG.hpp>

// SFMT 方式による乱数生成器
// SFMT RNG
# include <Siv3D/SFMT.hpp>

// メルセンヌ・ツイスタ方式による乱数生成器
// Mersenne Twister RNG
# include <Siv3D/MersenneTwister.hpp>

// その他の乱数生成器
// Other RNGs
# include <Siv3D/RNG.hpp>

// デフォルトの乱数生成器
// Default RNG
# include <Siv3D/DefaultRNG.hpp>

// 乱数ユーティリティ
// RNG Utilities
# include <Siv3D/Random.hpp>

// ランダムな Point の作成
// Random Point Generation
# include <Siv3D/RandomPoint.hpp>

// ランダムな Vec2 の作成
// Random Vec2 Generation
# include <Siv3D/RandomVec2.hpp>

// ランダムな Vec3 の作成
// Random Vec3 Generation
# include <Siv3D/RandomVec3.hpp>

// ランダムな Vec4 の作成
// Random Vec4 Generation
# include <Siv3D/RandomVec4.hpp>

// ランダムな色の作成
// Random Color Generation
# include <Siv3D/RandomColor.hpp>

// ランダムなサンプリング
// Random Sampling
# include <Siv3D/Sample.hpp>

//////////////////////////////////////////////////
//
//	Math
//
//////////////////////////////////////////////////

// 数学定数
// Math Constants
# include <Siv3D/MathConstants.hpp>

// 数学関数
// Math Functions
# include <Siv3D/Math.hpp>

// 線形補間
// Interpolation
# include <Siv3D/Interpolation.hpp>

// イージング関数
// Easing
# include <Siv3D/Easing.hpp>

// イージング ユーティリティ
// Easing Utility
# include <Siv3D/EasingController.hpp>

// トランジション
// Transition
# include <Siv3D/Transition.hpp>

// 周期関数
// Periodic Functions
# include <Siv3D/Periodic.hpp>

// Perlin ノイズ
// Perlin Noise
# include <Siv3D/PerlinNoise.hpp>

// ノイズ生成
// Noise
# include <Siv3D/NoiseGenerator.hpp>

// Poisson Disk 2D
// Poisson Disk 2D
# include <Siv3D/PoissonDisk2D.hpp>

// スプライン
// Spline
# include <Siv3D/Spline.hpp>

// SIMD 演算
// SIMD
# include <Siv3D/SIMDMath.hpp>

// 半精度浮動小数点数
// Half-Pecision Floating-Point
# include <Siv3D/HalfFloat.hpp>

// SIMD 対応 Float4
// SIMD Float4
# include <Siv3D/SIMD_Float4.hpp>

// 数式パーサ
// Math Parser
# include <Siv3D/MathParser.hpp>

//////////////////////////////////////////////////
//
//	Image Processing
//
//////////////////////////////////////////////////

// 画像
// Image
# include <Siv3D/Image.hpp>

// 画像の領域
// Region of Image
# include <Siv3D/ImageRegion.hpp>

// 画像デコーダ・エンコーダインタフェース
# include <Siv3D/ImageFormat.hpp>

// 画像処理
# include <Siv3D/ImageProcessing.hpp>

// 画像のフォーマット
# include <Siv3D/TextureFormat.hpp>

// Exif
# include <Siv3D/Exif.hpp>

// Color components
//# include <Siv3D/ColorComponents.hpp>

//// カスタムカラーフォーマットの画像
//# include <Siv3D/CustomImage.hpp>

// QR code
# include <Siv3D/QR.hpp>

// OpenCV bridge
# include <Siv3D/OpenCV_Bridge.hpp>

//// 手書き文字認識
//# include <Siv3D/HandwritingRecognizer.hpp>

//// 手書き文字認識用の学習データ作成
//# include <Siv3D/HandwritingTrainer.hpp>

# include <Siv3D/SDF.hpp>

//////////////////////////////////////////////////
//
//	Audio Processing
//
//////////////////////////////////////////////////

// 音声波形のサンプル
# include <Siv3D/WaveSample.hpp>

// 波形デコーダ・エンコーダインタフェース
# include <Siv3D/AudioFormat.hpp>

// 音声波形
# include <Siv3D/Wave.hpp>

// Sound Font
# include <Siv3D/SoundFont.hpp>

//// 音声波形のテンポ・ピッチ変更
//# include <Siv3D/WaveStretcher.hpp>

// FFT
# include <Siv3D/FFT.hpp>

//////////////////////////////////////////////////
//
//	Video File
//
//////////////////////////////////////////////////

// GIF アニメーションの書き出し
# include <Siv3D/AnimatedGIFWriter.hpp>

//// 動画ファイルの読み込み
//# include <Siv3D/VideoReader.hpp>

// 動画ファイルの書き出し
# include <Siv3D/VideoWriter.hpp>

//////////////////////////////////////////////////
//
//	Network
//
//////////////////////////////////////////////////

// シリアル通信
# include <Siv3D/Serial.hpp>

//// インターネット
//# include <Siv3D/Internet.hpp>
//// HTTP
//# include <Siv3D/HTTPClient.hpp>

// Twitter への投稿
// Twitter
# include <Siv3D/Twitter.hpp>

// IPv4
// IPv4
# include <Siv3D/IPv4.hpp>

// ネットワーク
// Network
# include <Siv3D/Network.hpp>

// TCP サーバー
// TCP Server
# include <Siv3D/TCPServer.hpp>

// TCP クライアント
// TCP Client
# include <Siv3D/TCPClient.hpp>

//////////////////////////////////////////////////
//
//	System and Window
//
//////////////////////////////////////////////////

// System
# include <Siv3D/System.hpp>

// CPU
# include <Siv3D/CPU.hpp>

// コンソール入出力
// Console Input/Output
# include <Siv3D/Console.hpp>

// Monitor Information
# include <Siv3D/Monitor.hpp>

// 高 DPI
// High DPI
# include <Siv3D/HighDPI.hpp>

// ウィンドウ
// Window
# include <Siv3D/Window.hpp>

// ウィンドウに対するユーザアクション
// User Action on Window
# include <Siv3D/UserAction.hpp>

// メッセージボックス
// Message Box
# include <Siv3D/MessageBox.hpp>

// クリップボード
// Clipboard
# include <Siv3D/Clipboard.hpp>

// ドラッグ & ドロップ
// Drag and Drop
# include <Siv3D/DragDrop.hpp>

// ファイル拡張子フィルタ
// File Extension Filter
# include <Siv3D/FileFilter.hpp>

// ファイルダイアログ
// File Dialog
# include <Siv3D/Dialog.hpp>

// 電源情報
// Power status
# include <Siv3D/PowerStatus.hpp>

// プロファイラー
// Profiling
# include <Siv3D/Profiler.hpp>

// プロセス
// Process
# include <Siv3D/Process.hpp>

// Toast Notification
// Toast Notification
# include <Siv3D/ToastNotification.hpp>

//////////////////////////////////////////////////
//
//	Text to speech
//
//////////////////////////////////////////////////

// Language code
# include <Siv3D/LanguageCode.hpp>

// Text to speech
# include <Siv3D/TextToSpeech.hpp>

// Text to speech
# include <Siv3D/Say.hpp>

//////////////////////////////////////////////////
//
//	Input Device
//
//////////////////////////////////////////////////

// Mouse Cursor
# include <Siv3D/Cursor.hpp>

// 入力状態
# include <Siv3D/Key.hpp>

// 2 つのキーの組み合わせ
# include <Siv3D/KeyConjunction.hpp>

// 2 つ以上のキーの組み合わせ
# include <Siv3D/KeyGroup.hpp>

// Keyboard
# include <Siv3D/Keyboard.hpp>

// Mouse
# include <Siv3D/Mouse.hpp>

// テキスト入力
// Text input
# include <Siv3D/TextInput.hpp>

// ゲームパッド
// Gamepad
# include <Siv3D/Gamepad.hpp>

// Joystick deadzone
# include <Siv3D/DeadZone.hpp>

// XInput 対応ゲームコントローラー
# include <Siv3D/XInput.hpp>

// Joy-Con
# include <Siv3D/JoyCon.hpp>

// Pro-Controller
# include <Siv3D/ProController.hpp>

// マイク入力
# include <Siv3D/Microphone.hpp>

//// タッチ
//# include <Siv3D/Touch.hpp>
//// ペンタブレット
//# include <Siv3D/Pentablet.hpp>
//// Kinect V1
//# include <Siv3D/KinectV1.hpp>
//// Kinect V2
//# include <Siv3D/KinectV2.hpp>

//////////////////////////////////////////////////
//
//	Audio
//
//////////////////////////////////////////////////

// オーディオ
// Audio
# include <Siv3D/Audio.hpp>

//// サウンドの拍カウント
//# include <Siv3D/SoundBeat.hpp>


//////////////////////////////////////////////////
//
//	Graphics
//
//////////////////////////////////////////////////

// 描画画面
// Scene
# include <Siv3D/Scene.hpp>

// 2D 頂点データ
// 2D Vertex
# include <Siv3D/Vertex2D.hpp>

// 2D スプライト
// 2D Sprite
# include <Siv3D/Sprite.hpp>

// ブレンドステート
// Blend State
# include <Siv3D/BlendState.hpp>

// ラスタライザーステート
// Rasterizer State
# include <Siv3D/RasterizerState.hpp>

//// デプスステートとステンシルステート
//# include <Siv3D/DepthStencilState.hpp>

// サンプラーステート
// Sampler State
# include <Siv3D/SamplerState.hpp>

// シェーダ
// Shader
# include <Siv3D/ShaderCommon.hpp>
# include <Siv3D/Shader.hpp>

// 頂点シェーダ
// Vertex Shader
# include <Siv3D/VertexShader.hpp>

// ピクセルシェーダ
// Pixel Shader
# include <Siv3D/PixelShader.hpp>

// 定数バッファ
// Constant Buffer
# include <Siv3D/ConstantBuffer.hpp>

//// 頂点レイアウト
//# include <Siv3D/InputLayout.hpp>

// グラフィックス全般
# include <Siv3D/Graphics.hpp>

// スクリーンショット
// Screen capture
# include <Siv3D/ScreenCapture.hpp>

// 2D グラフィックス設定
# include <Siv3D/Graphics2D.hpp>

// 2D グラフィックス設定
# include <Siv3D/ScopedRenderStates2D.hpp>

// 2D グラフィックス設定
# include <Siv3D/ScopedViewport2D.hpp>

// 2D グラフィックス設定
# include <Siv3D/ScopedColor2D.hpp>

// 2D グラフィックス設定
# include <Siv3D/ScopedCustomShader2D.hpp>

// 2D グラフィックス設定
# include <Siv3D/ScopedRenderTarget2D.hpp>

// 2D 座標変換
# include <Siv3D/Transformer2D.hpp>

// 2D グラフィックス設定
# include <Siv3D/Camera2D.hpp>

//////////////////////////////////////////////////
//
//	Texture
//
//////////////////////////////////////////////////

// Texture Description
# include <Siv3D/TextureDesc.hpp>

// Texture
# include <Siv3D/Texture.hpp>

// 領域を指定したテクスチャ
# include <Siv3D/TextureRegion.hpp>

// 円に貼り付けたテクスチャ
# include <Siv3D/TexturedCircle.hpp>

// 四角形に貼り付けたテクスチャ
# include <Siv3D/TexturedQuad.hpp>

// 角丸長方形に貼り付けたテクスチャ
# include <Siv3D/TexturedRoundRect.hpp>

// 動的テクスチャ
# include <Siv3D/DynamicTexture.hpp>

// レンダーテクスチャ
# include <Siv3D/RenderTexture.hpp>

// レンダーテクスチャ
# include <Siv3D/MSRenderTexture.hpp>

//////////////////////////////////////////////////
//
//	Font
//
//////////////////////////////////////////////////

// Outline Glyph
# include <Siv3D/OutlineGlyph.hpp>

// フォント
// Font
# include <Siv3D/Font.hpp>

// SDF フォント
// SDF Font
# include <Siv3D/SDFFont.hpp>

// 絵文字コレクション
// Emoji
# include <Siv3D/Emoji.hpp>

// アイコンコレクション
// Icon
# include <Siv3D/Icon.hpp>

//////////////////////////////////////////////////
//
//	Stand-alone GUI
//
//////////////////////////////////////////////////

// SimpleGUI
// SimpleGUI
# include <Siv3D/SimpleGUI.hpp>

// SimpleGUI マネージャー
// SimpleGUI manager
# include <Siv3D/SimpleGUIManager.hpp>

// テキストボックス
// Text box
# include <Siv3D/TextBox.hpp>

// Text Editor
//# include <Siv3D/TextEditor.hpp>

//////////////////////////////////////////////////
//
//	Particle System / Effect
//
//////////////////////////////////////////////////

// 簡易エフェクト
// Effect
# include <Siv3D/Effect.hpp>

// 2D パーティクルシステム
// 2D Particle system (Particle)
# include <Siv3D/Particle2D.hpp>

// 2D パーティクルシステム
// 2D Particle system (Emitter)
# include <Siv3D/Emitter2D.hpp>

// 2D パーティクルシステム
// 2D Particle system (System)
# include <Siv3D/ParticleSystem2D.hpp>

//////////////////////////////////////////////////
//
//	Movie
//
//////////////////////////////////////////////////

//// ムービー (AVI, WMV 等に対応)
//# include <Siv3D/VideoPlayer.hpp>
//// メディアプレイヤー (AVI, WMV, MP4 等に対応)
//# include <Siv3D/MediaPlayer.hpp>

//////////////////////////////////////////////////
//
//	Webcam and AR
//
//////////////////////////////////////////////////

// Web カメラ
// Webcam
# include <Siv3D/Webcam.hpp>

//// AR マーカー
//# include <Siv3D/AR.hpp>

//////////////////////////////////////////////////
//
//	3D Shape
//
//////////////////////////////////////////////////

// 4x4 行列
// 4x4 matrix
# include <Siv3D/Mat4x4.hpp>

// クォータニオン
// Quaternion
# include <Siv3D/Quaternion.hpp>

// 3D カメラ
// 3D camera
# include <Siv3D/Camera3D.hpp>

// レイ
// Ray
# include <Siv3D/Ray.hpp>

// 3D 線分
// 3D Line segment
# include <Siv3D/Line3D.hpp>

// 3D 三角形
// 3D Triangle
# include <Siv3D/Triangle3D.hpp>

// 軸平行境界ボックス (AABB)
// Axis Aligned Bounding Box (AABB)
# include <Siv3D/AABB.hpp>

// 有向境界ボックス (OBB)
// Oriented Bounding Box (OBB)
# include <Siv3D/OBB.hpp>

//// メッシュデータ
//# include <Siv3D/MeshData.hpp>
//// メッシュ
//# include <Siv3D/Mesh.hpp>
//// 動的メッシュ
//# include <Siv3D/DynamicMesh.hpp>
//// 変換情報を持ったメッシュ
//# include <Siv3D/TransformedMesh.hpp>
//// パーティクル
//# include <Siv3D/Particle.hpp>
//// 平面
//# include <Siv3D/Plane.hpp>

// 球
// Sphere
# include <Siv3D/Sphere.hpp>

//// ボックス
//# include <Siv3D/Box.hpp>
//// 円盤
//# include <Siv3D/Disc.hpp>
//// 円柱
//# include <Siv3D/Cylinder.hpp>
//// 円錐
//# include <Siv3D/Cone.hpp>
//// 3D 幾何
//# include <Siv3D/Geometry3D.hpp>
//// OBJ ファイル読み込み
//# include <Siv3D/ModelLoader.hpp>
//// 3D モデル
//# include <Siv3D/Model.hpp>
//// フォグ
//# include <Siv3D/Fog.hpp>
//// ライト
//# include <Siv3D/Light.hpp>
//// 3D グラフィックス設定
//# include <Siv3D/Graphics3D.hpp>
//// ポストエフェクト
//# include <Siv3D/PostEffect.hpp>

// ナビゲーションメッシュ
// Navigation Mesh
# include <Siv3D/NavMesh.hpp>

//////////////////////////////////////////////////
//
//	Asset Management
//
//////////////////////////////////////////////////

// アセットハンドル
# include <Siv3D/AssetHandle.hpp>

// アセット管理
// Asset Management
# include <Siv3D/Asset.hpp>

// オーディオアセット
// Audio Asset
# include <Siv3D/AudioAsset.hpp>

// テクスチャアセット
// Texture Asset
# include <Siv3D/TextureAsset.hpp>

// フォントアセット
// Font Asset
# include <Siv3D/FontAsset.hpp>

//// GUI Asset
//# include <Siv3D/GUIAsset.hpp>

//////////////////////////////////////////////////
//
//	2D Physics
//
//////////////////////////////////////////////////

// 2D 物理演算
// 2D Physics
# include <Siv3D/Physics2D.hpp>

//////////////////////////////////////////////////
//
//	Machine Learning
//
//////////////////////////////////////////////////

// SVM
// SVM
# include <Siv3D/SVM.hpp>

// 自然言語処理（日本語）
// NLP (Japanese)
# include <Siv3D/NLP_Japanese.hpp>

//////////////////////////////////////////////////
//
//	Scripting
//
//////////////////////////////////////////////////

// スクリプト
// Script
# include <Siv3D/Script.hpp>

// マネージドスクリプト
// ManagedScript
# include <Siv3D/ManagedScript.hpp>

//////////////////////////////////////////////////
//
//	Others
//
//////////////////////////////////////////////////

// デバッグ表示
// Debug Output
# include <Siv3D/Print.hpp>

//// Add-on
//# include <Siv3D/Addon.hpp>

// シリアライズ
// Serialization
# include <Siv3D/Serialization.hpp>

// GPU ドライバー
// GPU Driver
# include <Siv3D/DiscreteGPU.hpp>

// 静的リンクライブラリ
// Static Libs (MSVC)
# include <Siv3D/WindowsStaticLibs.hpp>

// シーン管理
// Scene Manager
# include <Siv3D/SceneManager.hpp>

//////////////////////////////////////////////////
//
// using namespace を無効にするには NO_S3D_USING マクロを定義します
//
// define NO_S3D_USING to disable using namespace
//
//////////////////////////////////////////////////

# ifndef NO_S3D_USING

using namespace s3d;
using namespace std::literals;

# endif
