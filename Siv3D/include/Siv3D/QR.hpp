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
# include "Fwd.hpp"
# include "ByteArray.hpp"
# include "Image.hpp"
# include "Unspecified.hpp"

namespace s3d
{
	enum class QRErrorCorrection
	{
		Low,

		Medium,

		Quartile,

		High,
	};

	enum class QRMode
	{
		Numeric,

		/// <remarks>
		/// 0-9, A-Z, $ % * + - . / : と半角スペース
		/// 小文字と大文字は区別されない
		/// </remarks>
		Alnum,

		Binary,

		Kanji,
	};

	struct QRCode
	{
		Image image;

		int32 version = 0;

		QRMode mode = QRMode::Numeric;

		QRErrorCorrection ec = QRErrorCorrection::Low;

		bool save(const FilePath& path, int32 size = 512, int32 borderCells = 4);
	};

	struct QRContent
	{
		Quad quad;

		String text;

		ByteArray data;

		int32 version = 0;

		QRMode mode = QRMode::Numeric;

		QRErrorCorrection ec = QRErrorCorrection::Low;

		[[nodiscard]] explicit operator bool() const
		{
			return (version != 0);
		}

		void clear()
		{
			quad.set(0, 0, 0, 0, 0, 0, 0, 0);
			text.clear();
			data.release();
			version = 0;
			mode = QRMode::Numeric;
			ec = QRErrorCorrection::Low;
		}
	};

	class QRDecoder
	{
	private:

		class QRDecoderDetail;

		std::shared_ptr<QRDecoderDetail> pImpl;

	public:

		/// <summary>
		/// デフォルトコンストラクタ
		/// </summary>
		QRDecoder();

		/// <summary>
		/// デストラクタ
		/// </summary>
		~QRDecoder();

		bool decode(const Image& image, QRContent& content);

		bool decode(const Image& image, Array<QRContent>& contents);
	};

	namespace QR
	{
		constexpr int32 MinVersion = 1;

		constexpr int32 MaxVersion = 40;

		[[nodiscard]] size_t CalculateCapacity(int32 version, QRMode mode, QRErrorCorrection ec);

		bool EncodeNumber(QRCode& qr, StringView view, QRErrorCorrection ec = QRErrorCorrection::Low, const Optional<int32>& version = unspecified);

		bool EncodeAlnum(QRCode& qr, StringView view, QRErrorCorrection ec = QRErrorCorrection::Low, const Optional<int32>& version = unspecified);

		bool EncodeText(QRCode& qr, StringView view, QRErrorCorrection ec = QRErrorCorrection::Low, const Optional<int32>& version = unspecified);

		bool EncodeBinary(QRCode& qr, const void* data, size_t size, QRErrorCorrection ec = QRErrorCorrection::Low, const Optional<int32>& version = unspecified);

		bool EncodeBinary(QRCode& qr, ByteArrayView view, QRErrorCorrection ec = QRErrorCorrection::Low, const Optional<int32>& version = unspecified);
	}
}
