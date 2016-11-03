//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (C) 2008-2016 Ryo Suzuki
//	Copyright (C) 2016 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# pragma once
# include <iostream>
# include "Fwd.hpp"
# include "String.hpp"

namespace s3d
{
	namespace detail
	{
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
			auto operator <<(const Type& value) const
			{
				write(Format(value));

				return *this;
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
}
