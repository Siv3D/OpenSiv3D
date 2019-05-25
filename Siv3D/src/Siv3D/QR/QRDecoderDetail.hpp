//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2019 Ryo Suzuki
//	Copyright (c) 2016-2019 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# pragma once
# include <Siv3D/QR.hpp>
# include <quirc/quirc.h>

namespace s3d
{
	class QRDecoder::QRDecoderDetail
	{
	private:

		quirc* m_quirc = nullptr;

		Size m_resolution = Size(0, 0);

	public:

		QRDecoderDetail();

		~QRDecoderDetail();

		bool decode(const Image& image, QRContent& content);

		bool decode(const Image& image, Array<QRContent>& contents);
	};
}
