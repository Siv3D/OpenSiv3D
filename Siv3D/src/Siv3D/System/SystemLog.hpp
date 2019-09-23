//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2019 Ryo Suzuki
//	Copyright (c) 2016-2019 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# pragma once
# include <Siv3D/Fwd.hpp>
# include <Siv3D/EngineLog.hpp>
# include <Siv3D/DateTime.hpp>
# include <Siv3D/Version.hpp>

namespace s3d
{
	namespace SystemLog
	{
		inline void Initial()
		{
			LOG_INFO(U"ℹ️ {}"_fmt(DateTime::Now().format()));

			LOG_INFO(U"⌛ Preparing for setup...");

			if constexpr (SIV3D_BUILD_TYPE(DEBUG))
			{
				LOG_INFO(U"ℹ️ Siv3D Engine (Debug build) version " SIV3D_VERSION U" (" SIV3D_PLATFORM_NAME U")");
			}
			else
			{
				LOG_INFO(U"ℹ️ Siv3D Engine version " SIV3D_VERSION U" (" SIV3D_PLATFORM_NAME U")");
			}
		}

		inline void Final()
		{
			LOG_INFO(U"✅ Siv3D engine has terminated");

			LOG_INFO(U"ℹ️ {}"_fmt(DateTime::Now().format()));
		}
	}
}
