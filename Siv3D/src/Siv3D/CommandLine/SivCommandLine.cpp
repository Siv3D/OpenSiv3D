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

# include <Siv3D/CommandLine.hpp>

namespace s3d
{
	namespace detail::init
	{
		Array<String> g_commandLines;

		void InitCommandLines(int argc, char** argv)
		{
			g_commandLines.resize(argc);

			for (int32 i = 0; i < argc; ++i)
			{
				g_commandLines[i] = Unicode::Widen(argv[i]);
			}
		}
	}

	namespace System
	{
		const Array<String>& GetCommandLineArgs() noexcept
		{
			return detail::init::g_commandLines;
		}
	}
}
