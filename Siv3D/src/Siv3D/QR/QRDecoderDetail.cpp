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

# include "QRDecoderDetail.hpp"

namespace s3d
{
	QRDecoder::QRDecoderDetail::QRDecoderDetail()
		: m_quirc(::quirc_new())
	{

	}

	QRDecoder::QRDecoderDetail::~QRDecoderDetail()
	{
		if (m_quirc)
		{
			::quirc_destroy(m_quirc);
		}
	}

	bool QRDecoder::QRDecoderDetail::decode(const Image& image, QRContent& content)
	{
		if (image.width() <= 16 || image.height() <= 16)
		{
			content.clear();
			return false;
		}

		if (image.size() != m_resolution)
		{
			::quirc_resize(m_quirc, image.width(), image.height());

			m_resolution = image.size();
		}

		uint8* p = ::quirc_begin(m_quirc, nullptr, nullptr);

		for (const auto& pixel : image)
		{
			*(p++) = pixel.grayscale0_255();
		}

		::quirc_end(m_quirc);

		const int32 num_codes = ::quirc_count(m_quirc);

		if (!num_codes)
		{
			content.clear();
			return false;
		}

		quirc_code qcode;
		::quirc_extract(m_quirc, 0, &qcode);

		quirc_data qdata;

		if (::quirc_decode(&qcode, &qdata))
		{
			content.clear();
			return false;
		}

		for (size_t i = 0; i < 4; ++i)
		{
			content.quad.p(i).set(qcode.corners[i].x, qcode.corners[i].y);
		}
		
		content.version	= qdata.version;
		content.ec		= static_cast<QRErrorCorrection>(qdata.ecc_level);
		
		const int32 mode = qdata.data_type;

		const void* pData = static_cast<const void*>(qdata.payload);
		const size_t size = qdata.payload_len;

		if (mode == QUIRC_DATA_TYPE_NUMERIC)
		{
			content.text = Unicode::WidenAscii(std::string_view(static_cast<const char*>(pData), size));
			content.mode = QRMode::Numeric;
		}
		else if (mode == QUIRC_DATA_TYPE_ALPHA)
		{
			content.text = Unicode::WidenAscii(std::string_view(static_cast<const char*>(pData), size));
			content.mode = QRMode::Alnum;
		}
		else if (mode == QUIRC_DATA_TYPE_BYTE)
		{
			content.text = Unicode::FromUTF8(std::string_view(static_cast<const char*>(pData), size));
			content.data.create(pData, size);
			content.mode = QRMode::Binary;
		}
		else // QUIRC_DATA_TYPE_KANJI
		{
			// [Siv3D ToDo] macOS / Linux 対応
			content.text = Unicode::Widen(std::string_view(static_cast<const char*>(pData), size));
			content.data.create(pData, size);
			content.mode = QRMode::Kanji;
		}

		return true;
	}

	bool QRDecoder::QRDecoderDetail::decode(const Image& image, Array<QRContent>& contents)
	{
		if (image.width() <= 16 || image.height() <= 16)
		{
			return false;
		}

		if (image.size() != m_resolution)
		{
			::quirc_resize(m_quirc, image.width(), image.height());

			m_resolution = image.size();
		}

		uint8* p = ::quirc_begin(m_quirc, nullptr, nullptr);

		for (const auto& pixel : image)
		{
			*(p++) = pixel.grayscale0_255();
		}

		::quirc_end(m_quirc);

		const int32 num_codes = ::quirc_count(m_quirc);

		contents.resize(num_codes);

		if (!num_codes)
		{
			return false;
		}

		quirc_code qcode;

		for (int32 index = 0; index < num_codes; ++index)
		{
			auto& content = contents[index];

			::quirc_extract(m_quirc, 0, &qcode);

			quirc_data qdata;

			if (::quirc_decode(&qcode, &qdata))
			{
				return false;
			}

			for (size_t i = 0; i < 4; ++i)
			{
				content.quad.p(i).set(qcode.corners[i].x, qcode.corners[i].y);
			}

			content.version = qdata.version;
			content.ec = static_cast<QRErrorCorrection>(qdata.ecc_level);

			const int32 mode = qdata.data_type;

			const void* pData = static_cast<const void*>(qdata.payload);
			const size_t size = qdata.payload_len;

			if (mode == QUIRC_DATA_TYPE_NUMERIC)
			{
				content.text = Unicode::WidenAscii(std::string_view(static_cast<const char*>(pData), size));
				content.mode = QRMode::Numeric;
			}
			else if (mode == QUIRC_DATA_TYPE_ALPHA)
			{
				content.text = Unicode::WidenAscii(std::string_view(static_cast<const char*>(pData), size));
				content.mode = QRMode::Alnum;
			}
			else if (mode == QUIRC_DATA_TYPE_BYTE)
			{
				content.text = Unicode::FromUTF8(std::string_view(static_cast<const char*>(pData), size));
				content.data.create(pData, size);
				content.mode = QRMode::Binary;
			}
			else // QUIRC_DATA_TYPE_KANJI
			{
				// [Siv3D ToDo] macOS / Linux 対応
				content.text = Unicode::Widen(std::string_view(static_cast<const char*>(pData), size));
				content.data.create(pData, size);
				content.mode = QRMode::Kanji;
			}
		}

		return true;
	}
}
