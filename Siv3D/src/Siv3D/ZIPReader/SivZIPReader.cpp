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

# include <Siv3D/ZIPReader.hpp>
# include <Siv3D/ByteArray.hpp>
# include "ZIPReaderDetail.hpp"

namespace s3d
{
	ZIPReader::ZIPReader()
		: pImpl(std::make_shared<ZIPReaderDetail>())
	{

	}

	ZIPReader::ZIPReader(const FilePathView path)
		: ZIPReader()
	{
		open(path);
	}

	ZIPReader::~ZIPReader()
	{

	}

	bool ZIPReader::open(const FilePathView path)
	{
		return pImpl->open(path);
	}

	void ZIPReader::close()
	{
		pImpl->close();
	}

	bool ZIPReader::isOpen() const
	{
		return pImpl->isOpen();
	}

	ZIPReader::operator bool() const
	{
		return isOpen();
	}

	const Array<FilePath>& ZIPReader::enumPaths() const
	{
		return pImpl->enumPaths();
	}

	bool ZIPReader::extractAll(const FilePathView targetDirectory) const
	{
		return pImpl->extractAll(targetDirectory);
	}

	bool ZIPReader::extract(const StringView pattern, const FilePathView targetDirectory) const
	{
		return pImpl->extract(pattern, targetDirectory);
	}

	ByteArray ZIPReader::extractToMemory(const FilePathView filePath) const
	{
		return pImpl->extractToMemory(filePath);
	}
}
