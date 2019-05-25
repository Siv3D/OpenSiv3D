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

# pragma once
# include <iostream>
# include "Fwd.hpp"
# include "String.hpp"
# include "Format.hpp"
# include "Parse.hpp"
# include "Unicode.hpp"

namespace s3d
{
	namespace detail
	{
		struct ConsoleBuffer
		{
			std::unique_ptr<FormatData> formatData;

			ConsoleBuffer();

			ConsoleBuffer(ConsoleBuffer&& other);

			~ConsoleBuffer();

			template <class Type>
			ConsoleBuffer& operator <<(const Type& value)
			{
				Formatter(*formatData, value);

				return *this;
			}
		};

		struct Console_impl
		{
			void open() const;

			void write(const char32_t* text) const;

			void write(StringView text) const;

			void write(const String& text) const;

			template <class... Args>
			void write(const Args&... args) const
			{
				return write(Format(args...));
			}

			void writeln(const String& text) const;

			template <class... Args>
			void writeln(const Args&... args) const
			{
				return write(Format(args..., U'\n'));
			}

			void operator()(const String& text) const;

			template <class... Args>
			void operator()(const Args&... args) const
			{
				return write(Format(args..., U'\n'));
			}

			template <class Type, class = decltype(Formatter(std::declval<FormatData&>(), std::declval<Type>()))>
			ConsoleBuffer operator <<(const Type& value) const
			{
				ConsoleBuffer buf;

				Formatter(*buf.formatData, value);

				return buf;
			}

			template <class Type>
			Type read() const
			{
				open();

				Type t;

				std::cin >> t;

				return t;
			}

			template <class Type>
			Type readLine() const
			{
				open();

				std::string s;

				std::getline(std::cin, s);

				return Parse<Type>(Unicode::Widen(s));
			}

			template <class Type>
			auto operator >>(Type& value) const
			{
				value = read<Type>();

				return *this;
			}
		};
	}

	inline constexpr auto Console = detail::Console_impl();
}
