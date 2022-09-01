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
# if  __has_include(<compare>)
#	include <compare>
# endif
# include "Common.hpp"
# include "StringView.hpp"
# include "Optional.hpp"

namespace s3d
{
	class UUIDValue
	{
	public:

		enum class Variant
		{
			NCS,
			RFC,
			Microsoft,
			Reserved,
		};

		enum class Version
		{
			Nil,
			TimeBased,
			DCE,
			NameBasedMD5,
			Random,
			NameBasedSHA1,
		};

		using value_type = uint8;

		SIV3D_NODISCARD_CXX20
		UUIDValue() = default;

		SIV3D_NODISCARD_CXX20
		explicit UUIDValue(const value_type(&uuid)[16]) noexcept;

		SIV3D_NODISCARD_CXX20
		explicit constexpr UUIDValue(const std::array<value_type, 16>& uuid) noexcept;

		template <class Iterator>
		SIV3D_NODISCARD_CXX20
		explicit UUIDValue(Iterator first, Iterator last);

		[[nodiscard]]
		constexpr bool isNil() const noexcept;

		[[nodiscard]]
		Variant variant() const noexcept;

		[[nodiscard]]
		Version version() const noexcept;

		[[nodiscard]]
		std::string to_string() const;

		[[nodiscard]]
		String str() const;

		[[nodiscard]]
		constexpr const std::array<value_type, 16>& getData() const noexcept;

		void swap(UUIDValue& other);

		[[nodiscard]]
		size_t hash() const noexcept;

#if __cpp_impl_three_way_comparison

		[[nodiscard]]
		std::strong_ordering operator <=>(const UUIDValue& rhs) const noexcept = default;

#else

		[[nodiscard]]
		friend bool operator ==(const UUIDValue& lhs, const UUIDValue& rhs) noexcept
		{
			return (lhs.m_data == rhs.m_data);
		}

		[[nodiscard]]
		friend bool operator !=(const UUIDValue& lhs, const UUIDValue& rhs) noexcept
		{
			return (lhs.m_data != rhs.m_data);
		}

		[[nodiscard]]
		friend bool operator <(const UUIDValue& lhs, const UUIDValue& rhs) noexcept
		{
			return (lhs.m_data < rhs.m_data);
		}

#endif

		[[nodiscard]]
		static UUIDValue Generate();

		[[nodiscard]]
		static UUIDValue GenerateFromRNG(DefaultRNG& rng = GetDefaultRNG());

		[[nodiscard]]
		static UUIDValue GenerateFromName(const UUIDValue& namespaceUUIDValue, const std::string& name);

		[[nodiscard]]
		static UUIDValue GenerateFromName(const UUIDValue& namespaceUUIDValue, const String& name);

		[[nodiscard]]
		static UUIDValue Nil();

		[[nodiscard]]
		static UUIDValue NamespaceDNS() noexcept;

		[[nodiscard]]
		static UUIDValue NamespaceURL() noexcept;

		[[nodiscard]]
		static UUIDValue NamespaceOID() noexcept;

		[[nodiscard]]
		static UUIDValue NamespaceX500() noexcept;

		[[nodiscard]]
		static bool IsValid(std::string_view uuid);

		[[nodiscard]]
		static bool IsValid(StringView uuid);

		[[nodiscard]]
		static Optional<UUIDValue> Parse(std::string_view uuid);

		[[nodiscard]]
		static Optional<UUIDValue> Parse(StringView uuid);

		template <class CharType>
		friend std::basic_ostream<CharType>& operator <<(std::basic_ostream<CharType>& output, const UUIDValue& value)
		{
			return (output << value.str());
		}

		friend void Formatter(FormatData& formatData, const UUIDValue& value);

	private:

		std::array<value_type, 16> m_data{};
	};
}

template <>
struct SIV3D_HIDDEN fmt::formatter<s3d::UUIDValue, s3d::char32>
{
	std::u32string tag;

	auto parse(basic_format_parse_context<s3d::char32>& ctx)
	{
		return s3d::detail::GetFormatTag(tag, ctx);
	}

	template <class FormatContext>
	auto format(const s3d::UUIDValue& value, FormatContext& ctx)
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
struct std::hash<s3d::UUIDValue>
{
	[[nodiscard]]
	size_t operator ()(const s3d::UUIDValue& value) const noexcept
	{
		return value.hash();
	}
};

template <>
inline void std::swap(s3d::UUIDValue& a, s3d::UUIDValue& b) noexcept;

# include "detail/UUIDValue.ipp"
