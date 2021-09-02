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
# include "Common.hpp"
# include "PointVector.hpp"
# include "ColorHSV.hpp"

namespace s3d
{
	struct TextStyle
	{
		Float4 param = { 0.5f, 0.5f, 0.0f, 0.0f };

		Float4 outlineColor = { 0.0f, 0.0f, 0.0f, 1.0f };

		Float4 shadowColor = { 0.0f, 0.0f, 0.0f, 0.5f };

		enum class Type : uint8
		{
			Default,
			Outline,
			Shadow,
			OutlineShadow,
			CustomShader,
		} type = Type::Default;

		[[nodiscard]]
		static constexpr TextStyle Default() noexcept;

		[[nodiscard]]
		static constexpr TextStyle CustomShader() noexcept;

		[[nodiscard]]
		static constexpr TextStyle Outline(double p, const ColorF& color) noexcept;

		[[nodiscard]]
		static constexpr TextStyle Outline(double inner, double outer, const ColorF& color) noexcept;

		[[nodiscard]]
		static constexpr TextStyle Shadow(const Vec2& offset, const ColorF& color) noexcept;
		
		[[nodiscard]]
		static constexpr TextStyle OutlineShadow(double p, const ColorF& outlineColor, const Vec2& offset, const ColorF& shadowColor) noexcept;

		[[nodiscard]]
		static constexpr TextStyle OutlineShadow(double inner, double outer, const ColorF& outlineColor, const Vec2& offset, const ColorF& shadowColor) noexcept;
	};
}

# include "detail/TextStyle.ipp"
