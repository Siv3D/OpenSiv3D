//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (C) 2008-2017 Ryo Suzuki
//	Copyright (C) 2016-2017 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# include <Siv3D/BinaryWriter.hpp>
# include "CBinaryWriter_Windows.hpp"
# include "CBinaryWriter_macOS.hpp"
# include "CBinaryWriter_Linux.hpp"

namespace s3d
{
	BinaryWriter::BinaryWriter()
		: pImpl(std::make_shared<CBinaryWriter>())
	{

	}

	bool BinaryWriter::open(const FilePath& path, const OpenMode openMode)
	{
		return pImpl->open(path, openMode);
	}

	void BinaryWriter::flush()
	{
		pImpl->flush();
	}

	void BinaryWriter::close()
	{
		pImpl->close();
	}

	bool BinaryWriter::isOpened() const
	{
		return pImpl->isOpened();
	}

	void BinaryWriter::clear()
	{
		pImpl->clear();
	}

	int64 BinaryWriter::size() const
	{
		return pImpl->size();
	}

	int64 BinaryWriter::getPos() const
	{
		return pImpl->getPos();
	}

	bool BinaryWriter::setPos(int64 pos)
	{
		if (pos < 0 || pImpl->size() < pos)
		{
			return false;
		}

		return pImpl->setPos(pos) == pos;
	}

	int64 BinaryWriter::seekEnd()
	{
		return pImpl->setPos(pImpl->size());
	}

	int64 BinaryWriter::write(const void* const src, const size_t size)
	{
		return pImpl->write(src, size);
	}

	const FilePath& BinaryWriter::path() const
	{
		return pImpl->path();
	}
}
