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
# include <memory>
# include "Common.hpp"
# include "QRContent.hpp"

namespace s3d
{
	/// @brief QR コードの読み取り
	class QRScanner
	{
	public:

		SIV3D_NODISCARD_CXX20
		QRScanner();

		~QRScanner();

		/// @brief 画像中の QR コードを検出してスキャンします。
		/// @param image 画像
		/// @return スキャン結果
		[[nodiscard]]
		QRContent scanOne(const Image& image) const;

		/// @brief 画像中の QR コードを複数検出してスキャンします。
		/// @param image 画像
		/// @return スキャン結果の一覧
		[[nodiscard]]
		Array<QRContent> scan(const Image& image) const;

	private:

		class QRScannerDetail;

		std::shared_ptr<QRScannerDetail> pImpl;
	};
}
