//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (C) 2008-2017 Ryo Suzuki
//	Copyright (C) 2016-2017 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# pragma once
# include <iostream>
# include "Fwd.hpp"
# include "String.hpp"
# include "Format.hpp"

namespace s3d
{
	namespace detail
	{
		struct ConsoleBuffer
		{
			std::unique_ptr<FormatData> formatData;

			ConsoleBuffer()
				: formatData(std::make_unique<FormatData>()) {}

			ConsoleBuffer(ConsoleBuffer&& other)
				: formatData(std::move(other.formatData)) {}

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

			void write(const String& text) const
			{
				open();

				std::cout << text;
			}

			template <class... Args>
			void write(const Args&... args) const
			{
				return write(Format(args...));
			}

			void writeln(const String& text) const
			{
				write(text + L'\n');
			}

			template <class... Args>
			void writeln(const Args&... args) const
			{
				return write(Format(args..., L'\n'));
			}

			void operator()(const String& text) const
			{
				writeln(text);
			}

			template <class... Args>
			void operator()(const Args&... args) const
			{
				return write(Format(args..., L'\n'));
			}

			template <class Type>
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
			auto operator >>(Type& value) const
			{
				value = read<Type>();

				return *this;
			}

			template <class Type>
			operator Type() const
			{
				return read<Type>();
			}
		};
	}

	constexpr auto Console = detail::Console_impl();

	namespace detail
	{
		inline ConsoleBuffer::~ConsoleBuffer()
		{
			if (formatData)
			{
				Console.writeln(formatData->string);
			}
		}
	}
}
