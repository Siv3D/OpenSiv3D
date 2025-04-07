//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2025 Ryo Suzuki
//	Copyright (c) 2016-2025 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# include "OpenAICommon.hpp"

namespace s3d
{
	namespace detail
	{
		HashTable<String, String> MakeHeaders(const StringView apiKey)
		{
			return{
				{ U"Content-Type", U"application/json" },
				{ U"Authorization", (U"Bearer " + apiKey) },
			};
		}
	}
}
