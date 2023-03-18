//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2023 Ryo Suzuki
//	Copyright (c) 2016-2023 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# pragma once

namespace s3d
{
	template <class Type>
	inline void swap(HashSet<Type>& a, HashSet<Type>& b) noexcept
	{
		a.swap(b);
	}

	template <class Type>
	inline void Formatter(FormatData& formatData, const HashSet<Type>& set)
	{
		Formatter(formatData, set.begin(), set.end());
	}
}
