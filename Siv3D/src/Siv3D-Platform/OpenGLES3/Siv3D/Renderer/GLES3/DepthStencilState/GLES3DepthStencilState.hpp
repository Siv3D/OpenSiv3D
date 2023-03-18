//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2023 Ryo Suzuki
//	Copyright (c) 2016-2023 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# pragma once
# include <Siv3D/Common.hpp>
# include <Siv3D/Common/OpenGL.hpp>
# include <Siv3D/DepthStencilState.hpp>
# include <Siv3D/HashTable.hpp>

namespace s3d
{
	class GLES3DepthStencilState
	{
	public:

		GLES3DepthStencilState();

		void set(const DepthStencilState& state);

	private:

		DepthStencilState m_currentState = DepthStencilState::Default2D;
	};
}
