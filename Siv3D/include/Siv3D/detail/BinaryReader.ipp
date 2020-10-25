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

# pragma once

namespace s3d
{
	inline BinaryReader::BinaryReader(const FilePathView path, const OpenMode openMode)
		: BinaryReader()
	{
		open(path, openMode);
	}

	inline bool BinaryReader::supportsLookahead() const noexcept
	{
		return true;
	}

	inline BinaryReader::operator bool() const noexcept
	{
		return isOpen();
	}

	SIV3D_CONCEPT_TRIVIALLY_COPYABLE_
	inline bool BinaryReader::read(TriviallyCopyable& dst)
	{
		return (read(std::addressof(dst), sizeof(TriviallyCopyable)) == sizeof(TriviallyCopyable));
	}

	SIV3D_CONCEPT_TRIVIALLY_COPYABLE_
	bool BinaryReader::lookahead(TriviallyCopyable& dst)
	{
		return (lookahead(std::addressof(dst), sizeof(TriviallyCopyable)) == sizeof(TriviallyCopyable));
	}
}
