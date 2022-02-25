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
# include "String.hpp"
# include "Byte.hpp"

namespace s3d
{
	enum class MMFOpenMode_if_Exists : uint8
	{
		Fail,

		JustOpen,

		MapAll,

		Truncate,
	};

	enum class MMFOpenMode_if_NotFound : uint8
	{
		Fail,

		Create,
	};

	class MemoryMappedFile
	{
	public:

		SIV3D_NODISCARD_CXX20
		MemoryMappedFile();

		SIV3D_NODISCARD_CXX20
		explicit MemoryMappedFile(FilePathView path,
			MMFOpenMode_if_Exists ifExists = MMFOpenMode_if_Exists::Truncate,
			MMFOpenMode_if_NotFound ifNotFound = MMFOpenMode_if_NotFound::Create);

		bool open(FilePathView path,
			MMFOpenMode_if_Exists ifExists = MMFOpenMode_if_Exists::Truncate,
			MMFOpenMode_if_NotFound ifNotFound = MMFOpenMode_if_NotFound::Create);

		void close();

		[[nodiscard]]
		bool isOpen() const;

		[[nodiscard]]
		explicit operator bool() const;

		void map(size_t offset = 0, size_t requestSize = 0);

		void unmap();

		bool flush();

		[[nodiscard]]
		size_t offset() const;

		[[nodiscard]]
		size_t mappedSize() const;

		[[nodiscard]]
		int64 fileSize() const;

		[[nodiscard]]
		Byte* data() const;

		[[nodiscard]]
		const FilePath& path() const;

	private:

		class MemoryMappedFileDetail;

		std::shared_ptr<MemoryMappedFileDetail> pImpl;
	};
}

