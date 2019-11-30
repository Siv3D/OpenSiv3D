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
# include <Siv3D/Fwd.hpp>
# include <Siv3D/PointVector.hpp>
# include <Siv3D/AnimatedGIFWriter.hpp>
# include <Siv3D/BinaryWriter.hpp>
# include "GIFWriter.hpp"

namespace s3d
{
	class AnimatedGIFWriter::AnimatedGIFWriterDetail
	{
	private:

		BinaryWriter m_writer;

		GifWriter m_gif;

		Size m_imageSize = Size(0, 0);

		size_t m_frameCount = 0;

		bool m_opened = false;

		bool m_hasAlpha = true;

		bool m_dither = true;

	public:

		AnimatedGIFWriterDetail();

		~AnimatedGIFWriterDetail();

		bool open(FilePathView path, const Size& size, bool dither, bool hasAlpha);

		bool close();

		bool isOpened() const;

		bool writeFrame(const Image& image, int32 delay);

		size_t frameCount() const;

		Size imageSize() const;
	};
}
