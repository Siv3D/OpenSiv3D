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

# include <Siv3D/MemoryMappedFile.hpp>
# include <Siv3D/MemoryMappedFile/MemoryMappedFileDetail.hpp>

namespace s3d
{
	MemoryMappedFile::MemoryMappedFile()
		: pImpl{ std::make_shared<MemoryMappedFileDetail>() } {}

	MemoryMappedFile::MemoryMappedFile(const FilePathView path,
		const MMFOpenMode_if_Exists ifExists,
		const MMFOpenMode_if_NotFound ifNotFound)
		: MemoryMappedFile{}
	{
		open(path, ifExists, ifNotFound);
	}

	bool MemoryMappedFile::open(const FilePathView path, const MMFOpenMode_if_Exists ifExists, const MMFOpenMode_if_NotFound ifNotFound)
	{
		return pImpl->open(path, ifExists, ifNotFound);
	}

	void MemoryMappedFile::close()
	{
		pImpl->close();
	}

	bool MemoryMappedFile::isOpen() const
	{
		return pImpl->isOpen();
	}

	void MemoryMappedFile::map(const size_t offset, const size_t requestSize)
	{
		pImpl->map(offset, requestSize);
	}

	void MemoryMappedFile::unmap()
	{
		pImpl->unmap();
	}

	bool MemoryMappedFile::flush()
	{
		return pImpl->flush();
	}

	size_t MemoryMappedFile::offset() const
	{
		return pImpl->offset();
	}

	size_t MemoryMappedFile::mappedSize() const
	{
		return pImpl->mappedSize();
	}

	int64 MemoryMappedFile::fileSize() const
	{
		return pImpl->fileSize();
	}

	Byte* MemoryMappedFile::data() const
	{
		return pImpl->data();
	}

	const FilePath& MemoryMappedFile::path() const
	{
		return pImpl->path();
	}
}
