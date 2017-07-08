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

# include <Siv3D/RoundRect.hpp>
# include <Siv3D/Mouse.hpp>
# include <Siv3D/Cursor.hpp>
# include <Siv3D/Sprite.hpp>
# include <Siv3D/Circular.hpp>
# include <Siv3D/TexturedRoundRect.hpp>
# include <Siv3D/TextureRegion.hpp>
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

		static Array<Vec2> GetOuterVertices(const RoundRect& rect, const double offset)
		{
			const double rr = std::min({ rect.w * 0.5, rect.h * 0.5, rect.r }) + offset;
			const float scale = Siv3DEngine::GetRenderer2D()->getMaxScaling();
			const int32 quality = detail::CaluculateFanQuality(rr * scale);
			const double radDelta = Math::HalfPi / (quality - 1);

			Array<Vec2> fanPositions(quality);

			for (int32 i = 0; i < quality; ++i)
			{
				fanPositions[i] = Circular(rr, radDelta * i);
			}

			const bool uniteV = (rect.h * 0.5 == rr);
			const bool uniteH = (rect.w * 0.5 == rr);
			const std::array<Vec2, 4> centers =
			{{
				{ rect.x + rect.w - rr + offset, rect.y + rr - offset },
				{ rect.x + rect.w - rr + offset, rect.y + rect.h - rr + offset },
				{ rect.x + rr - offset, rect.y + rect.h - rr + offset },
				{ rect.x + rr - offset, rect.y + rr - offset },
			}};

			const uint32 vertexSize = (quality - uniteV + quality - uniteH) * 2;
			
			Array<Vec2> vertices(vertexSize);
			{
				Vec2* pVertex = vertices.data();

				for (int32 i = 0; i < quality - uniteV; ++i)
				{
					*pVertex++ = centers[0] + fanPositions[i];
				}

				for (int32 i = 0; i < quality - uniteH; ++i)
				{
					*pVertex++ = centers[1] + Float2(fanPositions[quality - i - 1].x, -fanPositions[quality - i - 1].y);
				}

				for (int32 i = 0; i < quality - uniteV; ++i)
				{
					*pVertex++ = centers[2] + Float2(-fanPositions[i].x, -fanPositions[i].y);
				}

				for (int32 i = 0; i < quality - uniteH; ++i)
				{
					*pVertex++ = centers[3] + Float2(-fanPositions[quality - i - 1].x, fanPositions[quality - i - 1].y);
				}
			}

			return vertices;
		}
	}

	bool RoundRect::leftClicked() const
	{
		return MouseL.down() && mouseOver();
	}

	bool RoundRect::leftPressed() const
	{
		return MouseL.pressed() && mouseOver();
	}

	bool RoundRect::leftReleased() const
	{
		return MouseL.up() && mouseOver();
	}

	bool RoundRect::rightClicked() const
	{
		return MouseR.down() && mouseOver();
	}

	bool RoundRect::rightPressed() const
	{
		return MouseR.pressed() && mouseOver();
	}

	bool RoundRect::rightReleased() const
	{
		return MouseR.up() && mouseOver();
	}

	bool RoundRect::mouseOver() const
	{
		return Geometry2D::Intersect(Cursor::PosF(), *this);
	}


	const RoundRect& RoundRect::draw(const ColorF& color) const
	{
		const double rr = std::min({ rect.w * 0.5, rect.h * 0.5, r });
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
		{{
			{ rect.x + rect.w - rr, rect.y + rr },
			{ rect.x + rect.w - rr, rect.y + rect.h - rr },
			{ rect.x + rr, rect.y + rect.h - rr },
			{ rect.x + rr, rect.y + rr },
		}};

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
			const Float4 colorF = color.toFloat4();

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

		sprite.draw();

		return *this;
	}

	const RoundRect& RoundRect::drawFrame(double innerThickness, double outerThickness, const ColorF& color) const
	{
		if (rect.w == 0.0 && rect.h == 0.0)
		{
			return *this;
		}

		const Array<Vec2> vertices = detail::GetOuterVertices(*this, (outerThickness - innerThickness) * 0.5);

		Siv3DEngine::GetRenderer2D()->addLineString(
			LineStyle::Default,
			vertices.data(),
			static_cast<uint32>(vertices.size()),
			none,
			static_cast<float>(innerThickness + outerThickness),
			false,
			color.toFloat4(),
			true
		);

		return *this;
	}

	const RoundRect& RoundRect::drawShadow(const Vec2& offset, double blurRadius, double spread, const ColorF& color) const
	{
		if (blurRadius < 0.0)
		{
			return *this;
		}

		if (blurRadius * 0.5 > (std::min(w * 0.5, h * 0.5) + spread))
		{
			blurRadius = (std::min(w * 0.5, h * 0.5) + spread) * 2.0;
		}

		const double innnerOffset = blurRadius * 0.5 > r ? blurRadius * 0.5 : r;
		const double over = std::max(blurRadius * 0.5 - r, 0.0);
		const RectF baseRect = rect.stretched(spread - innnerOffset).movedBy(offset);
		const Float4 colF = color.toFloat4();
		const double pR = std::min({ w * 0.5, h * 0.5, r });
		const double nearR = std::max(pR - blurRadius * 0.5, 0.0);
		const double farR = pR + blurRadius * 0.5 + over;
		const float scale = Siv3DEngine::GetRenderer2D()->getMaxScaling();
		const uint32 quality = static_cast<uint32>(detail::CaluculateFanQuality(farR * scale));

		Array<Vec2> fanDirections(quality);

		const double radDelta = Math::HalfPi / (quality - 1);

		for (uint32 i = 0; i < quality; ++i)
		{
			fanDirections[i] = Circular(1.0, radDelta * i);
		}

		const std::array<Vec2, 4> centers =
		{{
			{ baseRect.x + baseRect.w, baseRect.y },
			{ baseRect.x + baseRect.w, baseRect.y + baseRect.h },
			{ baseRect.x, baseRect.y + baseRect.h },
			{ baseRect.x, baseRect.y },
		}};

		Array<Vec2> verticesInner;
		{
			verticesInner.reserve(quality * 4);

			for (uint32 i = 0; i < quality; ++i)
			{
				verticesInner.emplace_back(centers[0] + nearR * fanDirections[i]);
			}

			for (uint32 i = 0; i < quality; ++i)
			{
				verticesInner.emplace_back(centers[1] + nearR * Vec2(fanDirections[quality - i - 1].x, -fanDirections[quality - i - 1].y));
			}

			for (uint32 i = 0; i < quality; ++i)
			{
				verticesInner.emplace_back(centers[2] + nearR * Vec2(-fanDirections[i].x, -fanDirections[i].y));
			}

			for (uint32 i = 0; i < quality; ++i)
			{
				verticesInner.emplace_back(centers[3] + nearR * Vec2(-fanDirections[quality - i - 1].x, fanDirections[quality - i - 1].y));
			}
		}

		Array<Vec2> verticesOuter;
		{
			verticesOuter.reserve(quality * 4);

			for (uint32 i = 0; i < quality; ++i)
			{
				verticesOuter.emplace_back(centers[0] + farR * fanDirections[i]);
			}

			for (uint32 i = 0; i < quality; ++i)
			{
				verticesOuter.emplace_back(centers[1] + farR * Vec2(fanDirections[quality - i - 1].x, -fanDirections[quality - i - 1].y));
			}

			for (uint32 i = 0; i < quality; ++i)
			{
				verticesOuter.emplace_back(centers[2] + farR * Vec2(-fanDirections[i].x, -fanDirections[i].y));
			}

			for (uint32 i = 0; i < quality; ++i)
			{
				verticesOuter.emplace_back(centers[3] + farR * Vec2(-fanDirections[quality - i - 1].x, fanDirections[quality - i - 1].y));
			}
		}

		Sprite sprite(static_cast<uint32>(4 + verticesInner.size() + verticesOuter.size()), 6 + ((quality + 1) * 3 * 4) + ((quality) * 4 * 6));

		sprite.vertices[0].set(centers[0], Float2(0.5f, 0.5f), colF);
		sprite.vertices[1].set(centers[1], Float2(0.5f, 0.5f), colF);
		sprite.vertices[2].set(centers[2], Float2(0.5f, 0.5f), colF);
		sprite.vertices[3].set(centers[3], Float2(0.5f, 0.5f), colF);

		for (size_t i = 0; i < verticesInner.size(); ++i)
		{
			sprite.vertices[4 + i].set(verticesInner[i], Float2(0.5f, 0.5f), colF);
		}

		for (size_t i = 0; i < verticesOuter.size(); ++i)
		{
			sprite.vertices[4 + verticesInner.size() + i].set(verticesOuter[i], Float2(0.5f, 0.0f), colF);
		}

		sprite.indices[0] = 3;
		sprite.indices[1] = 0;
		sprite.indices[2] = 2;

		sprite.indices[3] = 2;
		sprite.indices[4] = 0;
		sprite.indices[5] = 1;

		for (uint32 i = 0; i < 4; ++i)
		{
			for (uint32 k = 0; k < quality - 1; ++k)
			{
				sprite.indices[6 + k * 3 + i * (quality + 1) * 3 + 0] = i;
				sprite.indices[6 + k * 3 + i * (quality + 1) * 3 + 1] = 4 + i * quality + k;
				sprite.indices[6 + k * 3 + i * (quality + 1) * 3 + 2] = 4 + i * quality + k + 1;
			}

			sprite.indices[6 + (i + 1) * (quality + 1) * 3 - 6] = i;
			sprite.indices[6 + (i + 1) * (quality + 1) * 3 - 5] = (i + 1) * quality - 1 + 4;
			sprite.indices[6 + (i + 1) * (quality + 1) * 3 - 4] = ((i + 1) * quality) % (4 * quality) + 4;

			sprite.indices[6 + (i + 1) * (quality + 1) * 3 - 3] = i;
			sprite.indices[6 + (i + 1) * (quality + 1) * 3 - 2] = ((i + 1) * quality) % (4 * quality) + 4;
			sprite.indices[6 + (i + 1) * (quality + 1) * 3 - 1] = (i + 1) % 4;
		}

		const uint32 i1 = 6 + 4 * (quality + 1) * 3;
		const uint32 v1 = static_cast<uint32>(verticesInner.size());

		for (uint32 i = 0; i < 4; ++i)
		{
			for (uint32 k = 0; k < quality; ++k)
			{
				const uint32 localV1 = i * quality + k;
				const uint32 localV2 = (localV1 + 1) % (quality * 4);

				sprite.indices[i1 + (i * quality * 6) + k * 6 + 0] = v1 + localV1 + 4;
				sprite.indices[i1 + (i * quality * 6) + k * 6 + 1] = v1 + localV2 + 4;
				sprite.indices[i1 + (i * quality * 6) + k * 6 + 2] = localV1 + 4;
				sprite.indices[i1 + (i * quality * 6) + k * 6 + 3] = localV1 + 4;
				sprite.indices[i1 + (i * quality * 6) + k * 6 + 4] = v1 + localV2 + 4;
				sprite.indices[i1 + (i * quality * 6) + k * 6 + 5] = localV2 + 4;
			}
		}

		sprite.draw(Siv3DEngine::GetRenderer2D()->getBoxShadowTexture());

		return *this;
	}

	TexturedRoundRect RoundRect::operator ()(const Texture& texture) const
	{
		return TexturedRoundRect(texture,
			0.0f, 0.0f, 1.0f, 1.0f,
			*this);
	}

	TexturedRoundRect RoundRect::operator ()(const TextureRegion& textureRegion) const
	{
		return TexturedRoundRect(textureRegion.texture,
			textureRegion.uvRect,
			*this);
	}

	void Formatter(FormatData& formatData, const RoundRect& value)
	{
		formatData.string.push_back(L'(');
		formatData.string.append(ToString(value.x, formatData.decimalPlace.value));
		formatData.string.push_back(L',');
		formatData.string.append(ToString(value.y, formatData.decimalPlace.value));
		formatData.string.push_back(L',');
		formatData.string.append(ToString(value.w, formatData.decimalPlace.value));
		formatData.string.push_back(L',');
		formatData.string.append(ToString(value.h, formatData.decimalPlace.value));
		formatData.string.push_back(L',');
		formatData.string.append(ToString(value.r, formatData.decimalPlace.value));
		formatData.string.push_back(L')');
	}
}
