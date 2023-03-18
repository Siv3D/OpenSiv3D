//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2023 Ryo Suzuki
//	Copyright (c) 2016-2023 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# include <Siv3D/Console.hpp>
# include <Siv3D/Unicode.hpp>
# include <Siv3D/Console/IConsole.hpp>
# include <Siv3D/Common/Siv3DEngine.hpp>

namespace s3d
{
	namespace detail
	{
		ConsoleBuffer::ConsoleBuffer()
			: formatData{ std::make_unique<FormatData>() } {}

		ConsoleBuffer::ConsoleBuffer(ConsoleBuffer&& other) noexcept
			: formatData{ std::move(other.formatData) } {}

		ConsoleBuffer::~ConsoleBuffer()
		{
			if (formatData)
			{
				Console.writeln(formatData->string);
			}
		}


		void Console_impl::open() const
		{
			SIV3D_ENGINE(Console)->open();
		}

		void Console_impl::write(const char32_t* s) const
		{
			open();

			std::cout << Unicode::Narrow(s);
		}

		void Console_impl::write(const StringView s) const
		{
			open();

			std::cout << s;
		}

		void Console_impl::write(const String& s) const
		{
			open();

			std::cout << s;
		}

		void Console_impl::writeln(const char32_t* s) const
		{
			write(s);

			std::cout << std::endl;
		}

		void Console_impl::writeln(const StringView s) const
		{
			write(s);

			std::cout << std::endl;
		}

		void Console_impl::writeln(const String& s) const
		{
			write(s);

			std::cout << std::endl;
		}

		void Console_impl::operator()(const char32_t* s) const
		{
			writeln(s);
		}

		void Console_impl::operator()(const StringView s) const
		{
			writeln(s);
		}

		void Console_impl::operator()(const String& s) const
		{
			writeln(s);
		}

		void Console_impl::setSystemDefaultCodePage() const
		{
			SIV3D_ENGINE(Console)->setSystemDefaultCodePage();
		}

		void Console_impl::setUTF8CodePage() const
		{
			SIV3D_ENGINE(Console)->setUTF8CodePage();
		}
	}
}
