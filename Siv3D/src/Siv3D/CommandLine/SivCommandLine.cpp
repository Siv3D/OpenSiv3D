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

# include <Siv3D/CommandLine.hpp>
# include <Siv3D/Unicode.hpp>

namespace s3d
{
	namespace detail::init
	{
		int g_argc = 0;

		char** g_argv = nullptr;

		Array<String> g_commandLines;

		void InitCommandLines(int argc, char** argv)
		{
			g_argc = argc;

			g_argv = argv;

			g_commandLines.resize(argc);

			for (int32 i = 0; i < argc; ++i)
			{
				g_commandLines[i] = Unicode::Widen(argv[i]);
			}
		}
	}

	namespace System
	{
		int32 GetArgc() noexcept
		{
			return detail::init::g_argc;
		}

		char** GetArgv() noexcept
		{
			return detail::init::g_argv;
		}

		const Array<String>& GetCommandLineArgs() noexcept
		{
			return detail::init::g_commandLines;
		}
	}
}
