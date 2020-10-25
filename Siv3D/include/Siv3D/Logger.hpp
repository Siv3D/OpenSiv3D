﻿//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2020 Ryo Suzuki
//	Copyright (c) 2016-2020 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# pragma once
# include <memory>
# include "Common.hpp"
# include "Formatter.hpp"

namespace s3d
{
	namespace detail
	{
		struct LoggerBuffer
		{
			std::unique_ptr<FormatData> formatData;

			LoggerBuffer();

			LoggerBuffer(LoggerBuffer&& other) noexcept;

			~LoggerBuffer();

			SIV3D_CONCEPT_FORMATTABLE
			LoggerBuffer& operator <<(const Formattable& value)
			{
				Formatter(*formatData, value);

				return *this;
			}
		};

		struct Logger_impl
		{
			void writeln(const char32_t* s) const;

			void writeln(StringView s) const;

			void writeln(const String& s) const;

			void operator()(const char32_t* s) const;

			void operator()(StringView s) const;

			void operator()(const String& s) const;

		# if __cpp_lib_concepts

			template <Concept::Formattable... Args>
			void writeln(const Args&... args) const
			{
				return writeln(Format(args...));
			}

			template <class... Args>
			void writeln(const Args&... args) const
			{
				// Format できない値が Logger.writeln() に渡されたときに発生するエラーです
				static_assert(0, "Logger.writeln(): Unformattable parameter value detected");
			}

			template <Concept::Formattable... Args>
			void operator()(const Args&... args) const
			{
				return writeln(Format(args...));
			}

			template <class... Args>
			void operator()(const Args&... args) const
			{
				// Format できない値が Logger() に渡されたときに発生するエラーです
				static_assert(0, "Logger(): Unformattable parameter value detected");
			}

		# else

			template <class... Args>
			void writeln(const Args&... args) const
			{
				return writeln(Format(args...));
			}

			template <class... Args>
			void operator()(const Args&... args) const
			{
				return writeln(Format(args...));
			}

		# endif

			SIV3D_CONCEPT_FORMATTABLE
			LoggerBuffer operator <<(const Formattable& value) const
			{
				LoggerBuffer buf;

				Formatter(*buf.formatData, value);

				return buf;
			}

			/// @brief ログ出力を無効化します
			void disable() const;

			/// @brief ログ出力を有効化します
			void enable() const;
		};
	}

	inline constexpr auto Logger = detail::Logger_impl();
}
