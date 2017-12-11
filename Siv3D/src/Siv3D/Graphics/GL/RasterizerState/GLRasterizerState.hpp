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

# include <Siv3D/Platform.hpp>
# if defined(SIV3D_TARGET_MACOS) || defined(SIV3D_TARGET_LINUX)

# include <Siv3D/RasterizerState.hpp>

namespace s3d
{
	class GLRasterizerState
	{
	private:

		RasterizerState m_currentState = RasterizerState::Default2D;

	public:
		
		GLRasterizerState();

		void set(const RasterizerState& state);
	};
}

# endif
