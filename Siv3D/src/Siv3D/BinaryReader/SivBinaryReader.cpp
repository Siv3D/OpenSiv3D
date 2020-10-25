﻿//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2020 Ryo Suzuki
//	Copyright (c) 2016-2020 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# include <Siv3D/BinaryReader.hpp>
# include <Siv3D/BinaryReader/BinaryReaderDetail.hpp>

namespace s3d
{
	BinaryReader::BinaryReader()
		: pImpl(std::make_shared<BinaryReaderDetail>())
	{

	}

	bool BinaryReader::open(const FilePathView path, const OpenMode openMode)
	{
		return pImpl->open(path, openMode);
	}

	void BinaryReader::close()
	{
		pImpl->close();
	}

	bool BinaryReader::isOpen() const noexcept
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
		if (not InRange<int64>(pos, 0, pImpl->size()))
		{
			return false;
		}

		return (pImpl->setPos(pos) == pos);
	}

	int64 BinaryReader::skip(const int64 offset)
	{
		const int64 clampedPos = Clamp<int64>(pImpl->getPos() + offset, 0, pImpl->size());

		return pImpl->setPos(clampedPos);
	}

	int64 BinaryReader::read(void* const dst, const int64 size)
	{
		if ((dst == nullptr) || (size <= 0))
		{
			return 0;
		}

		return pImpl->read(NonNull{ dst }, size);
	}

	int64 BinaryReader::read(void* const dst, const int64 pos, const int64 size)
	{
		if ((dst == nullptr) || (size <= 0) || (not InRange<int64>(pos, 0, pImpl->size())))
		{
			return 0;
		}

		return pImpl->read(NonNull{ dst }, pos, size);
	}

	int64 BinaryReader::lookahead(void* const dst, const int64 size) const
	{
		if ((dst == nullptr) || (size <= 0))
		{
			return 0;
		}

		return pImpl->lookahead(NonNull{ dst }, size);
	}

	int64 BinaryReader::lookahead(void* const dst, const int64 pos, const int64 size) const
	{
		if ((dst == nullptr) || (size <= 0) || (not InRange<int64>(pos, 0, pImpl->size())))
		{
			return 0;
		}

		return pImpl->lookahead(NonNull{ dst }, pos, size);
	}

	const FilePath& BinaryReader::path() const noexcept
	{
		return pImpl->path();
	}
}
