//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2018 Ryo Suzuki
//	Copyright (c) 2016-2018 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# include <Siv3D/MemoryMapping.hpp>
# include "CMemoryMapping.hpp"

namespace s3d
{
	MemoryMapping::MemoryMapping()
		: pImpl(std::make_shared<CMemoryMapping>())
	{

	}

	bool MemoryMapping::open(const FilePath& path, const bool mapAll)
	{
		return pImpl->open(path, mapAll);
	}

	void MemoryMapping::close()
	{
		pImpl->close();
	}

	bool MemoryMapping::isOpened() const
	{
		return pImpl->isOpened();
	}

	void MemoryMapping::map(const size_t offset, const size_t requestSize)
	{
		pImpl->map(offset, requestSize);
	}

	void MemoryMapping::unmap()
	{
		pImpl->unmap();
	}

	size_t MemoryMapping::offset() const
	{
		return pImpl->offset();
	}

	size_t MemoryMapping::mappedSize() const
	{
		return pImpl->mappedSize();
	}

	int64 MemoryMapping::fileSize() const
	{
		return pImpl->fileSize();
	}

	const Byte* MemoryMapping::data() const
	{
		return pImpl->data();
	}

	const FilePath& MemoryMapping::path() const
	{
		return pImpl->path();
	}
}
