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
	# include <Siv3D/Windows.hpp>

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
