//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2018 Ryo Suzuki
//	Copyright (c) 2016-2018 OpenSiv3D Project
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
	constexpr uint32 KeyboardButtonCount = 256;

	class ISiv3DKeyboard
	{
	public:

		static ISiv3DKeyboard* Create();

		virtual ~ISiv3DKeyboard() = default;

		virtual bool init() = 0;

		virtual void update() = 0;

		virtual bool down(uint32 index) const = 0;

		virtual bool pressed(uint32 index) const = 0;

		virtual bool up(uint32 index) const = 0;

		virtual MillisecondsF pressedDuration(uint32 index) const = 0;
	};
}
