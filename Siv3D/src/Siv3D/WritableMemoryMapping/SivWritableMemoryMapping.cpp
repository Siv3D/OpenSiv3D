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

# include <Siv3D/WritableMemoryMapping.hpp>
# include <WritableMemoryMapping/WritableMemoryMappingDetail.hpp>

namespace s3d
{
	WritableMemoryMapping::WritableMemoryMapping()
		: pImpl(std::make_shared<WritableMemoryMappingDetail>())
	{

	}

	WritableMemoryMapping::WritableMemoryMapping(const FilePath& path,
		const MMFOpenMode_if_Exists ifExists,
		const MMFOpenMode_if_NotFound ifNotFound)
		: WritableMemoryMapping()
	{
		open(path, ifExists, ifNotFound);
	}

	bool WritableMemoryMapping::open(const FilePath& path, const MMFOpenMode_if_Exists ifExists, const MMFOpenMode_if_NotFound ifNotFound)
	{
		return pImpl->open(path, ifExists, ifNotFound);
	}

	void WritableMemoryMapping::close()
	{
		pImpl->close();
	}

	bool WritableMemoryMapping::isOpened() const
	{
		return pImpl->isOpened();
	}

	void WritableMemoryMapping::map(const size_t offset, const size_t requestSize)
	{
		pImpl->map(offset, requestSize);
	}

	void WritableMemoryMapping::unmap()
	{
		pImpl->unmap();
	}

	bool WritableMemoryMapping::flush()
	{
		return pImpl->flush();
	}

	size_t WritableMemoryMapping::offset() const
	{
		return pImpl->offset();
	}

	size_t WritableMemoryMapping::mappedSize() const
	{
		return pImpl->mappedSize();
	}

	int64 WritableMemoryMapping::fileSize() const
	{
		return pImpl->fileSize();
	}

	Byte* WritableMemoryMapping::data() const
	{
		return pImpl->data();
	}

	const FilePath& WritableMemoryMapping::path() const
	{
		return pImpl->path();
	}
}
