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

# pragma once
# include <Siv3D/Fwd.hpp>
# include <Siv3D/Duration.hpp>
# include <Siv3D/Gamepad.hpp>

namespace s3d
{
	class ISiv3DGamepad
	{
	public:

		static ISiv3DGamepad* Create();

		virtual ~ISiv3DGamepad() = default;

		virtual void init() = 0;

		virtual void update(bool deviceChanged) = 0;

		virtual bool isConnected(size_t userIndex) const = 0;

		virtual const GamepadInfo& getInfo(size_t userIndex) const = 0;

		virtual bool down(size_t userIndex, uint32 index) const = 0;

		virtual bool pressed(size_t userIndex, uint32 index) const = 0;

		virtual bool up(size_t userIndex, uint32 index) const = 0;

		virtual Duration pressedDuration(size_t userIndex, uint32 index) const = 0;

		virtual Optional<int32> povDegree(size_t userIndex) const = 0;

		virtual const detail::Gamepad_impl& getInput(size_t userIndex) const = 0;
	};
}
