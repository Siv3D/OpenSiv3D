//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2022 Ryo Suzuki
//	Copyright (c) 2016-2022 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# pragma once
# include <memory>
# include "Common.hpp"
# include "Formatter.hpp"
# include "Parse.hpp"

namespace s3d
{
	namespace detail
	{
		struct ConsoleBuffer
		{
			std::unique_ptr<FormatData> formatData;

			ConsoleBuffer();

			ConsoleBuffer(ConsoleBuffer&& other) noexcept;

			~ConsoleBuffer();

			SIV3D_CONCEPT_FORMATTABLE
			ConsoleBuffer& operator <<(const Formattable& value)
			{
				Formatter(*formatData, value);

				return *this;
			}
		};

		struct Console_impl
		{
			void open() const;

			void write(const char32_t* s) const;

			void write(StringView s) const;

			void write(const String& s) const;

			void writeln(const char32_t* s) const;

			void writeln(StringView s) const;

			void writeln(const String& s) const;

			void operator ()(const char32_t* s) const;

			void operator ()(StringView s) const;

			void operator ()(const String& s) const;

		# if __cpp_lib_concepts
			
			template <Concept::Formattable... Args>
			void write(const Args&... args) const
			{
				return write(Format(args...));
			}

			// Format できない値が Console.write() に渡されたときに発生するエラーです
			template <class... Args>
			void write(const Args&... args) const = delete;

			template <Concept::Formattable... Args>
			void writeln(const Args&... args) const
			{
				return write(Format(args..., U'\n'));
			}

			// Format できない値が Console.writeln() に渡されたときに発生するエラーです
			template <class... Args>
			void writeln(const Args&... args) const = delete;

			template <Concept::Formattable... Args>
			void operator ()(const Args&... args) const
			{
				return write(Format(args..., U'\n'));
			}

			// Format できない値が Console() に渡されたときに発生するエラーです
			template <class... Args>
			void operator ()(const Args&... args) const = delete;

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
			void operator ()(const Args&... args) const
			{
				return write(Format(args..., U'\n'));
			}
	
		# endif

			SIV3D_CONCEPT_FORMATTABLE
			ConsoleBuffer operator <<(const Formattable& value) const
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

			void setSystemDefaultCodePage() const;

			void setUTF8CodePage() const;
		};
	}

	/// @brief コンソール入出力
	inline constexpr auto Console = detail::Console_impl{};
}
