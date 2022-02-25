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
# include "Common.hpp"
# include "String.hpp"
# include "Array.hpp"
# include "Blob.hpp"
# include "MemoryReader.hpp"

namespace s3d
{
	/// @brief ZIP アーカイブファイルの読み込み
	class ZIPReader
	{
	public:

		SIV3D_NODISCARD_CXX20
		ZIPReader();

		SIV3D_NODISCARD_CXX20
		explicit ZIPReader(FilePathView path);

		~ZIPReader();

		bool open(FilePathView path);

		void close();

		[[nodiscard]]
		bool isOpen() const noexcept;

		[[nodiscard]]
		explicit operator bool() const noexcept;

		[[nodiscard]]
		const Array<FilePath>& enumPaths() const;

		bool extractAll(FilePathView targetDirectory) const;

		bool extractFiles(StringView pattern, FilePathView targetDirectory) const;

		[[nodiscard]]
		MemoryReader extract(FilePathView filePath) const;

		[[nodiscard]]
		Blob extractToBlob(FilePathView filePath) const;

	private:

		class ZIPReaderDetail;

		std::shared_ptr<ZIPReaderDetail> pImpl;
	};
}
