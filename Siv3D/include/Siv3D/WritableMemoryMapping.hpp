﻿//-----------------------------------------------
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
	enum class MMFOpenMode_if_Exists
	{
		Fail,

		JustOpen,

		MapAll,

		Truncate,
	};

	enum class MMFOpenMode_if_NotFound
	{
		Fail,

		Create,
	};

	class WritableMemoryMapping
	{
	private:

		class CWritableMemoryMapping;

		std::shared_ptr<CWritableMemoryMapping> pImpl;

	public:

		/// <summary>
		/// デフォルトコンストラクタ
		/// </summary>
		WritableMemoryMapping();

		explicit WritableMemoryMapping(const FilePath& path,
			MMFOpenMode_if_Exists ifExists = MMFOpenMode_if_Exists::Truncate,
			MMFOpenMode_if_NotFound ifNotFound = MMFOpenMode_if_NotFound::Create)
			: WritableMemoryMapping()
		{
			open(path, ifExists, ifNotFound);
		}

		bool open(const FilePath& path,
			MMFOpenMode_if_Exists ifExists = MMFOpenMode_if_Exists::Truncate,
			MMFOpenMode_if_NotFound ifNotFound = MMFOpenMode_if_NotFound::Create);

		void close();

		[[nodiscard]] bool isOpened() const;

		[[nodiscard]] explicit operator bool() const
		{
			return isOpened();
		}

		void map(size_t offset = 0, size_t requestSize = 0);

		void unmap();

		bool flush();

		[[nodiscard]] size_t offset() const;

		[[nodiscard]] size_t mappedSize() const;

		[[nodiscard]] int64 fileSize() const;

		[[nodiscard]] Byte* data() const;

		[[nodiscard]] const FilePath& path() const;
	};
}
