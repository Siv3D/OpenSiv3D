//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2021 Ryo Suzuki
//	Copyright (c) 2016-2021 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# pragma once
# include <memory>
# include "Common.hpp"
# include "StringView.hpp"
# include "PointVector.hpp"

namespace s3d
{
	class VideoPlayer
	{
	public:

		SIV3D_NODISCARD_CXX20
		VideoPlayer();

		SIV3D_NODISCARD_CXX20
		explicit VideoPlayer(FilePathView path);

		bool open(FilePathView path);

		void close();

		[[nodiscard]]
		bool isOpen() const noexcept;

		[[nodiscard]]
		explicit operator bool() const noexcept;

		bool getFrame(Image& image);

		[[nodiscard]]
		Size getSize() const noexcept;

		[[nodiscard]]
		double getFPS() const noexcept;

		[[nodiscard]]
		double getLengthSec() const;

		void setCurrentFrameIndex(int32 index);

		[[nodiscard]]
		int32 getCurrentFrameIndex() const noexcept;

		[[nodiscard]]
		double getPosSec() const;

		[[nodiscard]]
		int32 getFrameCount() const noexcept;

		[[nodiscard]]
		double getFrameDeltaSec() const noexcept;

		[[nodiscard]]
		double getProgress() const noexcept;

		[[nodiscard]]
		bool reachedEnd() const noexcept;

		[[nodiscard]]
		const FilePath& path() const noexcept;

	private:

		class VideoPlayerDetail;

		std::shared_ptr<VideoPlayerDetail> pImpl;
	};
}
