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

# include "NinePatchDetail.hpp"
# include <Siv3D/TextureRegion.hpp>
# include <Siv3D/TexturedQuad.hpp>
# include <Siv3D/Shader.hpp>
# include <Siv3D/ScopedRenderStates2D.hpp>

namespace s3d
{
	NinePatch::NinePatchDetail::NinePatchDetail(const Image& image, const int32 leftWidth, const int32 topHeight, const int32 rightWidth, const int32 bottomHeight, const Style& style)
		: m_style{ style }
		, m_texture{ image }
		, m_patchSize{ leftWidth, topHeight, rightWidth, bottomHeight, m_texture.size() }
	{
		const int32 textureWidth = m_texture.width();
		const int32 textureHeight = m_texture.height();
		const int32 centerWidth = (textureWidth - (m_patchSize.left + m_patchSize.right));
		const int32 centerHeight = (textureHeight - (m_patchSize.top + m_patchSize.bottom));

		if (m_style.tileTopBottom)
		{
			m_repeatableTexture.top = RenderTexture{ image.clipped(m_patchSize.left, 0, centerWidth, m_patchSize.top) };
			m_repeatableTexture.bottom = RenderTexture{ image.clipped(m_patchSize.left, (textureHeight - m_patchSize.bottom), centerWidth, m_patchSize.bottom) };
		}

		if (m_style.tileLeftRight)
		{
			m_repeatableTexture.left = RenderTexture{ image.clipped(0, m_patchSize.top, m_patchSize.left, centerHeight) };
			m_repeatableTexture.right = RenderTexture{ image.clipped((textureWidth - m_patchSize.right), m_patchSize.top, m_patchSize.right, centerHeight) };
		}

		if (m_style.tileCenter)
		{
			m_repeatableTexture.center = RenderTexture{ image.clipped(m_patchSize.left, m_patchSize.top, centerWidth, centerHeight) };
		}
	}

	NinePatch::NinePatchDetail::NinePatchDetail(const Texture& texture, const int32 leftWidth, const int32 topHeight, const int32 rightWidth, const int32 bottomHeight, const Style& style)
		: m_style{ style }
		, m_texture{ texture }
		, m_patchSize{ leftWidth, topHeight, rightWidth, bottomHeight, m_texture.size() }
	{
		const int32 textureWidth = m_texture.width();
		const int32 textureHeight = m_texture.height();
		const int32 centerWidth = (textureWidth - (m_patchSize.left + m_patchSize.right));
		const int32 centerHeight = (textureHeight - (m_patchSize.top + m_patchSize.bottom));

		if (m_style.tileTopBottom)
		{
			m_repeatableTexture.top = RenderTexture{ Size{ centerWidth, m_patchSize.top } };
			Shader::Copy(m_texture(m_patchSize.left, 0, centerWidth, m_patchSize.top), m_repeatableTexture.top);

			m_repeatableTexture.bottom = RenderTexture{ Size{ centerWidth, m_patchSize.bottom } };
			Shader::Copy(m_texture(m_patchSize.left, (textureHeight - m_patchSize.bottom), centerWidth, m_patchSize.bottom), m_repeatableTexture.bottom);
		}

		if (m_style.tileLeftRight)
		{
			m_repeatableTexture.left = RenderTexture{ Size{ m_patchSize.left, centerHeight } };
			Shader::Copy(m_texture(0, m_patchSize.top, m_patchSize.left, centerHeight), m_repeatableTexture.left);

			m_repeatableTexture.right = RenderTexture{ Size{ m_patchSize.right, centerHeight } };
			Shader::Copy(m_texture((textureWidth - m_patchSize.right), m_patchSize.top, m_patchSize.right, centerHeight), m_repeatableTexture.right);
		}

		if (m_style.tileCenter)
		{
			m_repeatableTexture.center = RenderTexture{ Size{ centerWidth, centerHeight } };
			Shader::Copy(m_texture(m_patchSize.left, m_patchSize.top, centerWidth, centerHeight), m_repeatableTexture.center);
		}
	}

	void NinePatch::NinePatchDetail::draw(const RectF& rect, const double textureScale, const TextureFilter textureFilter, const ColorF& color) const
	{
		const double left = (m_patchSize.left * textureScale);
		const double top = (m_patchSize.top * textureScale);
		const double right = (m_patchSize.right * textureScale);
		const double bottom = (m_patchSize.bottom * textureScale);
		const double topBottomWidth = (rect.w - (left + right));
		const double leftRightHeight = (rect.h - (top + bottom));
		const bool showTopBottom = (0.0 <= topBottomWidth);
		const bool showLeftRight = (0.0 <= leftRightHeight);
		const int32 textureWidth = m_texture.width();
		const int32 textureHeight = m_texture.height();
		const int32 centerWidth = (textureWidth - (m_patchSize.left + m_patchSize.right));
		const int32 centerHeight = (textureHeight - (m_patchSize.top + m_patchSize.bottom));

		const RectF topLeftRect{ rect.pos, left, top };
		const RectF topRect{ (rect.x + left), rect.y, topBottomWidth, top };
		const RectF topRightRect{ (rect.x + rect.w - right), rect.y, right, top };
		const RectF leftRect{ rect.x, (rect.y + top), left, leftRightHeight };
		const RectF centerRect{ (rect.x + left), (rect.y + top), topBottomWidth, leftRightHeight };
		const RectF rightRect{ (rect.x + rect.w - right), (rect.y + top), right, leftRightHeight };
		const RectF bottomLeftRect{ rect.x, (rect.y + rect.h - bottom), left, bottom };
		const RectF bottomRect{ (rect.x + left), (rect.y + rect.h - bottom), topBottomWidth, bottom };
		const RectF bottomRightRect{ (rect.x + rect.w - right), (rect.y + rect.h - bottom), right, bottom };

		if (((not showTopBottom) || (not showLeftRight)) && m_style.fallbackToSimple)
		{
			if (not m_style.tileCenter)
			{
				const ScopedRenderStates2D sampler{ (textureFilter == TextureFilter::Nearest) ? SamplerState::ClampNearest : SamplerState::ClampLinear };
				rect(m_texture(m_patchSize.left, m_patchSize.top, centerWidth, centerHeight)).draw(color);
			}
			else
			{
				const ScopedRenderStates2D sampler{ (textureFilter == TextureFilter::Nearest) ? SamplerState::RepeatNearest : SamplerState::RepeatLinear };
				const double uWidth = (rect.w / (centerWidth * textureScale));
				const double vHeight = (rect.h / (centerHeight * textureScale));
				rect(m_repeatableTexture.center.uv(0.0, 0.0, uWidth, vHeight)).draw();
			}
		}
		else
		{
			{
				const ScopedRenderStates2D sampler{ (textureFilter == TextureFilter::Nearest) ? SamplerState::ClampNearest : SamplerState::ClampLinear };

				// top-left
				topLeftRect(m_texture(0, 0, m_patchSize.left, m_patchSize.top)).draw(color);

				// top
				if ((not m_style.tileTopBottom) && showTopBottom)
				{
					topRect(m_texture(m_patchSize.left, 0, centerWidth, m_patchSize.top)).draw(color);
				}

				// top-right
				topRightRect(m_texture((textureWidth - m_patchSize.right), 0, m_patchSize.right, m_patchSize.top)).draw(color);

				// left
				if ((not m_style.tileLeftRight) && showLeftRight)
				{
					leftRect(m_texture(0, m_patchSize.top, m_patchSize.left, centerHeight)).draw(color);
				}

				// center
				if ((not m_style.tileCenter) && showTopBottom && showLeftRight)
				{
					centerRect(m_texture(m_patchSize.left, m_patchSize.top, centerWidth, centerHeight)).draw(color);
				}

				// right
				if ((not m_style.tileLeftRight) && showLeftRight)
				{
					rightRect(m_texture((textureWidth - m_patchSize.right), m_patchSize.top, m_patchSize.right, centerHeight)).draw(color);
				}

				// bottom-left
				bottomLeftRect(m_texture(0, (textureHeight - m_patchSize.bottom), m_patchSize.left, m_patchSize.bottom)).draw(color);

				// bottom
				if ((not m_style.tileTopBottom) && showTopBottom)
				{
					bottomRect(m_texture(m_patchSize.left, (textureHeight - m_patchSize.bottom), centerWidth, m_patchSize.bottom)).draw(color);
				}

				// bottom-right
				bottomRightRect(m_texture((textureWidth - m_patchSize.right), (textureHeight - m_patchSize.bottom), m_patchSize.right, m_patchSize.bottom)).draw(color);
			}

			if (m_style.tileTopBottom || m_style.tileLeftRight || m_style.tileCenter)
			{
				const ScopedRenderStates2D sampler{ (textureFilter == TextureFilter::Nearest) ? SamplerState::RepeatNearest : SamplerState::RepeatLinear };
				const double uWidth = (topRect.w / (centerWidth * textureScale));
				const double vHeight = (leftRect.h / (centerHeight * textureScale));

				if (m_style.tileTopBottom && showTopBottom)
				{
					topRect(m_repeatableTexture.top.uv(0.0, 0.0, uWidth, 1.0)).draw();
					bottomRect(m_repeatableTexture.bottom.uv(0.0, 0.0, uWidth, 1.0)).draw();
				}

				if (m_style.tileLeftRight && showLeftRight)
				{
					leftRect(m_repeatableTexture.left.uv(0.0, 0.0, 1.0, vHeight)).draw();
					rightRect(m_repeatableTexture.right.uv(0.0, 0.0, 1.0, vHeight)).draw();
				}

				if (m_style.tileCenter && showTopBottom && showLeftRight)
				{
					centerRect(m_repeatableTexture.center.uv(0.0, 0.0, uWidth, vHeight)).draw();
				}
			}
		}
	}

	void NinePatch::NinePatchDetail::release()
	{
		m_style = Style::Default();
		m_texture.release();
		m_repeatableTexture = RepeatableTexture{};
		m_patchSize = PatchSize{};
	}

	const Texture& NinePatch::NinePatchDetail::getTexture() const noexcept
	{
		return m_texture;
	}

	const NinePatch::RepeatableTexture& NinePatch::NinePatchDetail::getRepeatableTexture() const noexcept
	{
		return m_repeatableTexture;
	}

	const NinePatch::PatchSize& NinePatch::NinePatchDetail::getPatchSize() const noexcept
	{
		return m_patchSize;
	}
}
