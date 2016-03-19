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

# pragma once
# include <cstdlib>

inline void* operator new[](size_t size, const char*, int, unsigned, const char*, int)
{
	return ::malloc(size);
}

inline void* operator new[](size_t size, size_t alignment, size_t alignmentOffset, const char*, int, unsigned, const char*, int)
{
	return ::_aligned_offset_malloc(size, alignment, alignmentOffset);
}
