﻿//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2020 Ryo Suzuki
//	Copyright (c) 2016-2020 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# include <cstdlib>
# include <Siv3D/EnvironmentVariable.hpp>

namespace s3d
{
	namespace EnvironmentVariable
	{
		String Get(const StringView name)
		{
			const char* value = std::getenv(name.narrow().c_str());

			if (not value)
			{
				return{};
			}

			return Unicode::Widen(value);
		}
	}
}
