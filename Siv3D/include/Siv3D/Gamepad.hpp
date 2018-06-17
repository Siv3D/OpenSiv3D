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
# include "Fwd.hpp"
# include "Array.hpp"
# include "Key.hpp"
# include "Optional.hpp"
# include "String.hpp"

namespace s3d
{
	/// <summary>
	/// ゲームパッドの情報
	/// </summary>
	struct GamepadInfo
	{
		/// <summary>
		/// 現在の接続のインデックス
		/// </summary>
		uint32 index = 0;

		uint32 vendorID = 0;

		uint32 productID = 0;

		/// <summary>
		/// 名称
		/// </summary>
		String name;
	};

	namespace detail
	{
		struct Gamepad_impl
		{
			Gamepad_impl(size_t _userIndex);

			[[nodiscard]] bool isConnected() const;

			[[nodiscard]] explicit operator bool() const;

			[[nodiscard]] const GamepadInfo& getInfo() const;

			/// <summary>
			/// ユーザインデックス
			/// </summary>
			uint32 userIndex;

			Array<double> axes;

			Array<Key> buttons;

			Key povUp;

			Key povDown;

			Key povLeft;

			Key povRight;

			[[nodiscard]] Optional<int32> povD8() const;
		};

		struct Gamepad_helper
		{
			[[nodiscard]] const Gamepad_impl& operator()(size_t userIndex) const;

			static constexpr size_t MaxUserCount = 16;
		};
	}

	constexpr auto Gamepad = detail::Gamepad_helper();

	namespace System
	{
		[[nodiscard]] Array<GamepadInfo> EnumerateGamepads();
	}
}
