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

# include <sstream>
# include <Siv3D/InputGroups.hpp>
# include <Siv3D/Keyboard/IKeyboard.hpp>
# include <Siv3D/Mouse/IMouse.hpp>
# include <Siv3D/XInput/IXInput.hpp>
# include <Siv3D/Gamepad/IGamepad.hpp>
# include <Siv3D/Common/Siv3DEngine.hpp>

namespace s3d
{
	namespace detail
	{
		static constexpr std::array<StringView, 8> MouseButtonNames =
		{
			U"MouseL",
			U"MouseR",
			U"MouseM",
			U"MouseX1",
			U"MouseX2",
			U"MouseX3",
			U"MouseX4",
			U"MouseX5",
		};

		static constexpr std::array<StringView, 16> XInputButtonNames =
		{
				U"Dpad_Up",
				U"Dpad_Down",
				U"Dpad_Left",
				U"Dpad_Right",
				U"Menu(Start)",
				U"View(Back)",
				U"LT",
				U"RT",
				U"LB",
				U"RB",
				U"Unknown",
				U"Unknown",
				U"A",
				U"B",
				U"X",
				U"Y",
		};
	}

	String Input::name() const
	{
		switch (m_deviceType)
		{
		case InputDeviceType::Keyboard:
			return SIV3D_ENGINE(Keyboard)->name(m_code);
		case InputDeviceType::Mouse:
			assert(m_code < detail::MouseButtonNames.size());
			return String{ detail::MouseButtonNames[m_code] };
		case InputDeviceType::Gamepad:
			{
				if (InRange<uint8>(m_code, 0x80, 0x83))
				{
					static const String names[4] =
					{
						U"Up",
						U"Right",
						U"Down",
						U"Left",
					};

					return U"Gamepad-POV_" + names[m_code - 0x80];
				}

				return U"Gamepad-Button" + ToString(m_code);
			}
		case InputDeviceType::XInput:
			assert(m_code < detail::XInputButtonNames.size());
			return (U"XInput-" + detail::XInputButtonNames[m_code]);
		default:
			return{};
		}
	}

	bool Input::down() const
	{
		switch (m_deviceType)
		{
		case InputDeviceType::Keyboard:
			return SIV3D_ENGINE(Keyboard)->down(m_code);
		case InputDeviceType::Mouse:
			return SIV3D_ENGINE(Mouse)->down(m_code);
		case InputDeviceType::Gamepad:
			return SIV3D_ENGINE(Gamepad)->down(m_playerIndex, m_code);
		case InputDeviceType::XInput:
			return SIV3D_ENGINE(XInput)->down(m_playerIndex, m_code);
		default:
			return false;
		}
	}

	bool Input::pressed() const
	{
		switch (m_deviceType)
		{
		case InputDeviceType::Keyboard:
			return SIV3D_ENGINE(Keyboard)->pressed(m_code);
		case InputDeviceType::Mouse:
			return SIV3D_ENGINE(Mouse)->pressed(m_code);
		case InputDeviceType::Gamepad:
			return SIV3D_ENGINE(Gamepad)->pressed(m_playerIndex, m_code);
		case InputDeviceType::XInput:
			return SIV3D_ENGINE(XInput)->pressed(m_playerIndex, m_code);
		default:
			return false;
		}
	}

	bool Input::up() const
	{
		switch (m_deviceType)
		{
		case InputDeviceType::Keyboard:
			return SIV3D_ENGINE(Keyboard)->up(m_code);
		case InputDeviceType::Mouse:
			return SIV3D_ENGINE(Mouse)->up(m_code);
		case InputDeviceType::Gamepad:
			return SIV3D_ENGINE(Gamepad)->up(m_playerIndex, m_code);
		case InputDeviceType::XInput:
			return SIV3D_ENGINE(XInput)->up(m_playerIndex, m_code);
		default:
			return false;
		}
	}

	void Input::clearInput() const
	{
		switch (m_deviceType)
		{
		case InputDeviceType::Keyboard:
			SIV3D_ENGINE(Keyboard)->clearInput(m_code);
			break;
		case InputDeviceType::Mouse:
			SIV3D_ENGINE(Mouse)->clearInput(m_code);
			break;
		case InputDeviceType::Gamepad:
			SIV3D_ENGINE(Gamepad)->clearInput(m_playerIndex, m_code);
			break;
		case InputDeviceType::XInput:
			SIV3D_ENGINE(XInput)->clearInput(m_playerIndex, m_code);
			break;
		default:
			break;
		}
	}

	bool Input::cleared() const
	{
		switch (m_deviceType)
		{
		case InputDeviceType::Keyboard:
			return SIV3D_ENGINE(Keyboard)->cleared(m_code);
		case InputDeviceType::Mouse:
			return SIV3D_ENGINE(Mouse)->cleared(m_code);
		case InputDeviceType::Gamepad:
			return SIV3D_ENGINE(Gamepad)->cleared(m_playerIndex, m_code);
		case InputDeviceType::XInput:
			return SIV3D_ENGINE(XInput)->cleared(m_playerIndex, m_code);
		default:
			return false;
		}
	}

	Duration Input::pressedDuration() const
	{
		switch (m_deviceType)
		{
		case InputDeviceType::Keyboard:
			return SIV3D_ENGINE(Keyboard)->pressedDuration(m_code);
		case InputDeviceType::Mouse:
			return SIV3D_ENGINE(Mouse)->pressedDuration(m_code);
		case InputDeviceType::Gamepad:
			return SIV3D_ENGINE(Gamepad)->pressedDuration(m_playerIndex, m_code);
		case InputDeviceType::XInput:
			return SIV3D_ENGINE(XInput)->pressedDuration(m_playerIndex, m_code);
		default:
			return Duration{ 0 };
		}
	}

	InputGroup Input::operator |(const Input other) const
	{
		return InputGroup{ *this, other };
	}

	InputGroup Input::operator |(const InputCombination& other) const
	{
		return InputGroup{ *this, other };
	}

	InputGroup Input::operator |(const InputGroup& other) const
	{
		return InputGroup{ *this, other };
	}

	void Formatter(FormatData& formatData, const Input& value)
	{
		Formatter(formatData, value.name());
	}

	String Input::Serialize(const Input& input)
	{
		if (input.playerIndex())
		{
			return U"({}, {}, {})"_fmt(FromEnum(input.deviceType()), input.code(), input.playerIndex());
		}
		else
		{
			return U"({}, {})"_fmt(FromEnum(input.deviceType()), input.code());
		}
	}

	Input Input::Deserialize(const StringView s)
	{
		std::istringstream is{ s.toUTF8() };

		char unused;
		is >> unused;

		uint32 values[3];
		is
			>> values[0] >> unused
			>> values[1] >> unused;

		if (unused == ',')
		{
			is >> values[2] >> unused;
		}
		else
		{
			values[2] = 0;
		}

		return Input{ ToEnum<InputDeviceType>(static_cast<uint8>(values[0])),
			static_cast<uint8>(values[1]),
			static_cast<uint8>(values[2]) };
	}
}
