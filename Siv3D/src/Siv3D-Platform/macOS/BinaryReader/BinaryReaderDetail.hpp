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
# include <Siv3D/String.hpp>
# include <Siv3D/BinaryReader.hpp>

namespace s3d
{
	class BinaryReader::BinaryReaderDetail
	{
	private:

		FILE* m_pFile = nullptr;
		
		int64 m_size = 0;
		
		FilePath m_fullPath;

	public:

		BinaryReaderDetail();

		~BinaryReaderDetail();

		bool open(FilePathView path);

		void close();

		bool isOpened() const noexcept;

		int64 size() const noexcept;

		int64 setPos(int64 pos);

		int64 getPos();

		int64 read(void* buffer, int64 size);

		int64 read(void* buffer, int64 pos, int64 size);

		int64 lookahead(void* buffer, int64 size);

		int64 lookahead(void* buffer, int64 pos, int64 size);

		const FilePath& path() const;
	};
}
