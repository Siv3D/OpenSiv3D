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

# include <Siv3D/BinaryReader.hpp>
# include <BinaryReader/BinaryReaderDetail.hpp>

namespace s3d
{
	BinaryReader::BinaryReader()
		: pImpl(std::make_shared<BinaryReaderDetail>())
	{

	}

	bool BinaryReader::open(const FilePathView path)
	{
		return pImpl->open(path);
	}

	void BinaryReader::close()
	{
		pImpl->close();
	}

	bool BinaryReader::isOpen() const
	{
		return pImpl->isOpen();
	}

	int64 BinaryReader::size() const
	{
		return pImpl->size();
	}

	int64 BinaryReader::getPos() const
	{
		return pImpl->getPos();
	}

	bool BinaryReader::setPos(const int64 pos)
	{
		if (pos < 0 || pImpl->size() < pos)
		{
			return false;
		}

		return pImpl->setPos(pos) == pos;
	}

	int64 BinaryReader::skip(const int64 offset)
	{
		return pImpl->setPos(pImpl->getPos() + offset);
	}

	int64 BinaryReader::read(void* const buffer, const int64 size)
	{
		return pImpl->read(buffer, size);
	}

	int64 BinaryReader::read(void* const buffer, const int64 pos, const int64 size)
	{
		return pImpl->read(buffer, pos, size);
	}

	int64 BinaryReader::lookahead(void* const buffer, const int64 size) const
	{
		return pImpl->lookahead(buffer, size);
	}

	int64 BinaryReader::lookahead(void* const buffer, const int64 pos, const int64 size) const
	{
		return pImpl->lookahead(buffer, pos, size);
	}

	const FilePath& BinaryReader::path() const
	{
		return pImpl->path();
	}

	ByteArray BinaryReader::readAll()
	{
		Array<Byte> data(static_cast<size_t>(size()));

		read(data.data(), 0, size());

		return ByteArray(std::move(data));
	}
}
