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

		MillisecondsF pressedDuration() const;

		String name() const;
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

	/// <summary>
	/// 0 キー
	/// </summary>
	constexpr Key Key0{ InputDevice::Keyboard, 0x30 };

	/// <summary>
	/// 1 キー
	/// </summary>
	constexpr Key Key1{ InputDevice::Keyboard, 0x31 };

	/// <summary>
	/// 2 キー
	/// </summary>
	constexpr Key Key2{ InputDevice::Keyboard, 0x32 };

	/// <summary>
	/// 3 キー
	/// </summary>
	constexpr Key Key3{ InputDevice::Keyboard, 0x33 };

	/// <summary>
	/// 4 キー
	/// </summary>
	constexpr Key Key4{ InputDevice::Keyboard, 0x34 };

	/// <summary>
	/// 5 キー
	/// </summary>
	constexpr Key Key5{ InputDevice::Keyboard, 0x35 };

	/// <summary>
	/// 6 キー
	/// </summary>
	constexpr Key Key6{ InputDevice::Keyboard, 0x36 };

	/// <summary>
	/// 7 キー
	/// </summary>
	constexpr Key Key7{ InputDevice::Keyboard, 0x37 };

	/// <summary>
	/// 8 キー
	/// </summary>
	constexpr Key Key8{ InputDevice::Keyboard, 0x38 };

	/// <summary>
	/// 9 キー
	/// </summary>
	constexpr Key Key9{ InputDevice::Keyboard, 0x39 };

	/// <summary>
	/// A キー
	/// </summary>
	constexpr Key KeyA{ InputDevice::Keyboard, 0x41 };

	/// <summary>
	/// B キー
	/// </summary>
	constexpr Key KeyB{ InputDevice::Keyboard, 0x42 };

	/// <summary>
	/// C キー
	/// </summary>
	constexpr Key KeyC{ InputDevice::Keyboard, 0x43 };

	/// <summary>
	/// D キー
	/// </summary>
	constexpr Key KeyD{ InputDevice::Keyboard, 0x44 };

	/// <summary>
	/// E キー
	/// </summary>
	constexpr Key KeyE{ InputDevice::Keyboard, 0x45 };

	/// <summary>
	/// F キー
	/// </summary>
	constexpr Key KeyF{ InputDevice::Keyboard, 0x46 };

	/// <summary>
	/// G キー
	/// </summary>
	constexpr Key KeyG{ InputDevice::Keyboard, 0x47 };

	/// <summary>
	/// H キー
	/// </summary>
	constexpr Key KeyH{ InputDevice::Keyboard, 0x48 };

	/// <summary>
	/// I キー
	/// </summary>
	constexpr Key KeyI{ InputDevice::Keyboard, 0x49 };

	/// <summary>
	/// J キー
	/// </summary>
	constexpr Key KeyJ{ InputDevice::Keyboard, 0x4A };

	/// <summary>
	/// K キー
	/// </summary>
	constexpr Key KeyK{ InputDevice::Keyboard, 0x4B };

	/// <summary>
	/// L キー
	/// </summary>
	constexpr Key KeyL{ InputDevice::Keyboard, 0x4C };

	/// <summary>
	/// M キー
	/// </summary>
	constexpr Key KeyM{ InputDevice::Keyboard, 0x4D };

	/// <summary>
	/// N キー
	/// </summary>
	constexpr Key KeyN{ InputDevice::Keyboard, 0x4E };

	/// <summary>
	/// O キー
	/// </summary>
	constexpr Key KeyO{ InputDevice::Keyboard, 0x4F };

	/// <summary>
	/// P キー
	/// </summary>
	constexpr Key KeyP{ InputDevice::Keyboard, 0x50 };

	/// <summary>
	/// Q キー
	/// </summary>
	constexpr Key KeyQ{ InputDevice::Keyboard, 0x51 };

	/// <summary>
	/// R キー
	/// </summary>
	constexpr Key KeyR{ InputDevice::Keyboard, 0x52 };

	/// <summary>
	/// S キー
	/// </summary>
	constexpr Key KeyS{ InputDevice::Keyboard, 0x53 };

	/// <summary>
	/// T キー
	/// </summary>
	constexpr Key KeyT{ InputDevice::Keyboard, 0x54 };

	/// <summary>
	/// U キー
	/// </summary>
	constexpr Key KeyU{ InputDevice::Keyboard, 0x55 };

	/// <summary>
	/// V キー
	/// </summary>
	constexpr Key KeyV{ InputDevice::Keyboard, 0x56 };

	/// <summary>
	/// W キー
	/// </summary>
	constexpr Key KeyW{ InputDevice::Keyboard, 0x57 };

	/// <summary>
	/// X キー
	/// </summary>
	constexpr Key KeyX{ InputDevice::Keyboard, 0x58 };

	/// <summary>
	/// Y キー
	/// </summary>
	constexpr Key KeyY{ InputDevice::Keyboard, 0x59 };

	/// <summary>
	/// Z キー
	/// </summary>
	constexpr Key KeyZ{ InputDevice::Keyboard, 0x5A };
}
