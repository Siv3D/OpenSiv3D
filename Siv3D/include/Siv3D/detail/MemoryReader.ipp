﻿//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2025 Ryo Suzuki
//	Copyright (c) 2016-2023 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# pragma once

namespace s3d
{
	SIV3D_CONCEPT_TRIVIALLY_COPYABLE_
	inline bool MemoryReader::read(TriviallyCopyable& dst)
	{
		return read(std::addressof(dst), sizeof(TriviallyCopyable)) == sizeof(TriviallyCopyable);
	}

	SIV3D_CONCEPT_TRIVIALLY_COPYABLE_
	inline bool MemoryReader::lookahead(TriviallyCopyable& dst) const
	{
		return lookahead(std::addressof(dst), sizeof(TriviallyCopyable)) == sizeof(TriviallyCopyable);
	}
}
