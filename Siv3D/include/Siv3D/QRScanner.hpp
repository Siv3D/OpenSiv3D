//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2021 Ryo Suzuki
//	Copyright (c) 2016-2021 OpenSiv3D Project
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
	class QRScanner
	{
	public:

		SIV3D_NODISCARD_CXX20
		QRScanner();

		~QRScanner();

		QRContent scanOne(const Image& image);

		Array<QRContent> scan(const Image& image);

	private:

		class QRScannerDetail;

		std::shared_ptr<QRScannerDetail> pImpl;
	};
}
