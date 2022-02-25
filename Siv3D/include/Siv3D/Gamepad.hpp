//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2022 Ryo Suzuki
//	Copyright (c) 2016-2022 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# pragma once
# include "Common.hpp"
# include "Array.hpp"
# include "Optional.hpp"
# include "InputGroups.hpp"
# include "GamepadInfo.hpp"

namespace s3d
{
	namespace detail
	{
		struct Gamepad_impl
		{
			SIV3D_NODISCARD_CXX20
			Gamepad_impl(size_t playerIndex);

			[[nodiscard]]
			bool isConnected() const;

			[[nodiscard]]
			explicit operator bool() const;

			[[nodiscard]]
			const GamepadInfo& getInfo() const;

			/// @brief プレイヤーインデックス
			uint32 playerIndex;

			Array<double> axes;

			Array<Input> buttons;

			Input povUp;

			Input povDown;

			Input povLeft;

			Input povRight;

			[[nodiscard]]
			Optional<int32> povD8() const;
		};

		struct Gamepad_helper
		{
			static constexpr size_t MaxPlayerCount = 16;

			[[nodiscard]]
			const Gamepad_impl& operator ()(size_t userIndex) const;
		};
	}

	inline constexpr auto Gamepad = detail::Gamepad_helper{};
}
