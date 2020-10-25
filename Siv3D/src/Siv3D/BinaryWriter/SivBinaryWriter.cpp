//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2020 Ryo Suzuki
//	Copyright (c) 2016-2020 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# include <Siv3D/BinaryWriter.hpp>
# include <Siv3D/BinaryWriter/BinaryWriterDetail.hpp>

namespace s3d
{
	BinaryWriter::BinaryWriter()
		: pImpl(std::make_shared<BinaryWriterDetail>())
	{

	}

	bool BinaryWriter::open(const FilePathView path, const OpenMode openMode)
	{
		return pImpl->open(path, openMode);
	}

	void BinaryWriter::close()
	{
		pImpl->close();
	}

	bool BinaryWriter::isOpen() const noexcept
	{
		return pImpl->isOpen();
	}

	void BinaryWriter::flush()
	{
		pImpl->flush();
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

	bool BinaryWriter::setPos(const int64 pos)
	{
		if (not InRange<int64>(pos, 0, pImpl->size()))
		{
			return false;
		}

		return (pImpl->setPos(pos) == pos);
	}

	int64 BinaryWriter::seekToEnd()
	{
		return pImpl->setPos(pImpl->size());
	}

	int64 BinaryWriter::write(const void* src, const int64 size)
	{
		if ((src == nullptr) || (size <= 0))
		{
			return 0;
		}

		return pImpl->write(NonNull{ src }, size);
	}

	const FilePath& BinaryWriter::path() const noexcept
	{
		return pImpl->path();
	}
}
