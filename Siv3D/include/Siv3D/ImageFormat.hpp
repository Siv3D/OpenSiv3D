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
# include "Array.hpp"

namespace s3d
{
	/// <summary>
	/// 画像フォーマット
	/// </summary>
	enum class ImageFormat
	{
		/// <summary>
		/// 不明
		/// </summary>
		Unknown,

		/// <summary>
		/// DDS
		/// </summary>
		DDS,

		/// <summary>
		/// PNG
		/// </summary>
		PNG,

		/// <summary>
		/// JPEG
		/// </summary>
		JPEG,

		/// <summary>
		/// JPEG2000
		/// </summary>
		JPEG2000,

		/// <summary>
		/// BMP
		/// </summary>
		BMP,

		/// <summary>
		/// WebP
		/// </summary>
		WebP,

		/// <summary>
		/// GIF
		/// </summary>
		GIF,

		/// <summary>
		/// TIFF
		/// </summary>
		TIFF,

		/// <summary>
		/// TGA
		/// </summary>
		TGA,

		/// <summary>
		/// PPM
		/// </summary>
		PPM,

		/// <summary>
		/// 指定しない / データと拡張子から判断
		/// </summary>
		Unspecified = Unknown,
	};

	/// <summary>
	/// PNG フィルタ
	/// </summary>
	namespace PNGFilter
	{
		enum Flag : uint32
		{
			/// <summary>
			/// 
			/// </summary>
			None = 0x08,

			/// <summary>
			/// 
			/// </summary>
			Sub = 0x10,

			/// <summary>
			/// 
			/// </summary>
			Up = 0x20,

			/// <summary>
			/// 
			/// </summary>
			Avg = 0x40,

			/// <summary>
			/// 
			/// </summary>
			Paeth = 0x80,

			/// <summary>
			/// 
			/// </summary>
			Default = None | Sub | Up | Avg | Paeth,
		};
	};
	
	enum class PPMType
	{
		P1,
		P2,
		P3,
		P4,
		P5,
		P6,
		Ascii01 = P1,
		AsciiGray = P2,
		AsciiRGB = P3,
		Binary01 = P4,
		BinaryGray = P5,
		BinaryRGB = P6
	};

	/// <summary>
	/// WebP の圧縮方法
	/// </summary>
	enum class WebPMethod
	{
		/// <summary>
		/// 高速圧縮	(圧縮率と品質： 最低、	速度： 早い)
		/// </summary>
		Fast,

		/// <summary>
		/// 通常圧縮	(圧縮率と品質： 普通、	速度： 普通)
		/// </summary>
		Default,

		/// <summary>
		/// 高圧縮	(圧縮率と品質： 高、	速度： 遅い)
		/// </summary>
		Quality,

		/// <summary>
		/// 最高圧縮	(圧縮率と品質： 最高、	速度： 非常に遅い)
		/// </summary>
		BestQuality,
	};

	class IImageFormat
	{
	public:

		virtual ~IImageFormat() = default;

		virtual ImageFormat format() const = 0;

		virtual const Array<String>& possibleExtexsions() const = 0;

		virtual bool isHeader(const uint8(&bytes)[16]) const = 0;

		virtual Size getSize(const IReader& reader) const = 0;

		virtual Image decode(IReader& reader) const = 0;

		virtual bool encode(const Image& image, IWriter& writer) const = 0;

		virtual bool save(const Image& image, const FilePath& path) const = 0;
	};

	namespace ImageProcessing
	{
		[[nodiscard]] ImageFormat GetFormat(const FilePath& path);

		[[nodiscard]] ImageFormat GetFormat(const IReader& reader);

		[[nodiscard]] ImageFormat GetFormatFromFilePath(const FilePath& path);

		[[nodiscard]] Size GetSize(const FilePath& path);

		[[nodiscard]] Size GetSize(const IReader& reader);
	}
}
