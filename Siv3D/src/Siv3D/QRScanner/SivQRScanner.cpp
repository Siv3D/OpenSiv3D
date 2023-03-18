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

# include <Siv3D/QRScanner.hpp>
# include <Siv3D/QRScanner/QRScannerDetail.hpp>

namespace s3d
{
	QRScanner::QRScanner()
		: pImpl{ std::make_shared<QRScannerDetail>() } {}

	QRScanner::~QRScanner()
	{
		// do nothing
	}

	QRContent QRScanner::scanOne(const Image& image) const
	{
		return pImpl->scanOne(image);
	}

	Array<QRContent> QRScanner::scan(const Image& image) const
	{
		return pImpl->scan(image);
	}
}
