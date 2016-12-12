//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2016 Ryo Suzuki
//	Copyright (c) 2016 OpenSiv3D Project
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
}
