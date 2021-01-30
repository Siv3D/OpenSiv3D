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
		const float rr = static_cast<float>(Min({ rect.w * 0.5, rect.h * 0.5, rect.r }));
		const float scale = SIV3D_ENGINE(Renderer2D)->getMaxScaling();
		const int32 quality = detail::CaluculateFanQuality(rr * scale);

		Array<Float2> fanPositions(quality);
		{
			const float radDelta = (Math::HalfPiF / (quality - 1));

			for (int32 i = 0; i < quality; ++i)
			{
				const float rad = (radDelta * i);
				const auto [s, c] = FastMath::SinCos(rad);
				fanPositions[i].set(s * rr, -c * rr);
			}
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
		const uint32 indexSize = (vertexSize - 2);

		Array<Vertex2D> vertices(vertexSize);
		{
			Vertex2D* pVertex = vertices.data();

			for (int32 i = 0; i < quality - uniteV; ++i)
			{
				pVertex->pos = centers[0] + fanPositions[i];
				++pVertex;
			}

			for (int32 i = 0; i < quality - uniteH; ++i)
			{
				pVertex->pos = centers[1] + Float2{ fanPositions[quality - i - 1].x, -fanPositions[quality - i - 1].y };
				++pVertex;
			}

			for (int32 i = 0; i < quality - uniteV; ++i)
			{
				pVertex->pos = centers[2] - fanPositions[i];
				++pVertex;
			}

			for (int32 i = 0; i < quality - uniteH; ++i)
			{
				pVertex->pos = centers[3] + Float2{ -fanPositions[quality - i - 1].x, fanPositions[quality - i - 1].y };
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

			Vertex2D* pVertex = vertices.data();

			for (size_t i = 0; i < vertexSize; ++i)
			{
				const float u = uOffst + (pVertex->pos.x - left) * ws;
				const float v = vOffst + (pVertex->pos.y - top) * hs;
				(pVertex++)->tex.set(u, v);
			}
		}

		{
			const Float4 colorF = diffuse.toFloat4();

			Vertex2D* pVertex = vertices.data();

			for (size_t i = 0; i < vertexSize; ++i)
			{
				(pVertex++)->color = colorF;
			}
		}

		Array<TriangleIndex> indices(indexSize);
		{
			TriangleIndex* pIndex = indices.data();

			for (Vertex2D::IndexType i = 0; i < (vertexSize - 2); ++i)
			{
				pIndex->i0 = 0;
				pIndex->i1 = (i + 1u);
				pIndex->i2 = ((i + 2u < vertexSize) ? (i + 2) : 0);
				++pIndex;
			}
		}

		SIV3D_ENGINE(Renderer2D)->addTexturedVertices(texture, vertices.data(), vertices.size(), indices.data(), indices.size());

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
