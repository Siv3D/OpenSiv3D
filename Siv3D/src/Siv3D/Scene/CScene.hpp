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
# include "IScene.hpp"

namespace s3d
{
	class CScene final : public ISiv3DScene
	{
	private:

		FrameCounter m_frameCounter;

		FrameTimer m_frameTimer;

	public:

		void update() override;

		FrameCounter& getFrameCounter() noexcept override;

		FrameTimer& getFrameTimer() noexcept override;
	};
}
