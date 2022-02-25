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
	template <class Type, size_t Alignment>
	Type* Allocator<Type, Alignment>::allocate(const size_t n)
	{
		return AlignedMalloc<Type, Alignment>(n);
	}

	template <class Type, size_t Alignment>
	void Allocator<Type, Alignment>::deallocate(Type* const p, const size_t)
	{
		AlignedFree(p);
	}

	template <class T1, class T2>
	inline constexpr bool operator ==(const Allocator<T1>&, const Allocator<T2>&) noexcept
	{
		return true;
	}
}
