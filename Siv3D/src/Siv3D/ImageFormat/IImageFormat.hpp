//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2018 Ryo Suzuki
//	Copyright (c) 2016-2018 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# pragma once
# include <Siv3D/Fwd.hpp>
# include <Siv3D/String.hpp>
# include <Siv3D/ImageFormat.hpp>

namespace s3d
{
	class ISiv3DImageFormat
	{
	public:

		static ISiv3DImageFormat* Create();

		virtual ~ISiv3DImageFormat() = default;

		virtual bool init() = 0;

		virtual ImageFormat getFormatFromReader(const IReader& reader, const FilePath& pathHint) const = 0;

		virtual ImageFormat getFormatFromFilePath(const FilePath& path) const = 0;

		virtual Size getSize(const IReader& reader, const FilePath& pathHint) const = 0;

		virtual Image load(const FilePath& path) const = 0;

		virtual Image decode(IReader&& reader, ImageFormat format) const = 0;

		virtual bool save(const Image& image, ImageFormat format, const FilePath& path) const = 0;

		virtual MemoryWriter encode(const Image& image, ImageFormat format) const = 0;

		virtual bool encodePNG(IWriter& writer, const Image& image, int32 filterFlag) const = 0;

		virtual bool encodeJPEG(IWriter& writer, const Image& image, int32 quality) const = 0;

		virtual bool encodePPM(IWriter& writer, const Image& image, PPMType format) const = 0;
	};
}
