//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2019 Ryo Suzuki
//	Copyright (c) 2016-2019 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# include <Siv3D/RoundRect.hpp>
# include <Siv3D/Mouse.hpp>
# include <Siv3D/Cursor.hpp>
# include <Siv3D/Polygon.hpp>
# include <Siv3D/LineString.hpp>
# include <Siv3D/FloatRect.hpp>
# include <Siv3D/Sprite.hpp>
# include <Siv3D/Circular.hpp>
# include <Siv3D/TexturedRoundRect.hpp>
# include <Siv3D/TextureRegion.hpp>
# include <Siv3DEngine.hpp>
# include <Renderer2D/IRenderer2D.hpp>

namespace s3d
{
	namespace detail
	{		
		static constexpr uint16 CaluculateFanQuality(const double r) noexcept
		{
			return r <= 1.0 ? 3
				: r <= 6.0 ? 5
				: r <= 12.0 ? 8
				: static_cast<uint16>(std::min(64.0, r * 0.2 + 6));
		}
		 
		static Array<Vec2> GetOuterVertices(const RoundRect& rect, const double offset)
		{
			const double rr = std::min({ rect.w * 0.5, rect.h * 0.5, std::max(0.0, rect.r) }) + offset;
			const float scale = Siv3DEngine::Get<ISiv3DRenderer2D>()->getMaxScaling();
			const int32 quality = detail::CaluculateFanQuality(rr * scale);
			const double radDelta = Math::Constants::HalfPi / (quality - 1);

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

	const RoundRect& RoundRect::paint(Image& dst, const Color& color) const
	{
		asPolygon().paint(dst, color);

		return *this;
	}

	const RoundRect& RoundRect::overwrite(Image& dst, const Color& color, const bool antialiased) const
	{
		asPolygon().overwrite(dst, color, antialiased);

		return *this;
	}

	const RoundRect& RoundRect::paintFrame(Image& dst, const int32 innerThickness, const int32 outerThickness, const Color& color) const
	{
		LineString(detail::GetOuterVertices(*this, (outerThickness - innerThickness) * 0.5)).paintClosed(dst, (outerThickness + innerThickness), color);

		return *this;
	}

	const RoundRect& RoundRect::overwriteFrame(Image& dst, const int32 innerThickness, const int32 outerThickness, const Color& color, const bool antialiased) const
	{
		LineString(detail::GetOuterVertices(*this, (outerThickness - innerThickness) * 0.5)).overwriteClosed(dst, (outerThickness + innerThickness), color, antialiased);

		return *this;
	}

	const RoundRect& RoundRect::draw(const ColorF& color) const
	{
		Siv3DEngine::Get<ISiv3DRenderer2D>()->addRoundRect(
			FloatRect(x, y, x + w, y + h),
			static_cast<float>(w),
			static_cast<float>(h),
			static_cast<float>(r),
			color.toFloat4()
		);

		return *this;
	}

	const RoundRect& RoundRect::drawFrame(double innerThickness, double outerThickness, const ColorF& color) const
	{
		if (rect.w == 0.0 && rect.h == 0.0)
		{
			return *this;
		}

		const Array<Vec2> vertices = detail::GetOuterVertices(*this, (outerThickness - innerThickness) * 0.5);

		Siv3DEngine::Get<ISiv3DRenderer2D>()->addLineString(
			LineStyle::Default,
			vertices.data(),
			static_cast<uint16>(vertices.size()),
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
		const float scale = Siv3DEngine::Get<ISiv3DRenderer2D>()->getMaxScaling();
		const uint16 quality = static_cast<uint16>(detail::CaluculateFanQuality(farR * scale));

		Array<Vec2> fanDirections(quality);

		const double radDelta = Math::Constants::HalfPi / (quality - 1);

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

		for (uint16 i = 0; i < 4; ++i)
		{
			for (uint16 k = 0; k < quality - 1; ++k)
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
		const uint16 v1 = static_cast<uint16>(verticesInner.size());

		for (uint16 i = 0; i < 4; ++i)
		{
			for (uint16 k = 0; k < quality; ++k)
			{
				const uint16 localV1 = i * quality + k;
				const uint16 localV2 = (localV1 + 1) % (quality * 4);

				sprite.indices[i1 + (i * quality * 6) + k * 6 + 0] = v1 + localV1 + 4;
				sprite.indices[i1 + (i * quality * 6) + k * 6 + 1] = v1 + localV2 + 4;
				sprite.indices[i1 + (i * quality * 6) + k * 6 + 2] = localV1 + 4;
				sprite.indices[i1 + (i * quality * 6) + k * 6 + 3] = localV1 + 4;
				sprite.indices[i1 + (i * quality * 6) + k * 6 + 4] = v1 + localV2 + 4;
				sprite.indices[i1 + (i * quality * 6) + k * 6 + 5] = localV2 + 4;
			}
		}

		sprite.draw(Siv3DEngine::Get<ISiv3DRenderer2D>()->getBoxShadowTexture());

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

	Polygon RoundRect::asPolygon() const
	{
		const double rr = std::min({ rect.w * 0.5, rect.h * 0.5, r });

		if (rr <= 0.0)
		{
			return Polygon();
		}

		const Array<Vec2> vertices = detail::GetOuterVertices(*this, 0.0);

		Array<uint16> indices((vertices.size() - 2) * 3);

		for (uint16 i = 0; i < (vertices.size() - 2); ++i)
		{
			indices[i * 3 + 1] = i;
			indices[i * 3 + 2] = i + 1;
		}

		return Polygon(vertices, indices, rect);
	}

	void Formatter(FormatData& formatData, const RoundRect& value)
	{
		formatData.string.push_back(U'(');
		formatData.string.append(ToString(value.x, formatData.decimalPlaces.value));
		formatData.string.append(U", "_sv);
		formatData.string.append(ToString(value.y, formatData.decimalPlaces.value));
		formatData.string.append(U", "_sv);
		formatData.string.append(ToString(value.w, formatData.decimalPlaces.value));
		formatData.string.append(U", "_sv);
		formatData.string.append(ToString(value.h, formatData.decimalPlaces.value));
		formatData.string.append(U", "_sv);
		formatData.string.append(ToString(value.r, formatData.decimalPlaces.value));
		formatData.string.push_back(U')');
	}
}
