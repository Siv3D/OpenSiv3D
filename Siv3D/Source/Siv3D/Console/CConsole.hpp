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
# include "IConsole.hpp"

# if defined (SIV3D_TARGET_WINDOWS)
#	include <cstdio>
#	include <iostream>
#	define  NOMINMAX
#	define  STRICT
#	define  WIN32_LEAN_AND_MEAN
#	define  _WIN32_WINNT _WIN32_WINNT_WIN7
#	define  NTDDI_VERSION NTDDI_WIN7
#	include <Windows.h>
# endif

namespace s3d
{
	class CConsole : public ISiv3DConsole
	{
	private:

# if defined (SIV3D_TARGET_WINDOWS)
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
