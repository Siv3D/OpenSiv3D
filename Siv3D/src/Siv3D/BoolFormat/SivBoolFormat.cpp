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

# include <Siv3D/BoolFormat.hpp>
# include <Siv3D/String.hpp>

namespace s3d
{
	String ToString(const bool value, const LetterCase letterCase)
	{
		static constexpr const char32 bools[] = U"falsetrueFALSETRUEFalseTrue";
		
		const size_t index = static_cast<size_t>(letterCase) * 9 + value * 5;
		
		return String(bools + index, 5 - value);
	}
}
