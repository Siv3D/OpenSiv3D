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

namespace s3d
{
	inline constexpr TextStyle TextStyle::Default() noexcept
	{
		return TextStyle{};
	}

	inline constexpr TextStyle TextStyle::CustomShader() noexcept
	{
		TextStyle style;
		style.type = Type::CustomShader;
		return style;
	}

	inline constexpr TextStyle TextStyle::Outline(const double p, const ColorF& color) noexcept
	{
		return Outline((p * 0.5), (p * 0.5), color);
	}

	inline constexpr TextStyle TextStyle::Outline(const double inner, const double outer, const ColorF& color) noexcept
	{
		TextStyle style;
		style.type = Type::Outline;
		style.param.x = static_cast<float>(0.5 + inner);
		style.param.y = static_cast<float>(0.5 - outer);
		style.outlineColor = color.toFloat4();
		return style;
	}

	inline constexpr TextStyle TextStyle::Shadow(const Vec2& offset, const ColorF& color) noexcept
	{
		TextStyle style;
		style.type = Type::Shadow;
		style.param.z = static_cast<float>(offset.x);
		style.param.w = static_cast<float>(offset.y);
		style.shadowColor = color.toFloat4();
		return style;
	}

	inline constexpr TextStyle TextStyle::OutlineShadow(const double p, const ColorF& outlineColor, const Vec2& offset, const ColorF& shadowColor) noexcept
	{
		return OutlineShadow((p * 0.5), (p * 0.5), outlineColor, offset, shadowColor);
	}

	inline constexpr TextStyle TextStyle::OutlineShadow(const double inner, const double outer, const ColorF& outlineColor, const Vec2& offset, const ColorF& shadowColor) noexcept
	{
		TextStyle style;
		style.type = Type::OutlineShadow;
		style.param.x = static_cast<float>(0.5 + inner);
		style.param.y = static_cast<float>(0.5 - outer);
		style.param.z = static_cast<float>(offset.x);
		style.param.w = static_cast<float>(offset.y);
		style.outlineColor = outlineColor.toFloat4();
		style.shadowColor = shadowColor.toFloat4();
		return style;
	}
}
