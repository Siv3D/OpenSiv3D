﻿//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2025 Ryo Suzuki
//	Copyright (c) 2016-2025 OpenSiv3D Project
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
	class GL4DepthStencilState
	{
	public:

		GL4DepthStencilState();

		void set(const DepthStencilState& state);

	private:

		DepthStencilState m_currentState = DepthStencilState::Default2D;
	};
}
