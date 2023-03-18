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

# include <Siv3D/AnimatedGIFReader.hpp>
# include "AnimatedGIFReaderDetail.hpp"

namespace s3d
{
	AnimatedGIFReader::AnimatedGIFReader()
		: pImpl{ std::make_shared<AnimatedGIFReaderDetail>() } {}

	AnimatedGIFReader::AnimatedGIFReader(const FilePathView path)
		: AnimatedGIFReader{}
	{
		open(path);
	}

	AnimatedGIFReader::AnimatedGIFReader(IReader&& reader)
		: AnimatedGIFReader()
	{
		open(std::move(reader));
	}

	AnimatedGIFReader::~AnimatedGIFReader()
	{

	}

	bool AnimatedGIFReader::open(const FilePathView path)
	{
		return pImpl->open(path);
	}

	bool AnimatedGIFReader::open(IReader&& reader)
	{
		return pImpl->open(std::move(reader));
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

	bool AnimatedGIFReader::read(Array<Image>& images, Array<int32>& delaysMillisec) const
	{
		return pImpl->read(images, delaysMillisec);
	}

	bool AnimatedGIFReader::read(Array<Image>& images, Array<int32>& delaysMillisec, int32& durationMillisec) const
	{
		if (pImpl->read(images, delaysMillisec))
		{
			durationMillisec = delaysMillisec.sum();
			
			return true;
		}
		else
		{
			return false;
		}
	}

	size_t AnimatedGIFReader::MillisecToIndex(const int64 timeMillisec, const Array<int32>& delaysMillisec) noexcept
	{
		return MillisecToIndex(timeMillisec, delaysMillisec, delaysMillisec.sum());
	}

	size_t AnimatedGIFReader::MillisecToIndex(const int64 timeMillisec, const Array<int32>& delaysMillisec, const int32 durationMillisec) noexcept
	{
		if ((not delaysMillisec) || durationMillisec <= 0)
		{
			return 0;
		}

		const int64 currentTime = (timeMillisec % durationMillisec);
		size_t frameIndex = 0;
		int64 sum = 0;

		for (const auto& delayMillisec : delaysMillisec)
		{
			if (sum > currentTime)
			{
				return frameIndex - 1;
			}

			sum += delayMillisec;
			++frameIndex;
		}

		return (frameIndex - 1);
	}

	size_t AnimatedGIFReader::GetFrameIndex(const double timeSec, const Array<int32>& delaysMillisec) noexcept
	{
		return GetFrameIndex(timeSec, delaysMillisec, delaysMillisec.sum());
	}

	size_t AnimatedGIFReader::GetFrameIndex(const double timeSec, const Array<int32>& delaysMillisec, const int32 durationMillisec) noexcept
	{
		return MillisecToIndex(static_cast<int64>(timeSec * 1000LL), delaysMillisec, durationMillisec);
	}
}