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

# include <Siv3D/Logger.hpp>
# include <Siv3D/LogType.hpp>
# include <Siv3D/Logger/ILogger.hpp>
# include <Siv3D/Common/Siv3DEngine.hpp>

namespace s3d
{
	namespace detail
	{
		LoggerBuffer::LoggerBuffer()
			: formatData{ std::make_unique<FormatData>() }
		{

		}

		LoggerBuffer::LoggerBuffer(LoggerBuffer&& other) noexcept
			: formatData{ std::move(other.formatData) }
		{

		}

		LoggerBuffer::~LoggerBuffer()
		{
			if (formatData)
			{
				Logger.writeln(formatData->string);
			}
		}


		void Logger_impl::writeln(const char32_t* s) const
		{
			writeln(StringView{ s });
		}

		void Logger_impl::writeln(const StringView s) const
		{
			if (Siv3DEngine::isActive())
			{
				SIV3D_ENGINE(Logger)->write(LogType::App, s);
			}
		}

		void Logger_impl::writeln(const String& s) const
		{
			writeln(StringView{ s });
		}

		void Logger_impl::operator()(const char32_t* s) const
		{
			writeln(s);
		}

		void Logger_impl::operator()(const StringView s) const
		{
			writeln(s);
		}

		void Logger_impl::operator()(const String& s) const
		{
			writeln(s);
		}

		void Logger_impl::disable() const
		{
			SIV3D_ENGINE(Logger)->setEnabled(false);
		}

		void Logger_impl::enable() const
		{
			SIV3D_ENGINE(Logger)->setEnabled(true);
		}
	}
}
