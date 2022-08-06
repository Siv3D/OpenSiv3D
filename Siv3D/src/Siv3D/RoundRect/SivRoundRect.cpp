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

# include <Siv3D/2DShapes.hpp>
# include <Siv3D/Circular.hpp>
# include <Siv3D/LineString.hpp>
# include <Siv3D/Polygon.hpp>
# include <Siv3D/FormatFloat.hpp>
# include <Siv3D/FloatRect.hpp>
# include <Siv3D/Mouse.hpp>
# include <Siv3D/Cursor.hpp>
# include <Siv3D/Geometry2D.hpp>
# include <Siv3D/TextureRegion.hpp>
# include <Siv3D/TexturedRoundRect.hpp>
# include <Siv3D/Renderer2D/IRenderer2D.hpp>
# include <Siv3D/Common/Siv3DEngine.hpp>

namespace s3d
{
	namespace detail
	{
		[[nodiscard]]
		inline constexpr Vertex2D::IndexType CaluculateFanQuality(const double r) noexcept
		{
			return r <= 1.0 ? 3
				: r <= 6.0 ? 5
				: r <= 12.0 ? 8
				: static_cast<Vertex2D::IndexType>(Min(64.0, r * 0.2 + 6));
		}

		[[nodiscard]]
		static Array<Vec2> GetOuterVertices(const RoundRect& rect, const double offset, const Optional<float>& scalingFactor)
		{
			const double rr = Min({ (rect.w * 0.5), (rect.h * 0.5), Max(0.0, rect.r) }) + offset;
			const float scale = scalingFactor ? *scalingFactor : SIV3D_ENGINE(Renderer2D)->getMaxScaling();
			const int32 quality = detail::CaluculateFanQuality(rr * scale);
			const double radDelta = (Math::HalfPi / (quality - 1));

			Array<Vec2> fanPositions(quality);

			for (int32 i = 0; i < quality; ++i)
			{
				fanPositions[i] = Circular{ rr, (radDelta * i) }.fastToVec2();
			}

			const bool uniteV = (rect.h * 0.5 == rr);
			const bool uniteH = (rect.w * 0.5 == rr);
			const std::array<Vec2, 4> centers =
			{ {
				{ rect.x + rect.w - rr + offset, rect.y + rr - offset },
				{ rect.x + rect.w - rr + offset, rect.y + rect.h - rr + offset },
				{ rect.x + rr - offset, rect.y + rect.h - rr + offset },
				{ rect.x + rr - offset, rect.y + rr - offset },
			} };

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
					*pVertex++ = centers[1] + Float2{ fanPositions[quality - i - 1].x, -fanPositions[quality - i - 1].y };
				}

				for (int32 i = 0; i < quality - uniteV; ++i)
				{
					*pVertex++ = centers[2] - fanPositions[i];
				}

				for (int32 i = 0; i < quality - uniteH; ++i)
				{
					*pVertex++ = centers[3] + Float2{ -fanPositions[quality - i - 1].x, fanPositions[quality - i - 1].y };
				}
			}

			return vertices;
		}
	}

	Array<Vec2> RoundRect::outerVertices(const uint32 quality) const
	{
		const double rr = Min({ (rect.w * 0.5), (rect.h * 0.5), r });

		if (rr <= 0.0)
		{
			return{};
		}

		const uint32 n = Max(quality, 3u);
		return detail::GetOuterVertices(*this, 0.0, (n / 24.0f));
	}

	Polygon RoundRect::asPolygon(const uint32 quality) const
	{
		const double rr = Min({ (rect.w * 0.5), (rect.h * 0.5), r });

		if (rr <= 0.0)
		{
			return{};
		}

		const uint32 n = Max(quality, 3u);
		const Array<Vec2> vertices = detail::GetOuterVertices(*this, 0.0, (n / 24.0f));

		Array<TriangleIndex> indices(vertices.size() - 2);
		TriangleIndex* pDst = indices.data();

		for (Vertex2D::IndexType i = 0; i < indices.size(); ++i)
		{
			pDst->i0 = 0;
			pDst->i1 = (i + 1);
			pDst->i2 = (i + 2);
			++pDst;
		}

		return Polygon{ vertices, indices, rect, SkipValidation::Yes };
	}

	bool RoundRect::leftClicked() const noexcept
	{
		return (MouseL.down() && mouseOver());
	}

	bool RoundRect::leftPressed() const noexcept
	{
		return (MouseL.pressed() && mouseOver());
	}

	bool RoundRect::leftReleased() const noexcept
	{
		return (MouseL.up() && mouseOver());
	}

	bool RoundRect::rightClicked() const noexcept
	{
		return (MouseR.down() && mouseOver());
	}

	bool RoundRect::rightPressed() const noexcept
	{
		return (MouseR.pressed() && mouseOver());
	}

	bool RoundRect::rightReleased() const noexcept
	{
		return (MouseR.up() && mouseOver());
	}

	bool RoundRect::mouseOver() const noexcept
	{
		return Geometry2D::Intersect(Cursor::PosF(), *this);
	}

	const RoundRect& RoundRect::paint(Image& dst, const Color& color) const
	{
		asPolygon().paint(dst, color);

		return *this;
	}

	const RoundRect& RoundRect::overwrite(Image& dst, const Color& color, const Antialiased antialiased) const
	{
		asPolygon().overwrite(dst, color, antialiased);

		return *this;
	}

	const RoundRect& RoundRect::paintFrame(Image& dst, const int32 innerThickness, const int32 outerThickness, const Color& color) const
	{
		LineString(detail::GetOuterVertices(*this, (outerThickness - innerThickness) * 0.5, none)).paintClosed(dst, (outerThickness + innerThickness), color);

		return *this;
	}

	const RoundRect& RoundRect::overwriteFrame(Image& dst, const int32 innerThickness, const int32 outerThickness, const Color& color, const Antialiased antialiased) const
	{
		LineString(detail::GetOuterVertices(*this, (outerThickness - innerThickness) * 0.5, none)).overwriteClosed(dst, (outerThickness + innerThickness), color, antialiased);

		return *this;
	}

	const RoundRect& RoundRect::draw(const ColorF& color) const
	{
		SIV3D_ENGINE(Renderer2D)->addRoundRect(
			FloatRect{ x, y, (x + w), (y + h) },
			static_cast<float>(w),
			static_cast<float>(h),
			static_cast<float>(r),
			color.toFloat4()
		);

		return *this;
	}

	const RoundRect& RoundRect::drawFrame(const double thickness, const ColorF& color) const
	{
		return drawFrame(thickness * 0.5, thickness * 0.5, color);
	}

	const RoundRect& RoundRect::drawFrame(const double innerThickness, const double outerThickness, const ColorF& color) const
	{
		if ((rect.w <= 0.0) || (rect.h <= 0.0)
			|| (innerThickness < 0.0) || (outerThickness < 0.0)
			|| ((innerThickness == 0.0) && (outerThickness == 0.0)))
		{
			return *this;
		}

		if (r <= 0.0)
		{
			rect.drawFrame(innerThickness, outerThickness, color);
			return *this;
		}

		const RectF outerRect = rect.stretched(outerThickness);
		const RoundRect outerRoundRect{ outerRect, Min((r + outerThickness), (Min(outerRect.w, outerRect.h) * 0.5)) };
		const RectF innerRect = rect.stretched(-innerThickness);

		if ((innerRect.w <= 0.0) || (innerRect.h <= 0.0))
		{
			outerRoundRect.draw(color);
			return *this;
		}

		const RoundRect innerRoundRect{ innerRect, Clamp((r - innerThickness), 0.0, (Min(innerRect.w, innerRect.h) * 0.5)) };

		SIV3D_ENGINE(Renderer2D)->addRoundRectFrame(
			outerRoundRect,
			innerRoundRect,
			color.toFloat4()
		);

		return *this;
	}

	const RoundRect& RoundRect::drawShadow(const Vec2& offset, double blurRadius, const double spread, const ColorF& color) const
	{
		if (blurRadius < 0.0)
		{
			return *this;
		}

		if (const double mr = (Min(w * 0.5, h * 0.5) + spread);
			mr < (blurRadius * 0.5))
		{
			blurRadius = (mr * 2.0);
		}

		const Float4 colF			= color.toFloat4();
		const double innnerOffset	= (r < blurRadius * 0.5) ? (blurRadius * 0.5) : r;
		const double over			= Max(blurRadius * 0.5 - r, 0.0);
		const RectF baseRect		= rect.stretched(spread - innnerOffset).movedBy(offset);
		const double pR				= Min({ w * 0.5, h * 0.5, r });
		const double nearR			= Max(pR - blurRadius * 0.5, 0.0);
		const double farR			= (pR + blurRadius * 0.5 + over);
		const float scale			= SIV3D_ENGINE(Renderer2D)->getMaxScaling();
		const Vertex2D::IndexType quality = static_cast<uint16>(detail::CaluculateFanQuality(farR * scale));

		Array<Vec2> fanDirections(quality);
		{
			const double radDelta = (Math::HalfPi / (quality - 1));

			for (int32 i = 0; i < quality; ++i)
			{
				fanDirections[i] = Circular{ 1.0, (radDelta * i) }.fastToVec2();
			}
		}

		const std::array<Vec2, 4> centers =
		{ {
			{ baseRect.x + baseRect.w, baseRect.y },
			{ baseRect.x + baseRect.w, baseRect.y + baseRect.h },
			{ baseRect.x, baseRect.y + baseRect.h },
			{ baseRect.x, baseRect.y },
		} };

		Array<Vec2> verticesInner(quality * 4);
		{
			Vec2* pDst = verticesInner.data();

			for (uint32 i = 0; i < quality; ++i)
			{
				*pDst++ = (centers[0] + nearR * fanDirections[i]);
			}

			for (uint32 i = 0; i < quality; ++i)
			{
				*pDst++ = (centers[1] + nearR * Vec2{ fanDirections[quality - i - 1].x, -fanDirections[quality - i - 1].y });
			}

			for (uint32 i = 0; i < quality; ++i)
			{
				*pDst++ = (centers[2] + nearR * -fanDirections[i]);
			}

			for (uint32 i = 0; i < quality; ++i)
			{
				*pDst++ = (centers[3] + nearR * Vec2{ -fanDirections[quality - i - 1].x, fanDirections[quality - i - 1].y });
			}
		}

		Array<Vec2> verticesOuter(quality * 4);
		{
			Vec2* pDst = verticesOuter.data();

			for (uint32 i = 0; i < quality; ++i)
			{
				*pDst++ = (centers[0] + farR * fanDirections[i]);
			}

			for (uint32 i = 0; i < quality; ++i)
			{
				*pDst++ = (centers[1] + farR * Vec2{ fanDirections[quality - i - 1].x, -fanDirections[quality - i - 1].y });
			}

			for (uint32 i = 0; i < quality; ++i)
			{
				*pDst++ = (centers[2] + farR * -fanDirections[i]);
			}

			for (uint32 i = 0; i < quality; ++i)
			{
				*pDst++ = (centers[3] + farR * Vec2{ -fanDirections[quality - i - 1].x, fanDirections[quality - i - 1].y });
			}
		}

		Array<Vertex2D> vertices(4 + verticesInner.size() + verticesOuter.size());
		{
			Vertex2D* pDst = vertices.data();

			pDst->set(centers[0], Float2{ 0.5f, 0.5f }, colF);
			++pDst;
			pDst->set(centers[1], Float2{ 0.5f, 0.5f }, colF);
			++pDst;
			pDst->set(centers[2], Float2{ 0.5f, 0.5f }, colF);
			++pDst;
			pDst->set(centers[3], Float2{ 0.5f, 0.5f }, colF);
			++pDst;

			for (size_t i = 0; i < verticesInner.size(); ++i)
			{
				pDst->set(verticesInner[i], Float2{ 0.5f, 0.5f }, colF);
				++pDst;
			}

			for (size_t i = 0; i < verticesOuter.size(); ++i)
			{
				pDst->set(verticesOuter[i], Float2{ 0.5f, 0.0f }, colF);
				++pDst;
			}
		}

		Array<TriangleIndex> indices(6 + ((quality + 1) * 3 * 4) + ((quality) * 4 * 6));
		{
			TriangleIndex* pDst = indices.data();

			pDst->i0 = 3;
			pDst->i1 = 0;
			pDst->i2 = 2;
			++pDst;

			pDst->i0 = 2;
			pDst->i1 = 0;
			pDst->i2 = 1;
			++pDst;

			for (uint16 i = 0; i < 4; ++i)
			{
				for (uint16 k = 0; k < quality - 1; ++k)
				{
					pDst->i0 = i;
					pDst->i1 = (4 + i * quality + k);
					pDst->i2 = (4 + i * quality + k + 1);
					++pDst;
				}

				const Vertex2D::IndexType t0 = i;
				const Vertex2D::IndexType t1 = (i + 1) * quality - 1 + 4;
				const Vertex2D::IndexType t2 = ((i + 1) * quality) % (4 * quality) + 4;
				const Vertex2D::IndexType t3 = (i + 1) % 4;

				pDst->i0 = t0;
				pDst->i1 = t1;
				pDst->i2 = t2;
				++pDst;

				pDst->i0 = t0;
				pDst->i1 = t2;
				pDst->i2 = t3;
				++pDst;
			}

			const uint16 v1 = static_cast<uint16>(verticesInner.size());

			for (uint16 i = 0; i < 4; ++i)
			{
				for (uint16 k = 0; k < quality; ++k)
				{
					const uint16 localV1 = i * quality + k;
					const uint16 localV2 = (localV1 + 1) % (quality * 4);

					const Vertex2D::IndexType t0 = v1 + localV1 + 4;
					const Vertex2D::IndexType t1 = v1 + localV2 + 4;
					const Vertex2D::IndexType t2 = localV1 + 4;
					const Vertex2D::IndexType t3 = localV2 + 4;

					pDst->i0 = t0;
					pDst->i1 = t1;
					pDst->i2 = t2;
					++pDst;

					pDst->i0 = t2;
					pDst->i1 = t1;
					pDst->i2 = t3;
					++pDst;
				}
			}
		}

		const Texture& texture = SIV3D_ENGINE(Renderer2D)->getBoxShadowTexture();
		SIV3D_ENGINE(Renderer2D)->addTexturedVertices(texture, vertices.data(), vertices.size(), indices.data(), indices.size());

		return *this;
	}

	TexturedRoundRect RoundRect::operator ()(const Texture& texture) const
	{
		return{ texture,
			0.0f, 0.0f, 1.0f, 1.0f,
			*this };
	}

	TexturedRoundRect RoundRect::operator ()(const TextureRegion& textureRegion) const
	{
		return{ textureRegion.texture,
			textureRegion.uvRect,
			*this };
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
