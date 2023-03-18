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

# include <Siv3D/MemoryMappedFileView.hpp>
# include <Siv3D/MemoryMappedFileView/MemoryMappedFileViewDetail.hpp>

namespace s3d
{
	MemoryMappedFileView::MemoryMappedFileView()
		: pImpl{ std::make_shared<MemoryMappedFileViewDetail>() } {}

	MemoryMappedFileView::MemoryMappedFileView(const FilePathView path, const MapAll mapAll)
		: MemoryMappedFileView{}
	{
		open(path, mapAll);
	}

	bool MemoryMappedFileView::open(const FilePathView path, const MapAll mapAll)
	{
		return pImpl->open(path, mapAll);
	}

	void MemoryMappedFileView::close()
	{
		pImpl->close();
	}

	bool MemoryMappedFileView::isOpen() const
	{
		return pImpl->isOpen();
	}

	MemoryMappedFileView::operator bool() const
	{
		return isOpen();
	}

	void MemoryMappedFileView::map(const size_t offset, const size_t requestSize)
	{
		pImpl->map(offset, requestSize);
	}

	void MemoryMappedFileView::unmap()
	{
		pImpl->unmap();
	}

	size_t MemoryMappedFileView::offset() const
	{
		return pImpl->offset();
	}

	size_t MemoryMappedFileView::mappedSize() const
	{
		return pImpl->mappedSize();
	}

	int64 MemoryMappedFileView::fileSize() const
	{
		return pImpl->fileSize();
	}

	const Byte* MemoryMappedFileView::data() const
	{
		return pImpl->data();
	}

	const FilePath& MemoryMappedFileView::path() const
	{
		return pImpl->path();
	}
}
