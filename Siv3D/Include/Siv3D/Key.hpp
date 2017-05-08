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

		S3D_MAYBE_UNUSED uint8 m_reserved = 0;

	public:

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
		bool down() const;

		/// <summary>
		/// キーが押されていることを示します。
		/// </summary>
		/// <returns>
		/// キーが押されている場合 true, それ以外の場合は false
		/// </returns>
		bool pressed() const;

		/// <summary>
		/// キーが離されたことを示します。
		/// </summary>
		/// <returns>
		/// キーが離された場合 true, 押されていたり、すでに離されていたりした場合は false
		/// </returns>
		bool up() const;

		MillisecondsF pressedDuration() const;

		constexpr InputDevice inputDevice() const noexcept
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

		constexpr uint32 asUint32() const noexcept
		{
			return (uint32(m_device) << 24) | (uint32(m_userIndex) << 16) | (uint32(m_code) << 8);
		}

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
		return key1.asUint32() == key2.asUint32();
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
		return key1.asUint32() != key2.asUint32();
	}

	constexpr inline bool operator <(const Key& key1, const Key& key2) noexcept
	{
		return key1.asUint32() < key2.asUint32();
	}

	constexpr inline bool operator <=(const Key& key1, const Key& key2) noexcept
	{
		return key1.asUint32() <= key2.asUint32();
	}

	constexpr inline bool operator >(const Key& key1, const Key& key2) noexcept
	{
		return key1.asUint32() > key2.asUint32();
	}

	constexpr inline bool operator >=(const Key& key1, const Key& key2) noexcept
	{
		return key1.asUint32() >= key2.asUint32();
	}
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
