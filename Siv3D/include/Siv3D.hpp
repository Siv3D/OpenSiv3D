//----------------------------------------------------------------------------------------
//
//	Copyright (c) 2008-2017 Ryo Suzuki
//	Copyright (c) 2016-2017 OpenSiv3D Project
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

	# define SIV3D_INCLUDED

# endif

//////////////////////////////////////////////////
//
//	Utilities
//
//////////////////////////////////////////////////

	// Platform
	# include "Siv3D/Platform.hpp"

	// Library version
	# include "Siv3D/Version.hpp"

	// Types
	# include "Siv3D/Types.hpp"

	// Forward declarations
	# include "Siv3D/Fwd.hpp"

	// Place holder
	# include "Siv3D/PlaceHolder.hpp"

	// Non-copyable mixin
	# include "Siv3D/Uncopyable.hpp"

	// Named parameter
	# include "Siv3D/NamedParameter.hpp"

	// Meta
	# include "Siv3D/Meta.hpp"

	// Utilities
	# include "Siv3D/Utility.hpp"

	// Functor
	# include "Siv3D/Functor.hpp"

	// Byte
	# include "Siv3D/Byte.hpp"

	// ByteArray view
	# include "Siv3D/ByteArrayView.hpp"

	// Thread
	# include "Siv3D/Threading.hpp"

	// Task
	# include "Siv3D/ConcurrentTask.hpp"

	// Memory alignment
	# include "Siv3D/AlignedMemory.hpp"	

	// Aligned allocator
	# include "Siv3D/AlignedAllocator.hpp"

	// Array
	# include "Siv3D/Array.hpp"

	// Hash table
	# include "Siv3D/HashTable.hpp"

	// Hash set
	# include "Siv3D/HashSet.hpp"

	// Indexed iterator
	# include "Siv3D/Indexed.hpp"

	// Range
	# include "Siv3D/Step.hpp"

	// 2D range
	# include "Siv3D/Step2D.hpp"

	// Infinite list
	# include "Siv3D/InfiniteList.hpp"

	// 2D array
	# include "Siv3D/Grid.hpp"

	// Optional
	# include "Siv3D/Optional.hpp"

	// unspecified
	# include "Siv3D/Unspecified.hpp"

	// 型特性
	# include "Siv3D/TypeTraits.hpp"

	// イテレータによる範囲の表現
	# include "Siv3D/RangeIterator.hpp"

	// map 省略表記
	# include "Siv3D/Evaluater.hpp"

//////////////////////////////////////////////////
//
//	String and Number
//
//////////////////////////////////////////////////

	// Character
	# include "Siv3D/Char.hpp"

	// String view
	# include "Siv3D/StringView.hpp"

	// String
	# include "Siv3D/String.hpp"

	// Unicode
	# include "Siv3D/Unicode.hpp"

	// Letter case
	# include "Siv3D/LetterCase.hpp"

	// Number
	# include "Siv3D/Number.hpp"

	// 多倍長整数
	# include "Siv3D/BigInt.hpp"

	// 多倍長浮動小数点数
	# include "Siv3D/BigFloat.hpp"

	// Format
	# include "Siv3D/BoolFormat.hpp"

	// Format
	# include "Siv3D/IntFormat.hpp"

	// Format
	# include "Siv3D/FloatFormat.hpp"

	// Format
	# include "Siv3D/Format.hpp"

	// Formatting literal
	# include "Siv3D/FormatLiteral.hpp"

	// Format
	# include "Siv3D/FormatUtility.hpp"
	
	// Text to bool conversion
	# include "Siv3D/ParseBool.hpp"
	
	// Text to integer conversion
	# include "Siv3D/ParseInt.hpp"
	
	// Text to float conversion
	# include "Siv3D/ParseFloat.hpp"
	
	// Text to value conversion
	# include "Siv3D/Parse.hpp"

	//// Regular expression
	//# include "Siv3D/Regex.hpp"

//////////////////////////////////////////////////
//
//	Time and Date
//
//////////////////////////////////////////////////

	// Duration
	# include "Siv3D/Duration.hpp"

	// Date
	# include "Siv3D/Date.hpp"

	// Date and time
	# include "Siv3D/DateTime.hpp"

	// 時間
	# include "Siv3D/Time.hpp"

	// Stopwatch
	# include "Siv3D/Stopwatch.hpp"

	// スピードを変更可能なストップウォッチ
	# include "Siv3D/CustomStopwatch.hpp"

	// Countdown timer
	# include "Siv3D/Timer.hpp"

	// Profiler
	# include "Siv3D/TimeProfiler.hpp"

	// 処理にかかった時間の測定
	# include "Siv3D/MillisecClock.hpp"

	// 処理にかかった時間の測定
	# include "Siv3D/MicrosecClock.hpp"

	// 処理にかかった CPU サイクル数の測定
	# include "Siv3D/RDTSCClock.hpp"

//////////////////////////////////////////////////
//
//	File I/O and Encryption
//
//////////////////////////////////////////////////

	// Files and directories
	# include "Siv3D/FileSystem.hpp"

	// Resource files
	# include "Siv3D/Resource.hpp"

	////// ファイルとディレクトリの変更の監視
	////# include "Siv3D/FileMonitor.hpp"

	// IReader interface
	# include "Siv3D/IReader.hpp"

	// IWriter interface
	# include "Siv3D/IWriter.hpp"

	// メモリ範囲への Reader インタフェース
	# include "Siv3D/ReaderView.hpp"

	// Memory mapped file
	# include "Siv3D/MemoryMapping.hpp"

	// Writable memory mapped file
	# include "Siv3D/WritableMemoryMapping.hpp"

	// 読み込み用バッファ
	# include "Siv3D/ByteArray.hpp"

	// 書き込み用バッファ
	# include "Siv3D/MemoryWriter.hpp"

	// Binary file reader
	# include "Siv3D/BinaryReader.hpp"

	// Binary file writer
	# include "Siv3D/BinaryWriter.hpp"

	// Text encoding
	# include "Siv3D/TextEncoding.hpp"

	//Text file reader
	# include "Siv3D/TextReader.hpp"

	// Text file writer
	# include "Siv3D/TextWriter.hpp"

	// Base64
	# include "Siv3D/Base64.hpp"

	// MD5
	# include "Siv3D/MD5.hpp"

	// xxHash
	# include "Siv3D/XXHash.hpp"

	// License management
	# include "Siv3D/LicenseManager.hpp"

	// Logger
	# include "Siv3D/Logger.hpp"

	////// AES128 による暗号化
	////# include "Siv3D/Crypto.hpp"

	// Lossless compression with Zstandard algorithm
	# include "Siv3D/Compression.hpp"

	////// アーカイブファイルからの読み込み
	////# include "Siv3D/ArchivedFileReader.hpp"

	////// アーカイブファイル
	////# include "Siv3D/FileArchive.hpp"

	// CSV ファイルデータの読み書き
	# include "Siv3D/CSVData.hpp"

	// INI ファイルデータの読み書き
	# include "Siv3D/INIData.hpp"

	////// XML ファイルの読み込み
	////# include "Siv3D/XMLReader.hpp"

	// JSON ファイルの読み込み
	# include "Siv3D/JSONReader.hpp"

	////// JSON ファイルの書き出し
	////# include "Siv3D/JSONWriter.hpp"

	////// ZIP 圧縮ファイルの読み込み
	////# include "Siv3D/ZIPReader.hpp"

	////// ZIP 圧縮ファイルの書き出し
	////# include "Siv3D/ZIPWriter.hpp"

	//// HTML ファイルの書き出し
	//# include "Siv3D/HTMLWriter.hpp"

//////////////////////////////////////////////////
//
//	Color
//
//////////////////////////////////////////////////

	// RGB color
	# include "Siv3D/Color.hpp"

	// HSV color
	# include "Siv3D/HSV.hpp"

//////////////////////////////////////////////////
//
//	2D shape
//
//////////////////////////////////////////////////

	// Vector
	# include "Siv3D/PointVector.hpp"

	// 円座標
	# include "Siv3D/Circular.hpp"

	// 円座標
	# include "Siv3D/OffsetCircular.hpp"

	// 円柱座標
	# include "Siv3D/Cylindrical.hpp"

	// 球面座標
	# include "Siv3D/Spherical.hpp"

	// 3x2 matrix
	# include "Siv3D/Mat3x2.hpp"

	// 線分
	# include "Siv3D/Line.hpp"

	// 長方形
	# include "Siv3D/Rectangle.hpp"

	// 円
	# include "Siv3D/Circle.hpp"

	// 楕円
	# include "Siv3D/Ellipse.hpp"

	// 三角形
	# include "Siv3D/Triangle.hpp"

	// 四角形
	# include "Siv3D/Quad.hpp"

	// 角丸長方形
	# include "Siv3D/RoundRect.hpp"

	//// 連続した複数の線分
	//# include "Siv3D/LineString.hpp"

	//// 多角形
	//# include "Siv3D/Polygon.hpp"

	//// 多角形の集合
	//# include "Siv3D/MultiPolygon.hpp"

	//// 2 次ベジェ曲線
	//# include "Siv3D/Bezier2.hpp"

	//// 3 次ベジェ曲線
	//# include "Siv3D/Bezier3.hpp"

	//// Float 型の長方形
	//# include "Siv3D/FloatRect.hpp"

	//// Float 型の四角形
	//# include "Siv3D/FloatQuad.hpp"

	//// 2D 形状
	//# include "Siv3D/Shape2D.hpp"

	////// 2D 図形の Variant
	////# include "Siv3D/ShapeVariant2D.hpp"

	// 2D 交差判定
	# include "Siv3D/Intersection.hpp"

	// 2D 幾何
	# include "Siv3D/Geometry2D.hpp"

//////////////////////////////////////////////////
//
//	Random number
//
//////////////////////////////////////////////////

	// Distribution
	# include "Siv3D/Distribution.hpp"
	
	// Hardware RNG
	# include "Siv3D/HardwareRNG.hpp"
	
	// Xorshift RNG
	# include "Siv3D/Xorshift.hpp"
	
	// SFMT RNG
	# include "Siv3D/SFMT.hpp"
	
	// Mersenne Twister RNG
	# include "Siv3D/MersenneTwister.hpp"
	
	// Default RNG
	# include "Siv3D/DefaultRNG.hpp"

	// 乱数ユーティリティ
	# include "Siv3D/Random.hpp"

	// ランダムな Point の作成
	# include "Siv3D/RandomPoint.hpp"

	// ランダムな Vec2 の作成
	# include "Siv3D/RandomVec2.hpp"

	// ランダムな Vec3 の作成
	# include "Siv3D/RandomVec3.hpp"

	// ランダムな Vec4 の作成
	# include "Siv3D/RandomVec4.hpp"

	// ランダムな色の作成
	# include "Siv3D/RandomColor.hpp"

//
// 数学
//
	// 数学定数
	# include "Siv3D/MathConstants.hpp"

	// 数学関数
	# include "Siv3D/Math.hpp"

	// 線形補間
	# include "Siv3D/Lerp.hpp"

	// イージング関数
	# include "Siv3D/Easing.hpp"

	// イージング ユーティリティ
	# include "Siv3D/EasingController.hpp"

	// トランジション
	# include "Siv3D/Transition.hpp"

	// Perlin Noise
	# include "Siv3D/PerlinNoise.hpp"

	// スプライン
	# include "Siv3D/Spline.hpp"

	// SIMD
	# include "Siv3D/SIMDMath.hpp"

	// 半精度浮動小数点数
	# include "Siv3D/HalfFloat.hpp"

	// 数式パーサ
	# include "Siv3D/MathParser.hpp"

//
// 画像処理
//
	//// 画像
	//# include "Siv3D/Image.hpp"
	//// 画像デコーダ・エンコーダインタフェース
	//# include "Siv3D/ImageFormat.hpp"
	//// 画像処理
	//# include "Siv3D/ImageProcessing.hpp"
	//// 画像のフォーマット
	//# include "Siv3D/TextureFormat.hpp"
	//// カスタムカラーフォーマット
	//# include "Siv3D/CustomColor.hpp"
	//// カスタムカラーフォーマットの画像
	//# include "Siv3D/CustomImage.hpp"
	//// QR コードの作成と認識
	//# include "Siv3D/QR.hpp"
	//// 手書き文字認識
	//# include "Siv3D/HandwritingRecognizer.hpp"
	//// 手書き文字認識用の学習データ作成
	//# include "Siv3D/HandwritingTrainer.hpp"
//
// 音声処理
//
	//// 音声波形のサンプル
	//# include "Siv3D/WaveSample.hpp"
	//// 波形デコーダ・エンコーダインタフェース
	//# include "Siv3D/AudioFormat.hpp"
	//// 音声波形
	//# include "Siv3D/Wave.hpp"
	//// 音声波形のテンポ・ピッチ変更
	//# include "Siv3D/WaveStretcher.hpp"
	//// FFT
	//# include "Siv3D/FFT.hpp"
//
// 動画ファイル
//
	//// GIF アニメーションの書き出し
	//# include "Siv3D/AnimatedGIFWriter.hpp"
	//// 動画ファイルの読み込み
	//# include "Siv3D/VideoReader.hpp"
	//// 動画ファイルの書き出し
	//# include "Siv3D/VideoWriter.hpp"
//
// ネットワーク・通信
//
	//// シリアル通信
	//# include "Siv3D/Serial.hpp"
	//// パイプサーバー
	//# include "Siv3D/PipeServer.hpp"
	//// インターネット
	//# include "Siv3D/Internet.hpp"
	//// HTTP
	//# include "Siv3D/HTTPClient.hpp"
	//// Twitter
	//# include "Siv3D/Twitter.hpp"
	//// ネットワーク
	//# include "Siv3D/Network.hpp"
	//// TCP サーバー
	//# include "Siv3D/TCPServer.hpp"
	//// TCP クライアント
	//# include "Siv3D/TCPClient.hpp"

	# include "Siv3D/System.hpp"

	// コンソールウィンドウ
	# include "Siv3D/Console.hpp"


//////////////////////////////////////////////////
//
//	Namespace
//
//	* define NO_S3D_USING to avoid using namespace *
//
//////////////////////////////////////////////////

# ifndef NO_S3D_USING

	using namespace s3d;
	using namespace s3d::literals;

# endif
