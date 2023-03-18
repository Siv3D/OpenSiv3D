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
# include <fstream>
# include <Siv3D/BinaryReader.hpp>
# include <Siv3D/String.hpp>
# include <Siv3D/NonNull.hpp>

namespace s3d
{
	class BinaryReader::BinaryReaderDetail
	{
	private:
		
		struct File
		{
			std::ifstream file;
			int64 pos = 0;
		} m_file;
		
		struct Info
		{
			bool isOpen = false;
			int64 size = 0;
			FilePath fullPath;
		} m_info;
		
	public:

		BinaryReaderDetail();

		~BinaryReaderDetail();

		bool open(FilePathView path);

		void close();

		bool isOpen() const noexcept;

		int64 size() const noexcept;

		int64 setPos(int64 clampedPos);

		int64 getPos();

		int64 read(NonNull<void*> buffer, int64 size);

		int64 read(NonNull<void*> buffer, int64 pos, int64 size);

		int64 lookahead(NonNull<void*> buffer, int64 size);

		int64 lookahead(NonNull<void*> buffer, int64 pos, int64 size);

		const FilePath& path() const noexcept;
	};
}
