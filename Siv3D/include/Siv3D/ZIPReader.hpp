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
# include "Fwd.hpp"
# include "Array.hpp"
# include "String.hpp"

namespace s3d
{
	class ZIPReader
	{
	private:

		class ZIPReaderDetail;

		std::shared_ptr<ZIPReaderDetail> pImpl;

	public:

		ZIPReader();

		explicit ZIPReader(FilePathView path);

		~ZIPReader();

		bool open(FilePathView path);

		void close();

		bool isOpen() const;

		explicit operator bool() const;

		const Array<FilePath>& enumPaths() const;

		bool extractAll(FilePathView targetDirectory) const;

		bool extract(StringView pattern, FilePathView targetDirectory) const;

		[[nodiscard]] ByteArray extractToMemory(FilePathView filePath) const;
	};
}
