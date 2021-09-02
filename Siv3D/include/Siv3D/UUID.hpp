//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2021 Ryo Suzuki
//	Copyright (c) 2016-2021 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# pragma once
# include <array>
# include "Common.hpp"
# include "StringView.hpp"
# include "Optional.hpp"

namespace s3d
{
	class UUID
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
		UUID() = default;

		SIV3D_NODISCARD_CXX20
		explicit UUID(const value_type(&uuid)[16]) noexcept;

		SIV3D_NODISCARD_CXX20
		explicit constexpr UUID(const std::array<value_type, 16>& uuid) noexcept;

		template <class Iterator>
		SIV3D_NODISCARD_CXX20
		explicit UUID(Iterator first, Iterator last);

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

		void swap(UUID& other);

		[[nodiscard]]
		size_t hash() const noexcept;

		[[nodiscard]]
		friend bool operator ==(const UUID& lhs, const UUID& rhs) noexcept
		{
			return (lhs.m_data == rhs.m_data);
		}

		[[nodiscard]]
		friend bool operator !=(const UUID& lhs, const UUID& rhs) noexcept
		{
			return (lhs.m_data != rhs.m_data);
		}

		[[nodiscard]]
		friend bool operator <(const UUID& lhs, const UUID& rhs) noexcept
		{
			return (lhs.m_data < rhs.m_data);
		}

		[[nodiscard]]
		static UUID Generate();

		[[nodiscard]]
		static UUID GenerateFromRNG(DefaultRNG& rng = GetDefaultRNG());

		[[nodiscard]]
		static UUID GenerateFromName(const UUID& namespaceUUID, const std::string& name);

		[[nodiscard]]
		static UUID GenerateFromName(const UUID& namespaceUUID, const String& name);

		[[nodiscard]]
		static UUID Nil();

		[[nodiscard]]
		static UUID NamespaceDNS() noexcept;

		[[nodiscard]]
		static UUID NamespaceURL() noexcept;

		[[nodiscard]]
		static UUID NamespaceOID() noexcept;

		[[nodiscard]]
		static UUID NamespaceX500() noexcept;

		[[nodiscard]]
		static bool IsValid(std::string_view uuid);

		[[nodiscard]]
		static bool IsValid(StringView uuid);

		[[nodiscard]]
		static Optional<UUID> Parse(std::string_view uuid);

		[[nodiscard]]
		static Optional<UUID> Parse(StringView uuid);

		template <class CharType>
		friend std::basic_ostream<CharType>& operator <<(std::basic_ostream<CharType>& output, const UUID& value)
		{
			return (output << value.str());
		}

		friend void Formatter(FormatData& formatData, const UUID& value);

	private:

		std::array<value_type, 16> m_data{};
	};
}

template <>
struct SIV3D_HIDDEN fmt::formatter<s3d::UUID, s3d::char32>
{
	std::u32string tag;

	auto parse(basic_format_parse_context<s3d::char32>& ctx)
	{
		return s3d::detail::GetFormatTag(tag, ctx);
	}

	template <class FormatContext>
	auto format(const s3d::UUID& value, FormatContext& ctx)
	{
		const s3d::String s = value.str();
		const basic_string_view<s3d::char32> sv(s.data(), s.size());

		if (tag.empty())
		{
			return format_to(ctx.out(), sv);
		}
		else
		{
			const std::u32string format = (U"{:" + tag + U'}');
			return format_to(ctx.out(), format, sv);
		}
	}
};

template <>
struct std::hash<s3d::UUID>
{
	[[nodiscard]]
	size_t operator()(const s3d::UUID& value) const noexcept
	{
		return value.hash();
	}
};

template <>
inline void std::swap(s3d::UUID& a, s3d::UUID& b) noexcept;

# include "detail/UUID.ipp"
