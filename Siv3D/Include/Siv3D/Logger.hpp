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
		struct Log_impl
		{
			void write(const String& text) const;

			void writeln(const String& text) const
			{
				write(text + L'\n');
			}

			void operator ()(const String& text) const
			{
				writeln(text);
			}

			template <class... Args>
			void operator ()(const Args&... args) const
			{
				writeln(Format(args...));
			}

			template <class Type>
			auto operator <<(const Type& value) const
			{
				write(Format(value));

				return *this;
			}
		};
	}

	constexpr auto Log = detail::Log_impl();

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
