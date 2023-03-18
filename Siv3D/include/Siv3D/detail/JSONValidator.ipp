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
	template <class Reader, std::enable_if_t<std::is_base_of_v<IReader, Reader>>*>
	inline JSONValidator JSONValidator::Load(Reader&& reader, AllowExceptions allowExceptions)
	{
		return Load(std::make_unique<Reader>(std::move(reader)), allowExceptions);
	}

	inline namespace Literals
	{
		inline namespace JSONLiterals
		{
			inline JSONValidator operator ""_jsonValidator(const char32_t* str, const size_t length)
			{
				return JSONValidator::Set(JSON::Parse(StringView{str, length}));
			}
		}
	}
}