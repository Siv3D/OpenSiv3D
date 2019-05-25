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

# include <Siv3D/MemoryWriter.hpp>
# include <Siv3D/BinaryWriter.hpp>
# include <Siv3D/ReaderView.hpp>
# include "MemoryWriterDetail.hpp"

namespace s3d
{
	MemoryWriter::MemoryWriter()
		: pImpl(std::make_shared<MemoryWriterDetail>())
	{

	}

	void MemoryWriter::clear()
	{
		return pImpl->clear();
	}

	void MemoryWriter::release()
	{
		return pImpl->release();
	}

	int64 MemoryWriter::size() const
	{
		return pImpl->size();
	}

	int64 MemoryWriter::getPos() const
	{
		return pImpl->getPos();
	}

	bool MemoryWriter::setPos(const int64 pos)
	{
		if (pos < 0 || pImpl->size() < pos)
		{
			return false;
		}

		return pImpl->setPos(pos) == pos;
	}

	int64 MemoryWriter::seekEnd()
	{
		return pImpl->setPos(pImpl->size());
	}

	int64 MemoryWriter::write(const void* src, const size_t size)
	{
		return pImpl->write(src, size);
	}

	const Byte* MemoryWriter::data() const
	{
		return pImpl->data();
	}

	bool MemoryWriter::save(const FilePath& path) const
	{
		return BinaryWriter(path).write(pImpl->data(), static_cast<size_t>(pImpl->size())) == pImpl->size();
	}

	ByteArrayView MemoryWriter::view() const
	{
		return ByteArrayView(pImpl->data(), static_cast<size_t>(pImpl->size()));
	}

	ByteArray MemoryWriter::retrieve()
	{
		return pImpl->retrieve();
	}
}
