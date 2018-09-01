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
# include "Duration.hpp"

namespace s3d
{
	enum class InputDevice : uint8
	{
		None,

		Keyboard,

		Mouse,

		Gamepad,

		XInput,
	};

	class Key
	{
	private:

		InputDevice m_device = InputDevice::None;

		uint8 m_code = 0;

		uint8 m_userIndex = 0;

		[[maybe_unused]] uint8 m_reserved = 0;

	public:

		Key() = default;

		constexpr Key(InputDevice device, uint8 code, uint8 userIndex = 0) noexcept
			: m_device(device)
			, m_code(code)
			, m_userIndex(userIndex) {}

		/// <summary>
		/// キーが押され始めたことを示します。
		/// </summary>
		/// <returns>
		/// キーが押され始めた場合 true, 押されていなかったり、すでに押されていたりした場合は false
		/// </returns>
		[[nodiscard]] bool down() const;

		/// <summary>
		/// キーが押されていることを示します。
		/// </summary>
		/// <returns>
		/// キーが押されている場合 true, それ以外の場合は false
		/// </returns>
		[[nodiscard]] bool pressed() const;

		/// <summary>
		/// キーが離されたことを示します。
		/// </summary>
		/// <returns>
		/// キーが離された場合 true, 押されていたり、すでに離されていたりした場合は false
		/// </returns>
		[[nodiscard]] bool up() const;

		[[nodiscard]] Duration pressedDuration() const;

		[[nodiscard]] constexpr InputDevice inputDevice() const noexcept
		{
			return m_device;
		}

		[[nodiscard]] constexpr uint8 code() const noexcept
		{
			return m_code;
		}

		[[nodiscard]] constexpr uint8 userIndex() const noexcept
		{
			return m_userIndex;
		}

		[[nodiscard]] constexpr uint32 asUint32() const noexcept
		{
			return (uint32(m_device) << 24) | (uint32(m_userIndex) << 16) | (uint32(m_code) << 8);
		}

		[[nodiscard]] String name() const;

		/// <summary>
		/// 2 つのキーが同じキーを示しているかを返します。
		/// </summary>
		/// <param name="other">
		/// 比較するキー
		/// </param>
		/// <returns>
		/// 2 つのキーが同じキーを示している場合 true, それ以外の場合は false
		/// </returns>
		[[nodiscard]] constexpr bool operator ==(const Key& other) const noexcept
		{
			return asUint32() == other.asUint32();
		}

		/// <summary>
		/// 2 つのキーが異なるキーを示しているかを返します。
		/// </summary>
		/// <param name="other">
		/// 比較するキー
		/// </param>
		/// <returns>
		/// 2 つのキーが異なるキーを示している場合 true, それ以外の場合は false
		/// </returns>
		[[nodiscard]] constexpr bool operator !=(const Key& other) const noexcept
		{
			return asUint32() != other.asUint32();
		}

		[[nodiscard]] constexpr bool operator <(const Key& other) const noexcept
		{
			return asUint32() < other.asUint32();
		}

		[[nodiscard]] constexpr bool operator <=(const Key& other) const noexcept
		{
			return asUint32() <= other.asUint32();
		}

		[[nodiscard]] constexpr bool operator >(const Key& other) const noexcept
		{
			return asUint32() > other.asUint32();
		}

		[[nodiscard]] constexpr bool operator >=(const Key& other) const noexcept
		{
			return asUint32() >= other.asUint32();
		}
	};
}

//////////////////////////////////////////////////////////////////////////////
//
//	Formatting Key
//
//	[x] Siv3D Formatter
//	[x] ostream
//	[x] wostream
//	[ ] istream
//	[ ] wistream
//	[p] fmtlib BasicFormatter<wchar>
//
namespace s3d
{
	inline void Formatter(FormatData& formatData, const Key& key)
	{
		formatData.string.append(key.name());
	}

	template <class CharType>
	inline std::basic_ostream<CharType> & operator <<(std::basic_ostream<CharType> os, const Key& key)
	{
		return os << key.name();
	}
}
//
//////////////////////////////////////////////////////////////////////////////
