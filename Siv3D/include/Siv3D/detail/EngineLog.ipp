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
	namespace Internal
	{
		void OutputEngineLog(LogType type, StringView s);

		class ScopedEngineLog
		{
		private:

			LogType m_type;

			String m_s;

		public:

			ScopedEngineLog(LogType type, String s);

			~ScopedEngineLog();
		};
	}
}
