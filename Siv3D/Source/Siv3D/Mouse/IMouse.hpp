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
# include <utility>
# include <Siv3D/Fwd.hpp>
# include "../Key/InputState.hpp"

namespace s3d
{
	constexpr uint32 MouseButtonCount = 8;

	class ISiv3DMouse
	{
	public:

		static ISiv3DMouse* Create();

		virtual ~ISiv3DMouse() = default;

		virtual bool init() = 0;

		virtual void update() = 0;

		virtual bool down(uint32 index) const = 0;

		virtual bool pressed(uint32 index) const = 0;

		virtual bool up(uint32 index) const = 0;

		virtual MillisecondsF pressedDuration(uint32 index) const = 0;

		virtual const Vec2& wheel() const = 0;
		
		virtual void onScroll(double v, double h) = 0;
	};
}
