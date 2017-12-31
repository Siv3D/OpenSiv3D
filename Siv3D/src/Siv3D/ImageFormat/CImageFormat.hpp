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
# include "IImageFormat.hpp"
# include <Siv3D/Array.hpp>
# include <Siv3D/ImageFormat.hpp>

namespace s3d
{
	class CImageFormat : public ISiv3DImageFormat
	{
	private:

		Array<std::unique_ptr<IImageFormat>> m_imageFormats;

		Array<std::unique_ptr<IImageFormat>>::const_iterator findFormat(ImageFormat format) const;

		Array<std::unique_ptr<IImageFormat>>::const_iterator findFormat(const IReader& reader, const FilePath& pathHint) const;

	public:

		CImageFormat();

		~CImageFormat() override;

		bool init() override;

		ImageFormat getFormatFromReader(const IReader& reader, const FilePath& pathHint) const override;

		ImageFormat getFormatFromFilePath(const FilePath& path) const override;

		Size getSize(const IReader& reader, const FilePath& pathHint) const override;

		Image load(const FilePath& path) const override;

		Image decode(IReader&& reader, ImageFormat format) const override;

		bool save(const Image& image, ImageFormat format, const FilePath& path) const override;

		MemoryWriter encode(const Image& image, ImageFormat format) const override;

		bool encodePNG(IWriter& writer, const Image& image, int32 filterFlag) const override;

		bool encodeJPEG(IWriter& writer, const Image& image, int32 quality) const override;

		bool encodePPM(IWriter& writer, const Image& image, PPMType format) const override;
	};
}
