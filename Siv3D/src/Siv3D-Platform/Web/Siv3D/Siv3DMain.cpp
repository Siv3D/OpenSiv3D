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

# include <iostream>
# include <Siv3D/Error.hpp>
# include <Siv3D/Unicode.hpp>
# include <Siv3D/Format.hpp>
# include <Siv3D/EngineLog.hpp>
# include <Siv3D/FreestandingMessageBox/FreestandingMessageBox.hpp>
# include <Siv3D/EngineOptions.hpp>
# include <Siv3D/Windows/Windows.hpp>
# include <Siv3D/Common/Siv3DEngine.hpp>
# include <Siv3D/System/CSystem.hpp>
# include <Siv3D/Window/CWindow.hpp>
# include <Siv3D/Script/IScript.hpp>

void Main();

namespace s3d
{
	static void TryMain()
	{
		String errorMessage;

		try
		{
			LOG_TRACE(U"Main() ---");

			Main();

			LOG_TRACE(U"--- Main()");
		}
		catch (const Error& error)
		{
			errorMessage = Format(error);
		}
		catch (const fmt::format_error& error)
		{
			errorMessage = U"Error occured in _fmt : {}"_fmt(Unicode::Widen(error.what()));
		}
		catch (const std::runtime_error& error)
		{
			errorMessage = U"[std::runtime_error] {}"_fmt(Unicode::Widen(error.what()));
		}
		catch (const std::out_of_range& error)
		{
			errorMessage = U"[std::out_of_range] {}"_fmt(Unicode::Widen(error.what()));
		}
		catch (const std::exception& error)
		{
			errorMessage = U"[std::exception] {}"_fmt(Unicode::Widen(error.what()));
		}

		if (errorMessage)
		{
			errorMessage += U"\n\nFor more information, [Debug] -> [Windows] -> [Exception Settings] -> Tick the C++ Exceptions checkbox under the [Break When Thrown] heading.";

			FreestandingMessageBox::ShowError(errorMessage);
		}

		SIV3D_ENGINE(Script)->shutdown();
	}

	namespace detail::init
	{
		void InitCommandLines(int argc, char** argv);

		void InitModulePath(const char* arg);
	}
}



int main(int argc, char* argv[])
{
	using namespace s3d;

	std::cout << "OpenSiv3D for Web\n";

	detail::init::InitCommandLines(argc, argv);
	detail::init::InitModulePath("/a.out");

	Siv3DEngine engine;

	try
	{
		SIV3D_ENGINE(System)->init();
	}
	catch (const Error& error)
	{
		FreestandingMessageBox::ShowError(Format(error));
		return -1;
	}

	TryMain();

	return 0;
}
