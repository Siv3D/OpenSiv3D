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
# include <Siv3D/Platform.hpp>
# if defined(SIV3D_TARGET_WINDOWS)

# define  NOMINMAX
# define  STRICT
# define  _WIN32_WINNT _WIN32_WINNT_WIN7
# define  NTDDI_VERSION NTDDI_WIN7
# include <Windows.h>
# include <Siv3D/String.hpp>
# include "IDragDrop.hpp"

namespace s3d
{
	class CDragDrop_Windows : public ISiv3DDragDrop
	{
	private:

		IDropTarget* m_pDropTarget = nullptr;

	public:

		CDragDrop_Windows();

		~CDragDrop_Windows() override;

		bool init() override;
		
		bool update() override;
	};
}

# endif
