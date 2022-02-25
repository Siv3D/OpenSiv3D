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
	inline RegExp::operator bool() const noexcept
	{
		return isValid();
	}

	inline namespace Literals
	{
		inline namespace RegExpLiterals
		{
			[[nodiscard]]
			inline RegExp operator ""_re(const char32_t* s, size_t length) noexcept
			{
				return RegExp(StringView(s, length));
			}
		}
	}
}
