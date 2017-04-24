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

# pragma once
# include "Fwd.hpp"
# include "Format.hpp"

namespace s3d
{
	namespace detail
	{
		struct LogBuffer
		{
			std::unique_ptr<FormatData> formatData;

			LogBuffer()
				: formatData(std::make_unique<FormatData>()) {}

			LogBuffer(LogBuffer&& other)
				: formatData(std::move(other.formatData)) {}

			~LogBuffer();

			template <class Type>
			LogBuffer& operator <<(const Type& value)
			{
				Formatter(*formatData, value);

				return *this;
			}
		};

		struct Log_impl
		{
			void writeln(const String& text) const;

			const Log_impl& operator()(const String& text) const
			{
				writeln(text);

				return *this;
			}

			template <class... Args>
			const Log_impl& operator()(const Args&... args) const
			{
				writeln(Format(args...));

				return *this;
			}

			template <class Type>
			LogBuffer operator <<(const Type& value) const
			{
				LogBuffer buf;

				Formatter(*buf.formatData, value);

				return buf;
			}
		};
	}

	constexpr auto Log = detail::Log_impl();

	namespace detail
	{
		inline LogBuffer::~LogBuffer()
		{
			if (formatData)
			{
				Log.writeln(formatData->string);
			}
		}
	}

	/// <summary>
	/// ログファイルの詳細度
	/// </summary>
	enum class OutputLevel
	{
		/// <summary>
		/// 低
		/// </summary>
		Less,

		/// <summary>
		/// 通常
		/// </summary>
		Normal,

		/// <summary>
		/// 高
		/// </summary>
		More,
	};

	enum class LogDescription
	{
		Error,		// Less
		Fail,		// Less
		Warning,	// Less
		Script,		// Less
		App,		// Normal
		Info,		// Normal
		Debug,		// More
	};

	namespace Logger
	{
		void SetOutputLevel(OutputLevel level);

		void OutputLog(LogDescription desc, const String& str);

		void WriteRawHTML(const String& str);

		String FormatBytes(int64 bytes);

		void RemoveLogOnExit();
	}
}

# define FMTBYTES(size)			s3d::Logger::FormatBytes(size)
# define LOG_ERROR(MESSAGE)		s3d::Logger::OutputLog(s3d::LogDescription::Error,MESSAGE)
# define LOG_FAIL(MESSAGE)		s3d::Logger::OutputLog(s3d::LogDescription::Fail,MESSAGE)
# define LOG_WARNING(MESSAGE)	s3d::Logger::OutputLog(s3d::LogDescription::Warning,MESSAGE)
# define LOG_SCRIPT(MESSAGE)	s3d::Logger::OutputLog(s3d::LogDescription::Script,MESSAGE)
# define LOG_INFO(MESSAGE)		s3d::Logger::OutputLog(s3d::LogDescription::Info,MESSAGE)

# if defined(_DEBUG) || defined(DEBUG)

	# define LOG_DEBUG(MESSAGE)	s3d::Logger::OutputLog(s3d::LogDescription::Debug,MESSAGE)
	# define LOG_TEST(MESSAGE)	s3d::Logger::OutputLog(s3d::LogDescription::Debug,MESSAGE)

# else

	# define LOG_DEBUG(...)		((void)0)

# endif
