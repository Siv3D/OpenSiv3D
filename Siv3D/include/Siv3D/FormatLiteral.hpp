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
# include "String.hpp"
# include "Array.hpp"
# include "detail/FormatLiteral_impl.ipp"

namespace s3d
{
	namespace detail
	{
		struct FormatHelper;

		template <class ParseContext>
		inline auto GetFormatTag(std::u32string& representation, ParseContext& ctx)
		{
			auto it = ctx.begin();
			const auto itEnd = ctx.end();

			while (it != itEnd && (*it != '}'))
			{
				representation.push_back(*it++);
			}

			return it;
		}
	}

	[[nodiscard]]
	inline constexpr detail::FormatHelper Fmt(const char32* s) noexcept;

	[[nodiscard]]
	inline constexpr detail::FormatHelper Fmt(StringView s) noexcept;

	[[nodiscard]]
	inline detail::FormatHelper Fmt(const String& s) noexcept;

	[[nodiscard]]
	inline detail::FormatHelper Fmt(const std::u32string& s) noexcept;

	inline namespace Literals
	{
		inline namespace FormatLiterals
		{
			[[nodiscard]]
			inline constexpr detail::FormatHelper operator ""_fmt(const char32* s, size_t length) noexcept;
		}
	}
}

# include "detail/FormatLiteral.ipp"

template <>
struct SIV3D_HIDDEN fmt::formatter<s3d::String, s3d::char32>
{
	std::u32string tag;

	auto parse(basic_format_parse_context<s3d::char32>& ctx)
	{
		return s3d::detail::GetFormatTag(tag, ctx);
	}

	template <class FormatContext>
	auto format(const s3d::String& value, FormatContext& ctx)
	{
		const basic_string_view<s3d::char32> sv(value.data(), value.size());

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
struct SIV3D_HIDDEN fmt::formatter<s3d::StringView, s3d::char32>
{
	std::u32string tag;

	auto parse(basic_format_parse_context<s3d::char32>& ctx)
	{
		return s3d::detail::GetFormatTag(tag, ctx);
	}

	template <class FormatContext>
	auto format(const s3d::StringView& value, FormatContext& ctx)
	{
		const basic_string_view<s3d::char32> sv(value.data(), value.size());

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

template <class Type, class Allocator>
struct SIV3D_HIDDEN fmt::formatter<s3d::Array<Type, Allocator>, s3d::char32>
{
	std::u32string tag;

	auto parse(basic_format_parse_context<s3d::char32>& ctx)
	{
		return s3d::detail::GetFormatTag(tag, ctx);
	}

	template <class FormatContext>
	auto format(const s3d::Array<Type, Allocator>& value, FormatContext& ctx)
	{
		if (value.empty())
		{
			return format_to(ctx.out(), U"{{}}");
		}

		const std::u32string firstTag = (tag.empty() ? U"{{{}" : (U"{{{:" + tag + U"}"));
		const std::u32string secondTag = (tag.empty() ? U", {}" : (U", {:" + tag + U"}"));

		auto it = format_to(ctx.out(), firstTag, value[0]);

		for (size_t i = 1; i < value.size(); ++i)
		{
			it = format_to(it, secondTag, value[i]);
		}

		it = format_to(it, U"}}");

		return it;
	}
};

template <class Type, class Allocator>
struct SIV3D_HIDDEN fmt::formatter<std::vector<Type, Allocator>, s3d::char32>
{
	std::u32string tag;

	auto parse(basic_format_parse_context<s3d::char32>& ctx)
	{
		return s3d::detail::GetFormatTag(tag, ctx);
	}

	template <class FormatContext>
	auto format(const std::vector<Type, Allocator>& value, FormatContext& ctx)
	{
		if (value.empty())
		{
			return format_to(ctx.out(), U"{{}}");
		}

		const std::u32string firstTag = (tag.empty() ? U"{{{}" : (U"{{{:" + tag + U"}"));
		const std::u32string secondTag = (tag.empty() ? U", {}" : (U", {:" + tag + U"}"));

		auto it = format_to(ctx.out(), firstTag, value[0]);

		for (size_t i = 1; i < value.size(); ++i)
		{
			it = format_to(it, secondTag, value[i]);
		}

		it = format_to(it, U"}}");

		return it;
	}
};

template <class Type, size_t N>
struct SIV3D_HIDDEN fmt::formatter<std::array<Type, N>, s3d::char32>
{
	std::u32string tag;

	auto parse(basic_format_parse_context<s3d::char32>& ctx)
	{
		return s3d::detail::GetFormatTag(tag, ctx);
	}

	template <class FormatContext>
	auto format(const std::array<Type, N>& value, FormatContext& ctx)
	{
		if (value.empty())
		{
			return format_to(ctx.out(), U"{{}}");
		}

		const std::u32string firstTag = (tag.empty() ? U"{{{}" : (U"{{{:" + tag + U"}"));
		const std::u32string secondTag = (tag.empty() ? U", {}" : (U", {:" + tag + U"}"));

		auto it = format_to(ctx.out(), firstTag, value[0]);

		for (size_t i = 1; i < value.size(); ++i)
		{
			it = format_to(it, secondTag, value[i]);
		}

		it = format_to(it, U"}}");

		return it;
	}
};

