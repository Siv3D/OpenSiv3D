//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2022 Ryo Suzuki
//	Copyright (c) 2016-2022 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# pragma once
# include <memory>
# include "Common.hpp"
# include "Byte.hpp"
# include "String.hpp"
# include "PredefinedYesNo.hpp"

namespace s3d
{
	class MemoryMappedFileView
	{
	public:

		SIV3D_NODISCARD_CXX20
		MemoryMappedFileView();

		SIV3D_NODISCARD_CXX20
		explicit MemoryMappedFileView(const FilePathView path, MapAll mapAll = MapAll::Yes);

		bool open(FilePathView path, MapAll mapAll = MapAll::Yes);

		void close();

		[[nodiscard]]
		bool isOpen() const;

		[[nodiscard]]
		explicit operator bool() const;

		void map(size_t offset = 0, size_t requestSize = 0);

		void unmap();

		[[nodiscard]]
		size_t offset() const;

		[[nodiscard]]
		size_t mappedSize() const;

		[[nodiscard]]
		int64 fileSize() const;

		[[nodiscard]]
		const Byte* data() const;

		[[nodiscard]]
		const FilePath& path() const;

	private:

		class MemoryMappedFileViewDetail;

		std::shared_ptr<MemoryMappedFileViewDetail> pImpl;
	};
}
