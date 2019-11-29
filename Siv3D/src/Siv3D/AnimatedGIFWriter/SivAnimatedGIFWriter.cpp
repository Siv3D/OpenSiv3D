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

# include <Siv3D/AnimatedGIFWriter.hpp>
# include "AnimatedGIFWriterDetail.hpp"

namespace s3d
{
	AnimatedGIFWriter::AnimatedGIFWriter()
		: pImpl(std::make_shared<AnimatedGIFWriterDetail>())
	{

	}

	AnimatedGIFWriter::AnimatedGIFWriter(const FilePathView path, const int32 width, const int32 height, const bool dither, const bool hasAlpha)
		: AnimatedGIFWriter(path, Size(width, height), dither, hasAlpha)
	{
	
	}

	AnimatedGIFWriter::AnimatedGIFWriter(const FilePathView path, const Size& size, const bool dither, const bool hasAlpha)
		: AnimatedGIFWriter()
	{
		open(path, size, dither, hasAlpha);
	}

	AnimatedGIFWriter::~AnimatedGIFWriter()
	{

	}

	bool AnimatedGIFWriter::open(const FilePathView path, const int32 width, const int32 height, const bool dither, const bool hasAlpha)
	{
		return open(path, Size(width, height), dither, hasAlpha);
	}

	bool AnimatedGIFWriter::open(const FilePathView path, const Size& size, const bool dither, const bool hasAlpha)
	{
		return pImpl->open(path, size, dither, hasAlpha);
	}

	bool AnimatedGIFWriter::close()
	{
		return pImpl->close();
	}

	bool AnimatedGIFWriter::isOpened() const noexcept
	{
		return pImpl->isOpened();
	}

	AnimatedGIFWriter::operator bool() const noexcept
	{
		return isOpened();
	}

	bool AnimatedGIFWriter::writeFrame(const Image& image, const Duration& delay)
	{
		return pImpl->writeFrame(image, std::max(static_cast<int32>(delay.count() * 100.0), 1));
	}

	size_t AnimatedGIFWriter::frameCount() const noexcept
	{
		return pImpl->frameCount();
	}

	Size AnimatedGIFWriter::imageSize() const noexcept
	{
		return pImpl->imageSize();
	}
}
