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
# include <Siv3D/Fwd.hpp>
# include <Siv3D/String.hpp>

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

		//virtual ByteArray encode(const Image& image, ImageFormat format);
	};
}
