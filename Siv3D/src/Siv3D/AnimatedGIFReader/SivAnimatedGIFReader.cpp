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

# include <Siv3D/AnimatedGIFReader.hpp>
# include "AnimatedGIFReaderDetail.hpp"

namespace s3d
{
	AnimatedGIFReader::AnimatedGIFReader()
		: pImpl(std::make_shared<AnimatedGIFReaderDetail>())
	{

	}

	AnimatedGIFReader::AnimatedGIFReader(const FilePathView path)
		: AnimatedGIFReader()
	{
		open(path);
	}

	AnimatedGIFReader::AnimatedGIFReader(const std::shared_ptr<IReader>& reader)
		: AnimatedGIFReader()
	{
		open(reader);
	}

	AnimatedGIFReader::~AnimatedGIFReader()
	{

	}

	bool AnimatedGIFReader::open(const FilePathView path)
	{
		return pImpl->open(path);
	}

	bool AnimatedGIFReader::open(const std::shared_ptr<IReader>& reader)
	{
		return pImpl->open(reader);
	}

	void AnimatedGIFReader::close()
	{
		return pImpl->close();
	}

	bool AnimatedGIFReader::isOpen() const noexcept
	{
		return pImpl->isOpen();
	}

	AnimatedGIFReader::operator bool() const noexcept
	{
		return isOpen();
	}

	bool AnimatedGIFReader::read(Array<Image>& images, Array<int32>& delays, int32& duration) const
	{
		return pImpl->read(images, delays, duration);
	}

	size_t AnimatedGIFReader::MillisecToIndex(const int64 timeMillisec, const Array<int32>& delays, const int32 duration) noexcept
	{
		if (!delays || duration <= 0)
		{
			return 0;
		}

		const int64 currentTime = timeMillisec % duration;
		size_t frameIndex = 0;
		int64 sum = 0;

		for (const auto& delay: delays)
		{
			if (sum > currentTime)
			{
				return frameIndex - 1;
			}

			sum += delay;
			++frameIndex;
		}

		return (frameIndex - 1);
	}
}
