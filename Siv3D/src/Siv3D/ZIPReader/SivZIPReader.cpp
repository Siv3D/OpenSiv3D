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

# include <Siv3D/ZIPReader.hpp>
# include "ZIPReaderDetail.hpp"

namespace s3d
{
	ZIPReader::ZIPReader()
		: pImpl{ std::make_shared<ZIPReaderDetail>() }
	{

	}

	ZIPReader::ZIPReader(const FilePathView path)
		: ZIPReader{}
	{
		open(path);
	}

	ZIPReader::~ZIPReader()
	{
		// do nothing
	}

	bool ZIPReader::open(const FilePathView path)
	{
		return pImpl->open(path);
	}

	void ZIPReader::close()
	{
		pImpl->close();
	}

	bool ZIPReader::isOpen() const noexcept
	{
		return pImpl->isOpen();
	}

	ZIPReader::operator bool() const noexcept
	{
		return pImpl->isOpen();
	}

	const Array<FilePath>& ZIPReader::enumPaths() const
	{
		return pImpl->enumPaths();
	}

	bool ZIPReader::extractAll(const FilePathView targetDirectory) const
	{
		return pImpl->extractAll(targetDirectory);
	}

	bool ZIPReader::extractFiles(const StringView pattern, const FilePathView targetDirectory) const
	{
		return pImpl->extract(pattern, targetDirectory);
	}

	MemoryReader ZIPReader::extract(const FilePathView filePath) const
	{
		return MemoryReader{ pImpl->extractToBlob(filePath) };
	}

	Blob ZIPReader::extractToBlob(const FilePathView filePath) const
	{
		return pImpl->extractToBlob(filePath);
	}
}
