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
	SIV3D_CONCEPT_TRIVIALLY_COPYABLE_
	inline bool Serial::read(TriviallyCopyable& to)
	{
		if (available() < sizeof(TriviallyCopyable))
		{
			return false;
		}

		return read(std::addressof(to), sizeof(TriviallyCopyable)) == sizeof(TriviallyCopyable);
	}

	SIV3D_CONCEPT_TRIVIALLY_COPYABLE_
	inline bool Serial::write(const TriviallyCopyable& from)
	{
		return (write(std::addressof(from), sizeof(TriviallyCopyable))) == sizeof(TriviallyCopyable);
	}
}
