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

# include <Siv3D/EngineLog.hpp>
# include <Siv3D/String.hpp>
# include <Siv3D/Logger/ILogger.hpp>
# include <Siv3D/Common/Siv3DEngine.hpp>

namespace s3d
{
	namespace Internal
	{
		void OutputEngineLog(const LogType type, const StringView s)
		{
			if (Siv3DEngine::isActive())
			{
				SIV3D_ENGINE(Logger)->write(type, s);
			}
		}

		ScopedEngineLog::ScopedEngineLog(const LogType type, String s)
			: m_type{ type }
			, m_s{ std::move(s) }
		{
			if (Siv3DEngine::isActive())
			{
				SIV3D_ENGINE(Logger)->write(m_type, m_s + U" ---"_s);
			}
		}

		ScopedEngineLog::~ScopedEngineLog()
		{
			if (Siv3DEngine::isActive())
			{
				SIV3D_ENGINE(Logger)->write(m_type, U"--- "_s + m_s);
			}
		}
	}
}
