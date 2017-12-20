//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2017 Ryo Suzuki
//	Copyright (c) 2016-2017 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# include <Siv3D/Sprite.hpp>
# include <Siv3D/Circular.hpp>
# include <Siv3D/Texture.hpp>
# include <Siv3D/TexturedRoundRect.hpp>
# include "../Siv3DEngine.hpp"
# include "../Renderer2D/IRenderer2D.hpp"

namespace s3d
{
	namespace detail
	{
		static constexpr int32 CaluculateFanQuality(const double r) noexcept
		{
			return r <= 1.0 ? 3
				: r <= 6.0 ? 5
				: r <= 12.0 ? 8
				: static_cast<int32>(std::min(64.0, r * 0.2 + 6));
		}
	}

	const RoundRect& TexturedRoundRect::draw(const ColorF& diffuse) const
	{
		const double rr = std::min({ rect.w * 0.5, rect.h * 0.5, rect.r });
		const float scale = Siv3DEngine::GetRenderer2D()->getMaxScaling();
		const int32 quality = detail::CaluculateFanQuality(rr * scale);
		const double radDelta = Math::HalfPi / (quality - 1);

		Array<Float2> fanPositions(quality);

		for (int32 i = 0; i < quality; ++i)
		{
			fanPositions[i] = Circular(rr, radDelta * i).toFloat2();
		}

		const bool uniteV = (rect.h * 0.5 == rr);
		const bool uniteH = (rect.w * 0.5 == rr);
		const std::array<Float2, 4> centers =
		{ {
			{ rect.x + rect.w - rr, rect.y + rr },
			{ rect.x + rect.w - rr, rect.y + rect.h - rr },
			{ rect.x + rr, rect.y + rect.h - rr },
			{ rect.x + rr, rect.y + rr },
			} };

		const uint32 vertexSize = (quality - uniteV + quality - uniteH) * 2;
		const uint32 indexSize = (vertexSize - 2) * 3;

		Sprite sprite(vertexSize, indexSize);
		{
			Vertex2D* pVertex = sprite.vertices.data();

			for (int32 i = 0; i < quality - uniteV; ++i)
			{
				pVertex->pos = centers[0] + fanPositions[i];
				++pVertex;
			}

			for (int32 i = 0; i < quality - uniteH; ++i)
			{
				pVertex->pos = centers[1] + Float2(fanPositions[quality - i - 1].x, -fanPositions[quality - i - 1].y);
				++pVertex;
			}

			for (int32 i = 0; i < quality - uniteV; ++i)
			{
				pVertex->pos = centers[2] + Float2(-fanPositions[i].x, -fanPositions[i].y);
				++pVertex;
			}

			for (int32 i = 0; i < quality - uniteH; ++i)
			{
				pVertex->pos = centers[3] + Float2(-fanPositions[quality - i - 1].x, fanPositions[quality - i - 1].y);
				++pVertex;
			}
		}

		{
			const float uOffst = uvRect.left;
			const float vOffst = uvRect.top;
			const float left = static_cast<float>(rect.x);
			const float ws = (uvRect.right - uvRect.left) / static_cast<float>(rect.w);
			const float top = static_cast<float>(rect.y);
			const float hs = (uvRect.bottom - uvRect.top) / static_cast<float>(rect.h);

			Vertex2D* pVertex = sprite.vertices.data();

			for (size_t i = 0; i < vertexSize; ++i)
			{
				const float u = uOffst + (pVertex->pos.x - left) * ws;
				const float v = vOffst + (pVertex->pos.y - top) * hs;
				(pVertex++)->tex.set(u, v);
			}
		}

		{
			const Float4 colorF = diffuse.toFloat4();

			Vertex2D* pVertex = sprite.vertices.data();

			for (size_t i = 0; i < vertexSize; ++i)
			{
				(pVertex++)->color = colorF;
			}
		}

		{
			uint32* pIndex = sprite.indices.data();

			for (uint32 i = 0; i < (vertexSize - 2); ++i)
			{
				pIndex[i * 3 + 1] = i + 1;
				pIndex[i * 3 + 2] = (i + 2 < vertexSize) ? (i + 2) : 0;
			}
		}

		sprite.draw(texture);

		return rect;
	}

	RoundRect TexturedRoundRect::drawAt(const double x, const double y, const ColorF& diffuse) const
	{
		return TexturedRoundRect(texture, uvRect, RoundRect(Arg::center(x, y), rect.w, rect.h, rect.r)).draw(diffuse);
	}
}
