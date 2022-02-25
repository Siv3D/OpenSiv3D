//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2022 Ryo Suzuki
//	Copyright (c) 2016-2022 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# pragma once

namespace s3d
{
	inline BinaryWriter::BinaryWriter(const FilePathView path, const OpenMode openMode)
		: BinaryWriter{}
	{
		open(path, openMode);
	}

	inline BinaryWriter::operator bool() const noexcept
	{
		return isOpen();
	}

	SIV3D_CONCEPT_TRIVIALLY_COPYABLE_
	inline bool BinaryWriter::write(const TriviallyCopyable& src)
	{
		return (write(std::addressof(src), sizeof(TriviallyCopyable)) == sizeof(TriviallyCopyable));
	}
}
