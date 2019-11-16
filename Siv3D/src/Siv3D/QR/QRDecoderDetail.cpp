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
		Array<QRContent> contents;

		if (!decode(image, contents))
		{
			return false;
		}

		if (contents.size() == 1)
		{
			content = contents.front();
			return true;
		}
		else
		{
			for (const auto& c : contents)
			{
				if (c.isValid())
				{
					content = c;
					return true;
				}
			}

			content = contents.front();
			return true;
		}
	}

	bool QRDecoder::QRDecoderDetail::decode(const Image& image, Array<QRContent>& contents)
	{
		contents.clear();

		// Image のサイズが小さければ失敗
		if (image.width() <= 16 || image.height() <= 16)
		{
			return false;
		}

		// 内部バッファと異なるサイズの場合リサイズ
		if (image.size() != m_resolution)
		{
			::quirc_resize(m_quirc, image.width(), image.height());
			m_resolution = image.size();
		}

		// 画像をバッファにコピー
		{
			uint8* p = ::quirc_begin(m_quirc, nullptr, nullptr);

			for (const auto& pixel : image)
			{
				*(p++) = pixel.grayscale0_255();
			}

			::quirc_end(m_quirc);
		}

		const int32 num_codes = ::quirc_count(m_quirc);
		if (!num_codes)
		{
			return false;
		}

		quirc_code qcode;

		for (int32 index = 0; index < num_codes; ++index)
		{
			QRContent content;

			::quirc_extract(m_quirc, index, &qcode);

			quirc_data qdata;
			const quirc_decode_error_t err = ::quirc_decode(&qcode, &qdata);

			if ((err != QUIRC_SUCCESS)
				&& (err != QUIRC_ERROR_FORMAT_ECC)
				&& (err != QUIRC_ERROR_DATA_ECC))
			{
				continue;
			}

			for (size_t i = 0; i < 4; ++i)
			{
				content.quad.p(i).set(qcode.corners[i].x, qcode.corners[i].y);
			}

			if (!err)
			{
				content.version = qdata.version;
				content.ec = static_cast<QRErrorCorrection>(qdata.ecc_level);

				const void* pData = static_cast<const void*>(qdata.payload);
				const std::string_view view(static_cast<const char*>(pData), qdata.payload_len);

				if (const int32 mode = qdata.data_type;
					mode == QUIRC_DATA_TYPE_NUMERIC)
				{
					content.text = Unicode::WidenAscii(view);
					content.mode = QRMode::Numeric;
				}
				else if (mode == QUIRC_DATA_TYPE_ALPHA)
				{
					content.text = Unicode::WidenAscii(view);
					content.mode = QRMode::Alnum;
				}
				else if (mode == QUIRC_DATA_TYPE_BYTE)
				{
					content.text = Unicode::FromUTF8(view);
					content.data.create(pData, view.size());
					content.mode = QRMode::Binary;
				}
				else // QUIRC_DATA_TYPE_KANJI
				{
					// [Siv3D ToDo] macOS / Linux 対応
					content.text = Unicode::Widen(view);
					content.data.create(pData, view.size());
					content.mode = QRMode::Kanji;
				}
			}

			contents << content;
		}

		return true;
	}
}
