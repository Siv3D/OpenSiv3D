//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2021 Ryo Suzuki
//	Copyright (c) 2016-2021 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# pragma once
# include <memory>
# include "Common.hpp"
# include "Font.hpp"
# include "Formatter.hpp"

namespace s3d
{
	namespace detail
	{
		struct PrintBuffer
		{
			std::unique_ptr<FormatData> formatData;

			PrintBuffer();

			PrintBuffer(PrintBuffer&& other) noexcept;

			~PrintBuffer();

			SIV3D_CONCEPT_FORMATTABLE
			PrintBuffer& operator <<(const Formattable& value)
			{
				Formatter(*formatData, value);

				return *this;
			}
		};

		struct Print_impl
		{
			void write(const char32_t* s) const;

			void write(StringView s) const;

			void write(const String& s) const;

			void writeln(const char32_t* s) const;

			void writeln(StringView s) const;

			void writeln(const String& s) const;

			void operator()(const char32_t* s) const;

			void operator()(StringView s) const;

			void operator()(const String& s) const;

		# if __cpp_lib_concepts

			template <Concept::Formattable... Args>
			void write(const Args&... args) const
			{
				return write(Format(args...));
			}

			template <class... Args>
			void write(const Args&... args) const
			{
				// Format できない値が Print.write() に渡されたときに発生するエラーです
				static_assert(0, "Print.write(): Unformattable parameter value detected");
			}

			template <Concept::Formattable... Args>
			void writeln(const Args&... args) const
			{
				return write(Format(args..., U'\n'));
			}

			template <class... Args>
			void writeln(const Args&... args) const
			{
				// Format できない値が Print.writeln() に渡されたときに発生するエラーです
				static_assert(0, "Print.writeln(): Unformattable parameter value detected");
			}

			template <Concept::Formattable... Args>
			void operator()(const Args&... args) const
			{
				return write(Format(args..., U'\n'));
			}

			template <class... Args>
			void operator()(const Args&... args) const
			{
				// Format できない値が Print() に渡されたときに発生するエラーです
				static_assert(0, "Print(): Unformattable parameter value detected");
			}

		# else

			template <class... Args>
			void write(const Args&... args) const
			{
				return write(Format(args...));
			}

			template <class... Args>
			void writeln(const Args&... args) const
			{
				return write(Format(args..., U'\n'));
			}

			template <class... Args>
			void operator()(const Args&... args) const
			{
				return write(Format(args..., U'\n'));
			}

		# endif

			SIV3D_CONCEPT_FORMATTABLE
			PrintBuffer operator <<(const Formattable& value) const
			{
				PrintBuffer buf;

				Formatter(*buf.formatData, value);

				return buf;
			}
		};
	}

	inline constexpr auto Print = detail::Print_impl{};

	void ClearPrint();
}
