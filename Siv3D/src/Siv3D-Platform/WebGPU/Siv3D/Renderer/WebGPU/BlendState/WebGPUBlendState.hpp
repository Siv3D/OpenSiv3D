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

# pragma once
# include <Siv3D/Common.hpp>
# include <Siv3D/Common/OpenGL.hpp>
# include <Siv3D/BlendState.hpp>
# include <Siv3D/HashTable.hpp>

namespace s3d
{
	class WebGPUBlendState
	{
	private:

		BlendState m_currentState = BlendState::Default;

	public:

		WebGPUBlendState();

		void set(const BlendState& state);
	};
}
