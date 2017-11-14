//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2017 Ryo Suzuki
//	Copyright (c) 2016-2017 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# include <Siv3D/BinaryReader.hpp>
# include "CBinaryReader_Windows.hpp"
# include "CBinaryReader_macOS.hpp"
# include "CBinaryReader_Linux.hpp"

namespace s3d
{
	BinaryReader::BinaryReader()
		: pImpl(std::make_shared<CBinaryReader>())
	{

	}

	bool BinaryReader::open(const FilePath& path)
	{
		return pImpl->open(path);
	}

	void BinaryReader::close()
	{
		pImpl->close();
	}

	bool BinaryReader::isOpened() const
	{
		return pImpl->isOpened();
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

	//ByteArray BinaryReader::readWhole()
	//{
	//	return readSubset(0, size());
	//}

	//ByteArray BinaryReader::readSubset(const int64 size)
	//{
	//	const int64 pos = getPos();
	//	const int64 readBytes = Clamp<int64>(size, 0, std::max(this->size() - pos, 0LL));

	//	return readSubset(pos, readBytes);
	//}

	//ByteArray BinaryReader::readSubset(const int64 pos, const int64 size)
	//{
	//	if (pos != pImpl->setPos(pos))
	//	{
	//		return ByteArray{};
	//	}

	//	const int64 readBytes = Clamp<int64>(size, 0, std::max(this->size() - pos, 0LL));

	//	if (readBytes < 0 || pos < 0)
	//	{
	//		return ByteArray{};
	//	}

	//	Array<uint8> buffer(static_cast<size_t>(readBytes));

	//	pImpl->read(buffer.data(), readBytes);

	//	return ByteArray{ std::move(buffer) };
	//}

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
