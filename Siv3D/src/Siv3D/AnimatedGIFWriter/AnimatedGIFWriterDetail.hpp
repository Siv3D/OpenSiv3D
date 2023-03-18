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

# pragma once
# include <Siv3D/AnimatedGIFWriter.hpp>
# include <Siv3D/BinaryWriter.hpp>
# include <Siv3D/PointVector.hpp>
# include "GIFWriter.hpp"

namespace s3d
{
	class AnimatedGIFWriter::AnimatedGIFWriterDetail
	{
	public:

		AnimatedGIFWriterDetail();

		~AnimatedGIFWriterDetail();

		bool open(FilePathView path, Size size, Dither dither, HasAlpha hasAlpha);

		bool close();

		bool isOpen() const;

		bool writeFrame(const Image& image, int32 delay);

		size_t frameCount() const;

		Size imageSize() const;

	private:

		BinaryWriter m_writer;

		GifWriter m_gif;

		Size m_imageSize = Size{ 0, 0 };

		size_t m_frameCount = 0;

		bool m_opened = false;

		bool m_hasAlpha = true;

		bool m_dither = true;
	};
}
