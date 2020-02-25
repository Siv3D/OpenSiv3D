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
# include <Siv3D/AnimatedGIFReader.hpp>
# include <Siv3D/ByteArray.hpp>

namespace s3d
{
	class AnimatedGIFReader::AnimatedGIFReaderDetail
	{
	private:

		ByteArray m_data;

	public:

		AnimatedGIFReaderDetail();

		~AnimatedGIFReaderDetail();

		bool open(FilePathView path);

		bool open(const std::shared_ptr<IReader>& reader);

		void close();

		bool isOpen() const;

		bool read(Array<Image>& images, Array<int32>& delays, int32& duration) const;
	};
}
