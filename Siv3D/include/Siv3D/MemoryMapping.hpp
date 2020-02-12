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
# include "StringView.hpp"

namespace s3d
{
	class MemoryMapping
	{
	private:

		class MemoryMappingDetail;

		std::shared_ptr<MemoryMappingDetail> pImpl;

	public:

		/// <summary>
		/// デフォルトコンストラクタ
		/// </summary>
		MemoryMapping();

		explicit MemoryMapping(const FilePathView path, bool mapAll = true)
			: MemoryMapping()
		{
			open(path, mapAll);
		}

		bool open(FilePathView path, bool mapAll = true);

		void close();

		[[nodiscard]] bool isOpen() const;

		[[nodiscard]] explicit operator bool() const
		{
			return isOpen();
		}

		void map(size_t offset = 0, size_t requestSize = 0);

		void unmap();

		[[nodiscard]] size_t offset() const;

		[[nodiscard]] size_t mappedSize() const;

		[[nodiscard]] int64 fileSize() const;

		[[nodiscard]] const Byte* data() const;

		[[nodiscard]] const FilePath& path() const;
	};
}
