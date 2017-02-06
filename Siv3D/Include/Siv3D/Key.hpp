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
# include "Fwd.hpp"
# include "Duration.hpp"

namespace s3d
{
	enum class InputDevice : uint8
	{
		Keyboard,

		Mouse,

		Gamepad,

		XInput,
	};

	class Key
	{
	private:

		InputDevice m_device = InputDevice::Keyboard;

		uint8 m_code = 0;

		uint8 m_userIndex = 0;

		uint8 m_reserved = 0;

	public:

		constexpr Key(InputDevice device, uint8 code, uint8 userIndex = 0) noexcept
			: m_device(device)
			, m_code(code)
			, m_userIndex(userIndex) {}

		bool down() const;

		bool pressed() const;

		bool up() const;

		MillisecondsF pressedDuration() const;

		constexpr InputDevice device() const noexcept
		{
			return m_device;
		}

		constexpr uint8 code() const noexcept
		{
			return m_code;
		}

		constexpr uint8 userIndex() const noexcept
		{
			return m_userIndex;
		}
	};

	/// <summary>
	/// 2 つのキーが同じキーを示しているかを返します。
	/// </summary>
	/// <param name="key1">
	/// 比較するキー
	/// </param>
	/// <param name="key2">
	/// 比較するキー
	/// </param>
	/// <returns>
	/// 2 つのキーが同じキーを示している場合 true, それ以外の場合は false
	/// </returns>
	constexpr inline bool operator ==(const Key& key1, const Key& key2) noexcept
	{
		return key1.device() == key2.device()
			&& key1.code() == key2.code()
			&& key1.userIndex() == key2.userIndex();
	}

	/// <summary>
	/// 2 つのキーが異なるキーを示しているかを返します。
	/// </summary>
	/// <param name="key1">
	/// 比較するキー
	/// </param>
	/// <param name="key2">
	/// 比較するキー
	/// </param>
	/// <returns>
	/// 2 つのキーが異なるキーを示している場合 true, それ以外の場合は false
	/// </returns>
	constexpr inline bool operator !=(const Key& key1, const Key& key2) noexcept
	{
		return !(key1 == key2);
	}
}
