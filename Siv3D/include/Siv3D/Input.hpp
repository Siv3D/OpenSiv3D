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
# if  __has_include(<bit>)
#	include <bit>
# endif
# if  __has_include(<compare>)
#	include <compare>
# endif
# include "Common.hpp"
# include "InputDevice.hpp"
# include "Duration.hpp"
# include "String.hpp"

namespace s3d
{
	class InputCombination;
	class InputGroup;

	/// @brief 入力オブジェクト
	/// @remark キーボード、マウスのボタン、ゲームパッドのボタンなど、押下できる入力装置の要素を表現します。
	class Input
	{
	public:

		SIV3D_NODISCARD_CXX20
		Input() = default;

		SIV3D_NODISCARD_CXX20
		constexpr Input(InputDeviceType deviceType, uint8 code, uint8 playerIndex = 0) noexcept;

		/// @brief デバイスの種類を返します。
		/// @return デバイスの種類
		[[nodiscard]]
		constexpr InputDeviceType deviceType() const noexcept;

		[[nodiscard]]
		constexpr uint8 code() const noexcept;

		[[nodiscard]]
		constexpr uint8 playerIndex() const noexcept;

		/// @brief 入力オブジェクトの名前を返します。
		/// @return 入力オブジェクトの名前
		[[nodiscard]] 
		String name() const;

		/// @brief 入力オブジェクトが現在のフレームで押され始めたかを返します。
		/// @return 入力オブジェクトが現在のフレームで押され始めた場合 true, それ以外の場合は false
		[[nodiscard]]
		bool down() const;

		/// @brief 入力オブジェクトが押されているかを返します。
		/// @return 入力オブジェクトが押されている場合 true, それ以外の場合は false
		[[nodiscard]]
		bool pressed() const;

		/// @brief 入力オブジェクトが現在のフレームで離されたかを返します。
		/// @return 入力オブジェクトが現在のフレームで離された場合 true, それ以外の場合は false
		[[nodiscard]]
		bool up() const;

		/// @brief 入力オブジェクトが押され続けている時間を返します。
		/// @remark `up()` が true を返すフレームまで計測結果は有効なため、`if (KeyA.up()) Print << KeyA.pressedDuration()` と書けます。
		/// @return 入力オブジェクトが押され続けている時間
		[[nodiscard]] 
		Duration pressedDuration() const;

		[[nodiscard]]
		constexpr InputCombination operator +(Input other) const noexcept;

		[[nodiscard]]
		InputGroup operator |(Input other) const;
		
		[[nodiscard]]
		InputGroup operator |(const InputCombination& other) const;

		[[nodiscard]]
		InputGroup operator |(const InputGroup& other) const;

		[[nodiscard]]
		constexpr uint32 asUint32() const noexcept;

	# if __cpp_impl_three_way_comparison

		[[nodiscard]]
		friend constexpr bool operator ==(Input lhs, Input rhs) noexcept
		{
			return (lhs.asUint32() == rhs.asUint32());
		}

		[[nodiscard]]
		friend constexpr auto operator <=>(Input lhs, Input rhs) noexcept
		{
			return (lhs.asUint32() <=> rhs.asUint32());
		}

	# else

		[[nodiscard]]
		friend constexpr bool operator ==(Input lhs, Input rhs) noexcept
		{
			return (lhs.asUint32() == rhs.asUint32());
		}

		[[nodiscard]]
		friend constexpr bool operator !=(Input lhs, Input rhs) noexcept
		{
			return (lhs.asUint32() != rhs.asUint32());
		}

		[[nodiscard]]
		friend constexpr bool operator <(Input lhs, Input rhs) noexcept
		{
			return (lhs.asUint32() < rhs.asUint32());
		}

		[[nodiscard]]
		friend constexpr bool operator <=(Input lhs, Input rhs) noexcept
		{
			return (lhs.asUint32() <= rhs.asUint32());
		}

		[[nodiscard]]
		friend constexpr bool operator >(Input lhs, Input rhs) noexcept
		{
			return (lhs.asUint32() > rhs.asUint32());
		}

		[[nodiscard]]
		friend constexpr bool operator >=(Input lhs, Input rhs) noexcept
		{
			return (lhs.asUint32() >= rhs.asUint32());
		}

	# endif

		template <class CharType>
		friend std::basic_ostream<CharType>& operator <<(std::basic_ostream<CharType>& output, const Input& value)
		{
			return output << value.name();
		}

		friend void Formatter(FormatData& formatData, const Input& value);

	private:

		InputDeviceType m_deviceType = InputDeviceType::Undefined;

		uint8 m_code = 0;

		uint8 m_playerIndex = 0;

		SIV3D_MAYBE_UNUSED_NSDM uint8 m_reserved = 0;
	};
}
