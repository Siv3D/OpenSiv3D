//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (C) 2008-2016 Ryo Suzuki
//	Copyright (C) 2016 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# include <Siv3D/ByteArray.hpp>
# include <Siv3D/BinaryWriter.hpp>
# include "CByteArray.hpp"

namespace s3d
{
	ByteArray::ByteArray()
		: pImpl(std::make_shared<CByteArray>())
	{

	}

	bool ByteArray::create(const FilePath& path)
	{
		return pImpl->create(path);
	}

	bool ByteArray::create(const void* src, const size_t size)
	{
		return pImpl->create(src, size);
	}

	bool ByteArray::create(const Array<uint8>& data)
	{
		return pImpl->create(data.data(), data.size());
	}

	bool ByteArray::create(Array<uint8>&& data)
	{
		return pImpl->create(std::move(data));
	}

	void ByteArray::release()
	{
		return pImpl->release();
	}

	bool ByteArray::isOpened() const
	{
		return pImpl->isOpened();
	}

	int64 ByteArray::size() const
	{
		return pImpl->size();
	}

	int64 ByteArray::getPos() const
	{
		return pImpl->getPos();
	}

	bool ByteArray::setPos(const int64 pos)
	{
		if (pos < 0 || pImpl->size() < pos)
		{
			return false;
		}

		pImpl->setPos(pos);

		return true;
	}

	int64 ByteArray::skip(const int64 offset)
	{
		return pImpl->setPos(pImpl->getPos() + offset);
	}

	const uint8* ByteArray::data() const
	{
		return pImpl->data();
	}

	int64 ByteArray::read(void* const dst, const int64 size)
	{
		return pImpl->read(dst, size);
	}

	int64 ByteArray::read(void* const dst, const int64 pos, const int64 size)
	{
		return pImpl->read(dst, pos, size);
	}

	int64 ByteArray::lookahead(void* const dst, const int64 size) const
	{
		return pImpl->lookahead(dst, size);
	}

	int64 ByteArray::lookahead(void* const dst, const int64 pos, const int64 size) const
	{
		return pImpl->lookahead(dst, pos, size);
	}

	bool ByteArray::save(const FilePath& path) const
	{
		const int64 size = pImpl->size();

		return (BinaryWriter(path).write(pImpl->data(), static_cast<size_t>(size)) == size);
	}
}
