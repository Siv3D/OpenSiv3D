//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2023 Ryo Suzuki
//	Copyright (c) 2016-2023 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# include <Siv3D/TexturedRoundRect.hpp>
# include <Siv3D/Renderer2D/IRenderer2D.hpp>
# include <Siv3D/Common/Siv3DEngine.hpp>

namespace s3d
{
	namespace detail
	{
		[[nodiscard]]
		inline constexpr Vertex2D::IndexType CaluculateFanQuality(const float r) noexcept
		{
			return r <= 1.0f ? 3
				: r <= 6.0f ? 5
				: r <= 12.0f ? 8
				: static_cast<Vertex2D::IndexType>(Min(64.0f, r * 0.2f + 6));
		}
	}

	TexturedRoundRect::TexturedRoundRect(const Texture& _texture, const float l, const float t, const float r, const float b, const RoundRect& _rect)
		: rect{ _rect }
		, texture{ _texture }
		, uvRect{ l, t, r, b } {}

	TexturedRoundRect::TexturedRoundRect(const Texture& _texture, const FloatRect& _uvRect, const RoundRect& _rect)
		: rect{ _rect }
		, texture{ _texture }
		, uvRect{ _uvRect } {}

	const RoundRect& TexturedRoundRect::draw(const ColorF& diffuse) const
	{
		SIV3D_ENGINE(Renderer2D)->addTexturedRoundRect(texture,
			FloatRect{ rect.x, rect.y, (rect.x + rect.w), (rect.y + rect.h) },
			static_cast<float>(rect.w),
			static_cast<float>(rect.h),
			static_cast<float>(rect.r),
			uvRect, diffuse.toFloat4());
		return rect;
	}

	RoundRect TexturedRoundRect::draw(const double x, const double y, const ColorF& diffuse) const
	{
		const RoundRect rr = rect.movedBy(x, y);

		return TexturedRoundRect{ texture, uvRect, rr }.draw(diffuse);
	}

	RoundRect TexturedRoundRect::draw(const Vec2& pos, const ColorF& diffuse) const
	{
		return draw(pos.x, pos.y, diffuse);
	}

	RoundRect TexturedRoundRect::drawAt(const double x, const double y, const ColorF& diffuse) const
	{
		return TexturedRoundRect(texture, uvRect, RoundRect(Arg::center(x, y), rect.w, rect.h, rect.r)).draw(diffuse);
	}

	RoundRect TexturedRoundRect::drawAt(const Vec2& pos, const ColorF& diffuse) const
	{
		return drawAt(pos.x, pos.y, diffuse);
	}
}
