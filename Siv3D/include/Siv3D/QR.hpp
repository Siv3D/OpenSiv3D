//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2022 Ryo Suzuki
//	Copyright (c) 2016-2022 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# pragma once
# include "Common.hpp"
# include "Fwd.hpp"
# include "Grid.hpp"
# include "SVG.hpp"
# include "QRErrorCorrection.hpp"

namespace s3d
{
	/// @brief QR コードに関連する機能
	namespace QR
	{
		/// @brief QR コードの最小サイズを示す番号
		inline constexpr int32 MinVersion = 1;

		/// @brief QR コードの最大サイズを示す番号
		inline constexpr int32 MaxVersion = 40;

		/// @brief 数字から構成される文字列から QR データを作成します。
		/// @param s 文字列
		/// @param ec 誤り訂正レベル
		/// @param minVersion QR コードの最小サイズ
		/// @return QR データを保持する二次元配列
		[[nodiscard]]
		Grid<bool> EncodeNumber(StringView s, QRErrorCorrection ec = QRErrorCorrection::Low, int32 minVersion = MinVersion);

		/// @brief 英数字から構成される文字列から QR データを作成します。
		/// @param s 文字列
		/// @param ec 誤り訂正レベル
		/// @param minVersion QR コードの最小サイズ
		/// @return QR データを保持する二次元配列
		[[nodiscard]]
		Grid<bool> EncodeAlnum(StringView s, QRErrorCorrection ec = QRErrorCorrection::Low, int32 minVersion = MinVersion);

		/// @brief 文字列から QR データを作成します。
		/// @param s 文字列
		/// @param ec 誤り訂正レベル
		/// @param minVersion QR コードの最小サイズ
		/// @return QR データを保持する二次元配列
		[[nodiscard]]
		Grid<bool> EncodeText(StringView s, QRErrorCorrection ec = QRErrorCorrection::Low, int32 minVersion = MinVersion);

		/// @brief バイナリデータから QR データを作成します。
		/// @param data バイナリデータの先頭ポインタ
		/// @param size バイナリデータのサイズ（バイト）
		/// @param ec 誤り訂正レベル
		/// @param minVersion QR コードの最小サイズ
		/// @return QR データを保持する二次元配列
		[[nodiscard]]
		Grid<bool> EncodeBinary(const void* data, size_t size, QRErrorCorrection ec = QRErrorCorrection::Low, int32 minVersion = MinVersion);

		/// @brief QR コードを Image に変換します。
		/// @param qr QR コードを表現する二次元配列
		/// @param cellSize 1 セルの一辺のサイズ（ピクセル）
		/// @param borderCells QR コードの周囲の余白をセル何個分にするか
		/// @remark borderCells は 4 以上が推奨されています。
		/// @return 変換後の Image データ
		[[nodiscard]]
		Image MakeImage(const Grid<bool>& qr, int32 cellSize = 16, size_t borderCells = 4);

		/// @brief QR コードを SVG データに変換します。
		/// @param qr QR コードを表現する二次元配列
		/// @param borderCells QR コードの周囲の余白をセル何個分にするか
		/// @remark borderCells は 4 以上が推奨されています。
		/// @return 変換後の SVG データ
		[[nodiscard]]
		SVG MakeSVG(const Grid<bool>& qr, size_t borderCells = 4);

		/// @brief QR コードを SVG 画像ファイルとして保存します。
		/// @param path 保存するファイルパス
		/// @param qr QR コードを表現する二次元配列
		/// @param borderCells QR コードの周囲の余白をセル何個分にするか
		/// @remark borderCells は 4 以上が推奨されています。
		/// @return 保存に成功した場合 true, それ以外の場合は false
		bool SaveSVG(FilePathView path, const Grid<bool>& qr, size_t borderCells = 4);
	}
}
