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
# include <memory>
# include "Fwd.hpp"
# include "Format.hpp"

namespace s3d
{
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

	namespace detail
	{
		struct LoggerBuffer
		{
			std::unique_ptr<FormatData> formatData;

			LoggerBuffer()
				: formatData(std::make_unique<FormatData>()) {}

			LoggerBuffer(LoggerBuffer&& other)
				: formatData(std::move(other.formatData)) {}

			~LoggerBuffer();

			template <class Type>
			LoggerBuffer& operator <<(const Type& value)
			{
				Formatter(*formatData, value);

				return *this;
			}
		};

		struct Logger_impl
		{
			void writeln(const String& text) const;

			void operator()(const String& text) const
			{
				writeln(text);
			}

			template <class... Args>
			void operator()(const Args&... args) const
			{
				writeln(Format(args...));
			}

			template <class Type>
			LoggerBuffer operator <<(const Type& value) const
			{
				LoggerBuffer buf;

				Formatter(*buf.formatData, value);

				return buf;
			}

			void setOutputLevel(OutputLevel level) const;

			void outputLog(LogDescription desc, const String& text) const;

			void writeRawHTML(const String& htmlText) const;

			void writeRawHTML_UTF8(std::string_view htmlText) const;

			void removeOnExit() const;
		};
	}

	constexpr auto Logger = detail::Logger_impl();

	namespace detail
	{
		inline LoggerBuffer::~LoggerBuffer()
		{
			if (formatData)
			{
				Logger.writeln(formatData->string);
			}
		}
	}
}
