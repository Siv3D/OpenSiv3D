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

# include "CScene.hpp"

namespace s3d
{
	void CScene::update()
	{
		++m_frameCounter;
		m_frameTimer.update();
	}

	FrameCounter& CScene::getFrameCounter() noexcept
	{
		return m_frameCounter;
	}

	FrameTimer& CScene::getFrameTimer() noexcept
	{
		return m_frameTimer;
	}
}
