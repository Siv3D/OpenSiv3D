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
# include "Array.hpp"

namespace s3d
{
	/// @brief GIF アニメーションの読み込み
	class AnimatedGIFReader
	{
	public:

		/// @brief 
		SIV3D_NODISCARD_CXX20
		AnimatedGIFReader();

		/// @brief 
		/// @param path 
		SIV3D_NODISCARD_CXX20
		explicit AnimatedGIFReader(FilePathView path);

		/// @brief 
		/// @param reader 
		SIV3D_NODISCARD_CXX20
		explicit AnimatedGIFReader(IReader&& reader);

		~AnimatedGIFReader();

		bool open(FilePathView path);

		bool open(IReader&& reader);

		void close();

		[[nodiscard]]
		bool isOpen() const noexcept;

		[[nodiscard]]
		explicit operator bool() const noexcept;

		bool read(Array<Image>& images, Array<int32>& delays, int32& duration) const;

		[[nodiscard]]
		static size_t MillisecToIndex(int64 timeMillisec, const Array<int32>& delays, int32 duration) noexcept;

	private:

		class AnimatedGIFReaderDetail;

		std::shared_ptr<AnimatedGIFReaderDetail> pImpl;
	};
}
