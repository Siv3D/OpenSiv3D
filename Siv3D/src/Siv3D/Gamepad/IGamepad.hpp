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
# include <Siv3D/Gamepad.hpp>

namespace s3d
{
	class SIV3D_NOVTABLE ISiv3DGamepad
	{
	public:

		static ISiv3DGamepad* Create();

		virtual ~ISiv3DGamepad() = default;

		virtual void init() = 0;

		virtual void update() = 0;

		virtual Array<GamepadInfo> enumerate() = 0;

		virtual bool isConnected(size_t playerIndex) = 0;

		virtual const GamepadInfo& getInfo(size_t playerIndex) = 0;

		virtual bool down(size_t playerIndex, uint32 index) = 0;

		virtual bool pressed(size_t playerIndex, uint32 index) = 0;

		virtual bool up(size_t playerIndex, uint32 index) = 0;

		virtual void clearInput(size_t playerIndex, uint32 index) = 0;

		virtual bool cleared(size_t playerIndex, uint32 index) = 0;

		virtual Duration pressedDuration(size_t playerIndex, uint32 index) = 0;

		virtual Optional<int32> povDegree(size_t playerIndex) = 0;

		virtual const detail::Gamepad_impl& getInput(size_t playerIndex) = 0;
	};
}
