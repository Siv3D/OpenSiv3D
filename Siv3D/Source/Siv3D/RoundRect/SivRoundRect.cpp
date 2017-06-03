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
			const int32 quality = detail::CaluculateFanQuality(rr);
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

	const RoundRect& RoundRect::draw(const ColorF& color) const
	{
		const double rr = std::min({ rect.w * 0.5, rect.h * 0.5, r });
		const int32 quality = detail::CaluculateFanQuality(rr);
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
