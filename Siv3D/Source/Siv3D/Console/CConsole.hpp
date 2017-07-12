//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2017 Ryo Suzuki
//	Copyright (c) 2016-2017 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# pragma once
# include "IConsole.hpp"

# if defined(SIV3D_TARGET_WINDOWS)

	# include <cstdio>
	# include <iostream>
	# ifndef NOMINMAX
	#	define  NOMINMAX
	# endif
	# ifndef STRICT
	#	define  STRICT
	# endif
	# ifndef WIN32_LEAN_AND_MEAN
	#	define  WIN32_LEAN_AND_MEAN
	# endif
	# ifndef _WIN32_WINNT
	#	define  _WIN32_WINNT _WIN32_WINNT_WIN7
	# endif
	# ifndef NTDDI_VERSION
	#	define  NTDDI_VERSION NTDDI_WIN7
	# endif
	# include <Windows.h>

# endif

namespace s3d
{
	class CConsole : public ISiv3DConsole
	{
	private:

# if defined(SIV3D_TARGET_WINDOWS)

		FILE* m_out = nullptr;

		FILE* m_in = nullptr;

# endif

	public:

		CConsole();

		~CConsole() override;

		void open() override;

		void close() override;
	};
}
