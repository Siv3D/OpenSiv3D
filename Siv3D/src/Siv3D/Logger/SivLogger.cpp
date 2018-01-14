//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2018 Ryo Suzuki
//	Copyright (c) 2016-2018 OpenSiv3D Project
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
		void Logger_impl::writeln(const String& text) const
		{
			Siv3DEngine::GetLogger()->write(LogDescription::App, text);
		}

		void Logger_impl::setOutputLevel(const OutputLevel level) const
		{
			Siv3DEngine::GetLogger()->setOutputLevel(level);
		}

		void Logger_impl::_outputLog(const LogDescription desc, const String& text) const
		{
			Siv3DEngine::GetLogger()->write(desc, text);
		}

		void Logger_impl::_outputLogOnce(const LogDescription desc, const uint32 id, const String& text) const
		{
			Siv3DEngine::GetLogger()->writeOnce(desc, id, text);
		}

		void Logger_impl::writeRawHTML(const String& htmlText) const
		{
			Siv3DEngine::GetLogger()->writeRawHTML(htmlText);
		}

		void Logger_impl::writeRawHTML_UTF8(const std::string_view htmlText) const
		{
			Siv3DEngine::GetLogger()->writeRawHTML_UTF8(htmlText);
		}

		void Logger_impl::removeOnExit() const
		{
			Siv3DEngine::GetLogger()->removeOnExit();
		}
	}
}
