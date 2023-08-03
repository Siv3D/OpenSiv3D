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
	NinePatch::NinePatchDetail::NinePatchDetail(const Texture& texture, const int32 leftWidth, const int32 topHeight, const int32 rightWidth, const int32 bottomHeight, const Style& style)
		: m_style{ style }
		, m_texture{ texture }
		, m_leftWidth{ leftWidth }
		, m_topHeight{ topHeight }
		, m_rightWidth{ rightWidth }
		, m_bottomHeight{ bottomHeight }
	{
		const int32 textureWidth = m_texture.width();
		const int32 textureHeight = m_texture.height();
		const int32 centerWidth = (textureWidth - (m_leftWidth + m_rightWidth));
		const int32 centerHeight = (textureHeight - (m_topHeight + m_bottomHeight));

		if (m_style.tileTopBottom)
		{
			m_repeatableTexture.top = RenderTexture{ Size{ centerWidth, m_topHeight } };
			Shader::Copy(m_texture(m_leftWidth, 0, centerWidth, m_topHeight), m_repeatableTexture.top);

			m_repeatableTexture.bottom = RenderTexture{ Size{ centerWidth, m_bottomHeight } };
			Shader::Copy(m_texture(m_leftWidth, (textureHeight - m_bottomHeight), centerWidth, m_bottomHeight), m_repeatableTexture.bottom);
		}

		if (m_style.tileLeftRight)
		{
			m_repeatableTexture.left = RenderTexture{ Size{ m_leftWidth, centerHeight } };
			Shader::Copy(m_texture(0, m_topHeight, m_leftWidth, centerHeight), m_repeatableTexture.left);

			m_repeatableTexture.right = RenderTexture{ Size{ m_rightWidth, centerHeight } };
			Shader::Copy(m_texture((textureWidth - m_rightWidth), m_topHeight, m_rightWidth, centerHeight), m_repeatableTexture.right);
		}

		if (m_style.tileCenter)
		{
			m_repeatableTexture.center = RenderTexture{ Size{ centerWidth, centerHeight } };
			Shader::Copy(m_texture(m_leftWidth, m_topHeight, centerWidth, centerHeight), m_repeatableTexture.center);
		}
	}

	void NinePatch::NinePatchDetail::draw(const RectF& rect, const double textureScale, const TextureFilter textureFilter, const ColorF& color) const
	{
		const double left = (m_leftWidth * textureScale);
		const double top = (m_topHeight * textureScale);
		const double right = (m_rightWidth * textureScale);
		const double bottom = (m_bottomHeight * textureScale);
		const double topBottomWidth = (rect.w - (left + right));
		const double leftRightHeight = (rect.h - (top + bottom));
		const bool showTopBottom = (0.0 <= topBottomWidth);
		const bool showLeftRight = (0.0 <= leftRightHeight);
		const int32 textureWidth = m_texture.width();
		const int32 textureHeight = m_texture.height();
		const int32 centerWidth = (textureWidth - (m_leftWidth + m_rightWidth));
		const int32 centerHeight = (textureHeight - (m_topHeight + m_bottomHeight));

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
				rect(m_texture(m_leftWidth, m_topHeight, centerWidth, centerHeight)).draw(color);
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
				topLeftRect(m_texture(0, 0, m_leftWidth, m_topHeight)).draw(color);

				// top
				if ((not m_style.tileTopBottom) && showTopBottom)
				{
					topRect(m_texture(m_leftWidth, 0, centerWidth, m_topHeight)).draw(color);
				}

				// top-right
				topRightRect(m_texture((textureWidth - m_rightWidth), 0, m_rightWidth, m_topHeight)).draw(color);

				// left
				if ((not m_style.tileLeftRight) && showLeftRight)
				{
					leftRect(m_texture(0, m_topHeight, m_leftWidth, centerHeight)).draw(color);
				}

				// center
				if ((not m_style.tileCenter) && showTopBottom && showLeftRight)
				{
					centerRect(m_texture(m_leftWidth, m_topHeight, centerWidth, centerHeight)).draw(color);
				}

				// right
				if ((not m_style.tileLeftRight) && showLeftRight)
				{
					rightRect(m_texture((textureWidth - m_rightWidth), m_topHeight, m_rightWidth, centerHeight)).draw(color);
				}

				// bottom-left
				bottomLeftRect(m_texture(0, (textureHeight - m_bottomHeight), m_leftWidth, m_bottomHeight)).draw(color);

				// bottom
				if ((not m_style.tileTopBottom) && showTopBottom)
				{
					bottomRect(m_texture(m_leftWidth, (textureHeight - m_bottomHeight), centerWidth, m_bottomHeight)).draw(color);
				}

				// bottom-right
				bottomRightRect(m_texture((textureWidth - m_rightWidth), (textureHeight - m_bottomHeight), m_rightWidth, m_bottomHeight)).draw(color);
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
		m_leftWidth = m_topHeight = m_rightWidth = m_bottomHeight = 0;
	}
}
