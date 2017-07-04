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

# include <Siv3D/Logger.hpp>
# include "../Siv3DEngine.hpp"
# include "ILogger.hpp"

namespace s3d
{
	namespace detail
	{
		void Log_impl::writeln(const String& text) const
		{
			Siv3DEngine::GetLogger()->write(LogDescription::App, text);
		}

		const static String bytesUnits[9] =
		{
			S3DSTR("B"),
			S3DSTR("KiB"),
			S3DSTR("MiB"),
			S3DSTR("GiB"),
			S3DSTR("TiB"),
			S3DSTR("PiB"),
			S3DSTR("EiB"),
			S3DSTR("ZiB"),
			S3DSTR("YiB")
		};
	}

	namespace Logger
	{
		void SetOutputLevel(const OutputLevel level)
		{
			Siv3DEngine::GetLogger()->setOutputLevel(level);
		}

		void OutputLog(const LogDescription desc, const String& str)
		{
			Siv3DEngine::GetLogger()->write(desc, str);
		}

		void WriteRawHTML(const String& str)
		{
			Siv3DEngine::GetLogger()->writeRawHTML(str);
		}

		String FormatBytes(const int64 bytes)
		{
			double s = static_cast<double>(bytes);

			for (uint32 i = 0; i < 9; ++i)
			{
				if (s < 10.0)
				{
					return ToString(s, 2) + detail::bytesUnits[i];
				}
				else if (s < 100.0)
				{
					return ToString(s, 1) + detail::bytesUnits[i];
				}
				else if (s < 1024.0)
				{
					return ToString(s, 0) + detail::bytesUnits[i];
				}

				s /= 1024.0;
			}

			return String();
		}

		void RemoveLogOnExit()
		{
			Siv3DEngine::GetLogger()->removeLogOnExit();
		}
	}
}
