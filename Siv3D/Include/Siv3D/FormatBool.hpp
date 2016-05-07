//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2016 Ryo Suzuki
//	Copyright (c) 2016 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# pragma once
# include "Fwd.hpp"
# include "LetterCase.hpp"
# include "String.hpp"

namespace s3d
{
	namespace detail
	{
		inline String FormatBool(const bool value, const LetterCase letterCase)
		{
			static constexpr const wchar bools[] = L"falsetrueFALSETRUEFalseTrue";
			const size_t index = static_cast<size_t>(letterCase) * 9 + value * 5;
			return String(bools + index, 5 - value);
		}
	}

	inline String ToString(const bool value, const LetterCase letterCase = LetterCase::Lower)
	{
		return detail::FormatBool(value, letterCase);
	}
}
