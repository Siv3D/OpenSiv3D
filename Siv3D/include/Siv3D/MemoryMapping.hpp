//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2017 Ryo Suzuki
//	Copyright (c) 2016-2017 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# pragma once
# include <memory>
# include "Fwd.hpp"

namespace s3d
{
	class MemoryMapping
	{
	private:

		class CMemoryMapping;

		std::shared_ptr<CMemoryMapping> pImpl;

	public:

		/// <summary>
		/// デフォルトコンストラクタ
		/// </summary>
		MemoryMapping();

		explicit MemoryMapping(const FilePath& path, bool mapAll = true)
			: MemoryMapping()
		{
			open(path, mapAll);
		}

		bool open(const FilePath& path, bool mapAll = true);

		void close();

		[[nodiscard]] bool isOpened() const;

		[[nodiscard]] explicit operator bool() const
		{
			return isOpened();
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
