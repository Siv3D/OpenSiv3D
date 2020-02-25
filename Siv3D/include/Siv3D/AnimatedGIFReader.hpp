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
# include <memory>
# include "Fwd.hpp"
# include "Array.hpp"

namespace s3d
{
	class AnimatedGIFReader
	{
	private:

		class AnimatedGIFReaderDetail;

		std::shared_ptr<AnimatedGIFReaderDetail> pImpl;

	public:

		AnimatedGIFReader();

		explicit AnimatedGIFReader(FilePathView path);

		template <class Reader, std::enable_if_t<std::is_base_of_v<IReader, Reader> && !std::is_lvalue_reference_v<Reader>> * = nullptr>
		explicit AnimatedGIFReader(Reader&& reader)
			: AnimatedGIFReader()
		{
			open(std::forward<Reader>(reader));
		}

		explicit AnimatedGIFReader(const std::shared_ptr<IReader>& reader);

		~AnimatedGIFReader();

		bool open(FilePathView path);

		template <class Reader, std::enable_if_t<std::is_base_of_v<IReader, Reader> && !std::is_lvalue_reference_v<Reader>> * = nullptr>
		bool open(Reader&& reader)
		{
			return open(std::make_shared<Reader>(std::forward<Reader>(reader)));
		}

		bool open(const std::shared_ptr<IReader>& reader);

		void close();

		[[nodiscard]] bool isOpen() const noexcept;

		[[nodiscard]] explicit operator bool() const noexcept;

		bool read(Array<Image>& images, Array<int32>& delays, int32& duration) const;

		[[nodiscard]] static size_t MillisecToIndex(int64 timeMillisec, const Array<int32>& delays, int32 duration) noexcept;
	};
}
