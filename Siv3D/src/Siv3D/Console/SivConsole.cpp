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

# include <Siv3D/Console.hpp>
# include <Siv3DEngine.hpp>
# include <Console/IConsole.hpp>

namespace s3d
{
	namespace detail
	{
		ConsoleBuffer::ConsoleBuffer()
			: formatData(std::make_unique<FormatData>())
		{
		
		}

		ConsoleBuffer::ConsoleBuffer(ConsoleBuffer&& other)
			: formatData(std::move(other.formatData))
		{
		
		}

		ConsoleBuffer::~ConsoleBuffer()
		{
			if (formatData)
			{
				Console.writeln(formatData->string);
			}
		}

		void Console_impl::open() const
		{
			Siv3DEngine::Get<ISiv3DConsole>()->open();
		}

		void Console_impl::write(const char32_t* text) const
		{
			open();

			std::cout << Unicode::Narrow(text);
		}

		void Console_impl::write(StringView text) const
		{
			open();

			std::cout << text;
		}

		void Console_impl::write(const String& text) const
		{
			open();

			std::cout << text;
		}

		void Console_impl::writeln(const String& text) const
		{
			write(text + U'\n');
		}

		void Console_impl::operator()(const String& text) const
		{
			writeln(text);
		}
	}
}
