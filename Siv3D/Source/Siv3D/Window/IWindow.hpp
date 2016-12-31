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
# include <Siv3D/Fwd.hpp>

# if defined(SIV3D_TARGET_WINDOWS)

	# define  NOMINMAX
	# define  STRICT
	# define  WIN32_LEAN_AND_MEAN
	# define  _WIN32_WINNT _WIN32_WINNT_WIN7
	# define  NTDDI_VERSION NTDDI_WIN7
	# include <Windows.h>

# endif

namespace s3d
{
	# if defined(SIV3D_TARGET_WINDOWS)

		using WindowHandle = HWND;

	# else

		using WindowHandle = void*;

	# endif

	class ISiv3DWindow
	{
	public:

		static ISiv3DWindow* Create();

		virtual ~ISiv3DWindow() = default;

		virtual bool init() = 0;
		
		virtual bool update() = 0;

		virtual void destroy() = 0;

		virtual WindowHandle getHandle() const = 0;
	};
}
