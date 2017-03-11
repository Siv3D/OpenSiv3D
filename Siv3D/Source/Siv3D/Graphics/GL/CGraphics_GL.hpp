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
# include <Siv3D/Platform.hpp>
# if defined(SIV3D_TARGET_MACOS) || defined(SIV3D_TARGET_LINUX)

# include "../IGraphics.hpp"

namespace s3d
{
	class CGraphics_GL : public ISiv3DGraphics
	{
	private:

	public:

		CGraphics_GL();

		~CGraphics_GL() override;

		bool init() override;
	};
}

# endif
