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
# include "FormatLiteral.hpp"

namespace s3d
{
	class IPv4Address
	{
	public:

		using value_type = uint8;

		SIV3D_NODISCARD_CXX20
		IPv4Address() = default;

		SIV3D_NODISCARD_CXX20
		constexpr IPv4Address(value_type a, value_type b, value_type c, value_type d) noexcept;

		SIV3D_NODISCARD_CXX20
		explicit IPv4Address(const value_type(&ipv4)[4]) noexcept;

		SIV3D_NODISCARD_CXX20
		explicit constexpr IPv4Address(const std::array<value_type, 4>& ipv4) noexcept;

		SIV3D_NODISCARD_CXX20
		explicit IPv4Address(std::string_view ipv4);

		SIV3D_NODISCARD_CXX20
		explicit IPv4Address(StringView ipv4);

		constexpr bool isLoopback() const noexcept;

		[[nodiscard]]
		std::string to_string() const;

		[[nodiscard]]
		String str() const;

		[[nodiscard]]
		constexpr const std::array<value_type, 4>& getData() const noexcept;

		void swap(IPv4Address& other);

		[[nodiscard]]
		size_t hash() const noexcept;

		[[nodiscard]]
		friend bool operator ==(const IPv4Address& lhs, const IPv4Address& rhs) noexcept
		{
			return (lhs.m_data == rhs.m_data);
		}

		[[nodiscard]]
		friend bool operator !=(const IPv4Address& lhs, const IPv4Address& rhs) noexcept
		{
			return (lhs.m_data != rhs.m_data);
		}

		[[nodiscard]]
		friend bool operator <(const IPv4Address& lhs, const IPv4Address& rhs) noexcept
		{
			return (lhs.m_data < rhs.m_data);
		}

		[[nodiscard]]
		static constexpr IPv4Address Localhost() noexcept;

		template <class CharType>
		friend std::basic_ostream<CharType>& operator <<(std::basic_ostream<CharType>& output, const IPv4Address& value)
		{
			return (output << value.str());
		}

		friend void Formatter(FormatData& formatData, const IPv4Address& value);

	private:

		std::array<value_type, 4> m_data{};
	};
}

template <>
struct SIV3D_HIDDEN fmt::formatter<s3d::IPv4Address, s3d::char32>
{
	std::u32string tag;

	auto parse(basic_format_parse_context<s3d::char32>& ctx)
	{
		return s3d::detail::GetFormatTag(tag, ctx);
	}

	template <class FormatContext>
	auto format(const s3d::IPv4Address& value, FormatContext& ctx)
	{
		const s3d::String s = value.str();
		const basic_string_view<s3d::char32> sv(s.data(), s.size());

		if (tag.empty())
		{
			return format_to(ctx.out(), U"{}", sv);
		}
		else
		{
			const std::u32string format = (U"{:" + tag + U'}');
			return format_to(ctx.out(), format, sv);
		}
	}
};

template <>
struct std::hash<s3d::IPv4Address>
{
	[[nodiscard]]
	size_t operator ()(const s3d::IPv4Address& value) const noexcept
	{
		return value.hash();
	}
};

template <>
inline void std::swap(s3d::IPv4Address& a, s3d::IPv4Address& b) noexcept;

# include "detail/IPv4Address.ipp"
