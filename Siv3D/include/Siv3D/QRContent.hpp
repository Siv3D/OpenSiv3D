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
# include "Blob.hpp"
# include "QRMode.hpp"
# include "QRErrorCorrection.hpp"
# include "2DShapes.hpp"

namespace s3d
{
	/// @brief QR コードのスキャン結果
	struct QRContent
	{
		/// @brief 画像中の QR コードの領域
		Quad quad = Quad{ {0, 0}, {0, 0}, {0, 0}, {0, 0} };

		/// @brief テキスト
		String text;

		/// @brief バイナリ
		Blob binary;

		/// @brief QR コードのサイズ（バージョン）
		int32 version = 0;

		/// @brief QR コードのデータの種類
		QRMode mode = QRMode::Invalid;

		/// @brief QR コードの誤り訂正レベル
		QRErrorCorrection ec = QRErrorCorrection::Low;

		/// @brief スキャン結果が有効なデータであるかを返します。
		/// @return 有効なデータの場合 true, それ以外の場合は false
		[[nodiscard]]
		bool isValid() const noexcept;

		/// @brief スキャン結果が有効なデータであるかを返します。
		/// @remark `isValid()` と同じです。
		/// @return 有効なデータの場合 true, それ以外の場合は false
		[[nodiscard]]
		explicit operator bool() const noexcept;

		/// @brief スキャン結果をクリアします。
		void clear();
	};
}

# include "detail/QRContent.ipp"
