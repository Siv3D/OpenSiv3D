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
# include "FrameCounter.hpp"
# include "FrameTimer.hpp"

namespace s3d
{
	class SIV3D_NOVTABLE ISiv3DScene
	{
	public:

		static ISiv3DScene* Create();

		virtual ~ISiv3DScene() = default;

		virtual void update() = 0;

		virtual FrameCounter& getFrameCounter() noexcept = 0;

		virtual FrameTimer& getFrameTimer() noexcept = 0;
	};
}
