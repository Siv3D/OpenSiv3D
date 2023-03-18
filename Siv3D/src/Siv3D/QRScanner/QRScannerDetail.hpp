//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2023 Ryo Suzuki
//	Copyright (c) 2016-2023 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# pragma once
# include <Siv3D/QRScanner.hpp>
# include <Siv3D/PointVector.hpp>
# include <ThirdParty/quirc/quirc.h>

namespace s3d
{
	class QRScanner::QRScannerDetail
	{
	public:

		QRScannerDetail();

		~QRScannerDetail();

		QRContent scanOne(const Image& image);

		Array<QRContent> scan(const Image& image);

	private:

		quirc* m_quirc = nullptr;

		Size m_imageBufferSize = Size{ 0, 0 };
	};
}
