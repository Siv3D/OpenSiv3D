//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2017 Ryo Suzuki
//	Copyright (c) 2016-2017 OpenSiv3D Project
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
		ImageFormat GetFormat(const FilePath& path);

		ImageFormat GetFormat(const IReader& reader);

		ImageFormat GetFormatFromFilePath(const FilePath& path);

		Size GetSize(const FilePath& path);

		Size GetSize(const IReader& reader);
	}
}
