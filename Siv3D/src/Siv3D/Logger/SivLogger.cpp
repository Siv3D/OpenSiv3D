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

# include <Siv3D/Logger.hpp>
# include "../Siv3DEngine.hpp"
# include "ILogger.hpp"

namespace s3d
{
	namespace detail
	{
		LoggerBuffer::LoggerBuffer()
			: formatData(std::make_unique<FormatData>())
		{
		
		}

		LoggerBuffer::LoggerBuffer(LoggerBuffer&& other)
			: formatData(std::move(other.formatData))
		{
		
		}

		LoggerBuffer::~LoggerBuffer()
		{
			if (formatData)
			{
				Logger.writeln(formatData->string);
			}
		}

		void Logger_impl::writeln(const String& text) const
		{
			Siv3DEngine::Get<ISiv3DLogger>()->write(LogDescription::App, text);
		}

		void Logger_impl::operator()(const String& text) const
		{
			writeln(text);
		}

		void Logger_impl::setOutputLevel(const OutputLevel level) const
		{
			Siv3DEngine::Get<ISiv3DLogger>()->setOutputLevel(level);
		}

		void Logger_impl::_outputLog(const LogDescription desc, const String& text) const
		{
			Siv3DEngine::Get<ISiv3DLogger>()->write(desc, text);
		}

		void Logger_impl::_outputLogOnce(const LogDescription desc, const uint32 id, const String& text) const
		{
			Siv3DEngine::Get<ISiv3DLogger>()->writeOnce(desc, id, text);
		}

		void Logger_impl::writeRawHTML_UTF8(const std::string_view htmlText) const
		{
			Siv3DEngine::Get<ISiv3DLogger>()->writeRawHTML_UTF8(htmlText);
		}
	}
}
