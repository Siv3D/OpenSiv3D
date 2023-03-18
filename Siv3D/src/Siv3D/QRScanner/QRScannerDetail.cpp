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

# include <Siv3D/Image.hpp>
# include <Siv3D/EngineLog.hpp>
# include <Siv3D/Unicode.hpp>
# include "QRScannerDetail.hpp"

namespace s3d
{
	QRScanner::QRScannerDetail::QRScannerDetail() 
		: m_quirc{ ::quirc_new() } {}

	QRScanner::QRScannerDetail::~QRScannerDetail()
	{
		if (m_quirc)
		{
			::quirc_destroy(m_quirc);
			m_quirc = nullptr;
		}
	}

	QRContent QRScanner::QRScannerDetail::scanOne(const Image& image)
	{
		Array<QRContent> contents = scan(image);

		if (not contents)
		{
			return{};
		}

		// 最大面積のものを返す
		{
			size_t index = 0;
			double maxArea = 0.0;

			for (size_t i = 0; i < contents.size(); ++i)
			{
				const auto& c = contents[i];

				if (not c.isValid())
				{
					continue;
				}

				if (const double area = c.quad.area();
					maxArea < area)
				{
					maxArea = area;
					index = i;
				}
			}

			return contents[index];
		}
	}

	Array<QRContent> QRScanner::QRScannerDetail::scan(const Image& image)
	{
		// Image のサイズが小さければ失敗
		if (image.width() <= 16 || image.height() <= 16)
		{
			return{};
		}

		// 内部バッファと異なるサイズの場合リサイズ
		if (image.size() != m_imageBufferSize)
		{
			::quirc_resize(m_quirc, image.width(), image.height());
			m_imageBufferSize = image.size();
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
		
		if (num_codes == 0)
		{
			return{};
		}

		quirc_code qcode;

		Array<QRContent> results;

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

			if (not err)
			{
				content.version = qdata.version;
				content.ec = ToEnum<QRErrorCorrection>(static_cast<uint8>(qdata.ecc_level));

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
					content.binary.create(pData, view.size());
					content.mode = QRMode::Binary;
				}
				else // QUIRC_DATA_TYPE_KANJI
				{
					// [Siv3D ToDo] macOS / Linux 対応
					content.text = Unicode::Widen(view);
					content.binary.create(pData, view.size());
					content.mode = QRMode::Kanji;
				}
			}

			results << content;
		}

		return results;
	}
}
