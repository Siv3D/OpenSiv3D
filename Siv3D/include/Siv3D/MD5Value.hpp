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
# include <array>
# include "Common.hpp"
# include "String.hpp"
# include "FormatData.hpp"
# include "Error.hpp"

namespace s3d
{
	struct MD5Value
	{
		std::array<uint8, 16> value;

		/// @brief 空のデータに対する MD5 ハッシュ値 (d41d8cd98f00b204e9800998ecf8427e) で初期化
		SIV3D_NODISCARD_CXX20
		constexpr MD5Value() noexcept;

		SIV3D_NODISCARD_CXX20
		explicit constexpr MD5Value(const std::array<uint8, 16>& md5) noexcept;

		SIV3D_NODISCARD_CXX20
		explicit constexpr MD5Value(std::string_view md5);

		SIV3D_NODISCARD_CXX20
		explicit constexpr MD5Value(StringView md5);

		[[nodiscard]]
		std::string asStdString() const;

		[[nodiscard]]
		String asString() const;

		[[nodiscard]]
		size_t hash() const noexcept;

	# if __cpp_lib_three_way_comparison

		[[nodiscard]]
		friend /*constexpr*/ auto operator <=>(const MD5Value&, const MD5Value&) = default;

	# else

		[[nodiscard]]
		friend /*constexpr*/ bool operator ==(const MD5Value& lhs, const MD5Value& rhs) noexcept
		{
			return (lhs.value == rhs.value);
		}

		[[nodiscard]]
		friend /*constexpr*/ bool operator !=(const MD5Value& lhs, const MD5Value& rhs) noexcept
		{
			return (lhs.value != rhs.value);
		}

		[[nodiscard]]
		friend /*constexpr*/ bool operator <(const MD5Value& lhs, const MD5Value& rhs) noexcept
		{
			return (lhs.value < rhs.value);
		}

		[[nodiscard]]
		friend /*constexpr*/ bool operator <=(const MD5Value& lhs, const MD5Value& rhs) noexcept
		{
			return (lhs.value <= rhs.value);
		}

		[[nodiscard]]
		friend /*constexpr*/ bool operator >(const MD5Value& lhs, const MD5Value& rhs) noexcept
		{
			return (lhs.value > rhs.value);
		}

		[[nodiscard]]
		friend /*constexpr*/ bool operator >=(const MD5Value& lhs, const MD5Value& rhs) noexcept
		{
			return (lhs.value >= rhs.value);
		}

	# endif

		friend void Formatter(FormatData& formatData, const MD5Value& value);
	};
}

//////////////////////////////////////////////////
//
//	Hash
//
//////////////////////////////////////////////////

template <>
struct std::hash<s3d::MD5Value>
{
	[[nodiscard]]
	size_t operator ()(const s3d::MD5Value& value) const noexcept
	{
		return value.hash();
	}
};

# include "detail/MD5Value.ipp"
