//----------------------------------------------------------------------------------------
//
//	Copyright (C) 2008-2016 Ryo Suzuki
//	Copyright (C) 2016 OpenSiv3D Project
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

# include "Siv3D/Platform.hpp"
# include "Siv3D/PlatformWindows.hpp"

//
// ユーティリティ
//
	// ライブラリのバージョン
	# include "Siv3D/Version.hpp"
	// 型
	# include "Siv3D/Types.hpp"
	// 前方宣言
	# include "Siv3D/Fwd.hpp"
	// ユーティリティ
	# include "Siv3D/Utility.hpp"
	// ファンクタ
	# include "Siv3D/Functor.hpp"
	// コピー禁止クラス
	# include "Siv3D/Uncopyable.hpp"
	// アロケータ
	# include "Siv3D/Allocator.hpp"
	// 動的配列
	# include "Siv3D/Array.hpp"
	// 範囲
	# include "Siv3D/Step.hpp"
	// 二次元配列
	# include "Siv3D/Grid.hpp"
	// Optional
	# include "Siv3D/Optional.hpp"
	// unspecified
	# include "Siv3D/Unspecified.hpp"
//
// 文字列と数値
//
	// 文字
	# include "Siv3D/Char.hpp"
	// 文字列
	# include "Siv3D/String.hpp"
	// 文字列ビュー
	# include "Siv3D/StringView.hpp"
	// 文字コード変換
	# include "Siv3D/CharacterSet.hpp"
	// 基数
	# include "Siv3D/Radix.hpp"
	// 大文字小文字
	# include "Siv3D/LetterCase.hpp"	
	// 数値
	# include "Siv3D/Number.hpp"
	// 多倍長整数
	# include "Siv3D/BigInt.hpp"
	// 整数のフォーマット
	# include "Siv3D/FormatInt.hpp"
	// 浮動小数点数のフォーマット
	# include "Siv3D/FormatFloat.hpp"
	// ブール値のフォーマット
	# include "Siv3D/FormatBool.hpp"
	// データ -> 文字列 の変換
	# include "Siv3D/Format.hpp"
	// フォーマットリテラル
	# include "Siv3D/FormatLiteral.hpp"
	// 文字列 -> 整数 の変換
	# include "Siv3D/ParseInt.hpp"
	// 文字列 -> 浮動小数点数 の変換
	# include "Siv3D/ParseFloat.hpp"
	// 文字列 -> ブール値 の変換
	# include "Siv3D/ParseBool.hpp"
	// 文字列 -> データ の変換
	# include "Siv3D/Parse.hpp"
	// 正規表現
	//# include "Siv3D/Regex.hpp"
//
// 時刻と時間
//
	// 時間の単位
	# include "Siv3D/Duration.hpp"
	// 日付
	# include "Siv3D/Date.hpp"
	// 日付と時刻
	//# include "Siv3D/DateTime.hpp"
	// 時間
	# include "Siv3D/Time.hpp"
	// ストップウォッチ
	# include "Siv3D/Stopwatch.hpp"
	// スピードを変更可能なストップウォッチ
	# include "Siv3D/SpeedStopwatch.hpp"
	// タイマー
	# include "Siv3D/Timer.hpp"
	// 処理にかかった時間の測定
	# include "Siv3D/TimeProfiler.hpp"
	// 処理にかかった CPU サイクル数の測定
	# include "Siv3D/RDTSCProfiler.hpp"
//
// ファイル I/O と暗号化
//
	//// ファイルとディレクトリ
	//# include "Siv3D/FileSystem.hpp"
	//// ファイルとディレクトリの変更の監視
	//# include "Siv3D/FileMonitor.hpp"
	//// IReader インタフェース
	//# include "Siv3D/IReader.hpp"
	//// 読み込み用バッファ
	//# include "Siv3D/ByteArray.hpp"
	//// バイナリファイルの読み込み
	//# include "Siv3D/BinaryReader.hpp"
	//// IWriter インタフェース
	//# include "Siv3D/IWriter.hpp"
	//// 書き込み用バッファ
	//# include "Siv3D/MemoryWriter.hpp"
	//// バイナリファイルの書き込み
	//# include "Siv3D/BinaryWriter.hpp"
	//// テキストファイルの読み込み
	//# include "Siv3D/TextReader.hpp"
	//// テキストファイルの書き込み
	//# include "Siv3D/TextWriter.hpp"
	//// Base64
	//# include "Siv3D/Base64.hpp"
	//// MD5
	//# include "Siv3D/MD5.hpp"
	// ログファイル
	# include "Siv3D/Logger.hpp"
	//// AES128 による暗号化
	//# include "Siv3D/Crypto.hpp"
	//// Deflate によるデータの圧縮・展開
	//# include "Siv3D/Compression.hpp"
	//// アーカイブファイルからの読み込み
	//# include "Siv3D/ArchivedFileReader.hpp"
	//// アーカイブファイル
	//# include "Siv3D/FileArchive.hpp"
	//// CSV ファイルの読み込み
	//# include "Siv3D/CSVReader.hpp"
	//// CSV ファイルの書き出し
	//# include "Siv3D/CSVWriter.hpp"
	//// INI ファイルの読み込み
	//# include "Siv3D/INIReader.hpp"
	//// INI ファイルの書き出し
	//# include "Siv3D/INIWriter.hpp"
	//// XML ファイルの読み込み
	//# include "Siv3D/XMLReader.hpp"
	//// JSON ファイルの読み込み
	//# include "Siv3D/JSONReader.hpp"
	//// JSON ファイルの書き出し
	//# include "Siv3D/JSONWriter.hpp"
	//// ZIP 圧縮ファイルの読み込み
	//# include "Siv3D/ZIPReader.hpp"
	//// ZIP 圧縮ファイルの書き出し
	//# include "Siv3D/ZIPWriter.hpp"
//
// 色と二次元図形
//
	//// RGB カラー
	//# include "Siv3D/Color.hpp"
	//// HSV カラー
	//# include "Siv3D/HSV.hpp"
	//// ベクトル
	//# include "Siv3D/PointVector.hpp"
	//// 円座標
	//# include "Siv3D/Circular.hpp"
	//// 円柱座標
	//# include "Siv3D/Cylindrical.hpp"
	//// 球面座標
	//# include "Siv3D/Spherical.hpp"
	//// 3x2 行列
	//# include "Siv3D/Mat3x2.hpp"
	//// 線分
	//# include "Siv3D/Line.hpp"
	//// 長方形
	//# include "Siv3D/Rectangle.hpp"
	//// 円
	//# include "Siv3D/Circle.hpp"
	//// 楕円
	//# include "Siv3D/Ellipse.hpp"
	//// 三角形
	//# include "Siv3D/Triangle.hpp"
	//// 四角形
	//# include "Siv3D/Quad.hpp"
	//// 角丸長方形
	//# include "Siv3D/RoundRect.hpp"
	//// 連続した複数の線分
	//# include "Siv3D/LineString.hpp"
	//// 多角形
	//# include "Siv3D/Polygon.hpp"
	//// 多角形の集合
	//# include "Siv3D/MultiPolygon.hpp"
	//// 矢印形
	//# include "Siv3D/Arrow.hpp"
	//// 2D 図形の Variant
	//# include "Siv3D/Shape.hpp"
	//// レンダリング用形状
	//# include "Siv3D/FloatShape.hpp"
//
// 数学
//
	// 数学定数
	# include "Siv3D/MathConstants.hpp"
	//// 乱数生成エンジン
	//# include "Siv3D/RNG.hpp"
	//// 乱数の分布
	//# include "Siv3D/Distribution.hpp"
	//// 乱数ユーティリティ
	//# include "Siv3D/Random.hpp"
	//// 数学関数
	//# include "Siv3D/Math.hpp"
	//// 線形補間
	//# include "Siv3D/Lerp.hpp"
	//// イージング関数
	//# include "Siv3D/Easing.hpp"
	//// イージング ユーティリティ
	//# include "Siv3D/EasingController.hpp"
	//// 2D 幾何
	//# include "Siv3D/Geometry2D.hpp"
	//// Perlin Noise
	//# include "Siv3D/PerlinNoise.hpp"
	//// スプライン
	//# include "Siv3D/Spline.hpp"
	//// 2 次ベジェ曲線
	//# include "Siv3D/QuadraticBezier.hpp"
	//// 3 次ベジェ曲線
	//# include "Siv3D/CubicBezier.hpp"
	//// SIMD
	//# include "Siv3D/SIMD.hpp"
	//// 半精度浮動小数点数
	//# include "Siv3D/HalfFloat.hpp"
	//// 数式パーサー
	//# include "Siv3D/ExpressionParser.hpp"
