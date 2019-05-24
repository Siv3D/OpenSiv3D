//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2019 Ryo Suzuki
//	Copyright (c) 2016-2019 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# include <Siv3D/BlendState.hpp>

namespace s3d
{
	class GLBlendState
	{
	private:

		BlendState m_currentState = BlendState::Default;

	public:
		
		GLBlendState();

		void set(const BlendState& state);
	};
}
