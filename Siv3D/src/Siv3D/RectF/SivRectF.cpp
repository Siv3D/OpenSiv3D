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
# include <Siv3D/FormatFloat.hpp>
# include <Siv3D/FormatData.hpp>
# include <Siv3D/FloatRect.hpp>
# include <Siv3D/LineString.hpp>
# include <Siv3D/MathConstants.hpp>
# include <Siv3D/Polygon.hpp>
# include <Siv3D/Mouse.hpp>
# include <Siv3D/Cursor.hpp>
# include <Siv3D/Geometry2D.hpp>
# include <Siv3D/TextureRegion.hpp>
# include <Siv3D/TexturedQuad.hpp>
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
	}

	Quad RectF::rotated(const double angle) const noexcept
	{
		const Vec2 cent{ (x + w * 0.5), (y + h * 0.5) };
		const double cx = cent.x;
		const double cy = cent.y;
		const double x0 = -size.x * 0.5;
		const double x1 = size.x * 0.5;
		const double y0 = -size.y * 0.5;
		const double y1 = size.y * 0.5;
		const double s = std::sin(angle);
		const double c = std::cos(angle);
		const double x0c = x0 * c;
		const double x0s = x0 * s;
		const double x1c = x1 * c;
		const double x1s = x1 * s;
		const double y0c = y0 * c;
		const double y0s = y0 * s;
		const double y1c = y1 * c;
		const double y1s = y1 * s;
		return{ { x0c - y0s + cx, x0s + y0c + cy },{ x1c - y0s + cx, x1s + y0c + cy },{ x1c - y1s + cx, x1s + y1c + cy },{ x0c - y1s + cx, x0s + y1c + cy } };
	}

	Quad RectF::rotatedAt(const double _x, const double _y, const double angle) const noexcept
	{
		return rotatedAt({ _x, _y }, angle);
	}

	Quad RectF::rotatedAt(const Vec2 _pos, const double angle) const noexcept
	{
		Vec2 pts[4] = { { x, y },{ x + w, y },{ x + w, y + h },{ x, y + h } };

		for (int32 i = 0; i < 4; ++i)
		{
			pts[i] -= _pos;
		}

		const double s = std::sin(angle);
		const double c = std::cos(angle);

		Quad quad;

		for (int32 i = 0; i < 4; ++i)
		{
			quad.p(i).x = pts[i].x * c - pts[i].y * s + _pos.x;
			quad.p(i).y = pts[i].x * s + pts[i].y * c + _pos.y;
		}

		return quad;
	}

	Polygon RectF::rounded(double tl, double tr, double br, double bl) const noexcept
	{
		constexpr double epsilon = 0.001;

		tl = Max(tl, 0.0);
		tr = Max(tr, 0.0);
		br = Max(br, 0.0);
		bl = Max(bl, 0.0);

		if (const double t = (tl + tr); t > w)
		{
			const double s = w / t;
			tl *= s;
			tr *= s;
			br *= s;
			bl *= s;
		}

		if (const double r = (tr + br); r > h)
		{
			const double s = h / r;
			tl *= s;
			tr *= s;
			br *= s;
			bl *= s;
		}

		if (const double b = (bl + br); b > w)
		{
			const double s = w / b;
			tl *= s;
			tr *= s;
			br *= s;
			bl *= s;
		}

		if (const double l = (tl + bl); l > h)
		{
			const double s = h / l;
			tl *= s;
			tr *= s;
			br *= s;
			bl *= s;
		}

		const Vec2 tlCenter = (this->tl() + Vec2{ tl, tl });
		const Vec2 trCenter = (this->tr() + Vec2{ -tr, tr });
		const Vec2 brCenter = (this->br() + Vec2{ -br, -br });
		const Vec2 blCenter = (this->bl() + Vec2{ bl, -bl });

		const float scale = SIV3D_ENGINE(Renderer2D)->getMaxScaling();

		Array<Vec2> vertices;

		if (tl)
		{
			const Vertex2D::IndexType quality = detail::CaluculateFanQuality(tl * scale);
			const double radDelta = Math::HalfPi / (quality - 1);

			for (Vertex2D::IndexType i = 0; i < quality; ++i)
			{
				vertices << (Circular9{ tl, radDelta * i } + tlCenter);
			}
		}
		else
		{
			vertices << tlCenter;
		}

		if (tr)
		{
			const Vertex2D::IndexType quality = detail::CaluculateFanQuality(tr * scale);
			const double radDelta = Math::HalfPi / (quality - 1);

			for (Vertex2D::IndexType i = 0; i < quality; ++i)
			{
				vertices << (Circular0{ tr, radDelta * i } + trCenter);
			}
		}
		else
		{
			vertices << trCenter;
		}

		if (br)
		{
			const Vertex2D::IndexType quality = detail::CaluculateFanQuality(br * scale);
			const double radDelta = Math::HalfPi / (quality - 1);

			for (Vertex2D::IndexType i = 0; i < quality; ++i)
			{
				vertices << (Circular3{ br, radDelta * i } + brCenter);
			}
		}
		else
		{
			vertices << brCenter;
		}

		if (bl)
		{
			const Vertex2D::IndexType quality = detail::CaluculateFanQuality(bl * scale);
			const double radDelta = Math::HalfPi / (quality - 1);

			for (Vertex2D::IndexType i = 0; i < quality; ++i)
			{
				vertices << (Circular6{ bl, radDelta * i } + blCenter);
			}
		}
		else
		{
			vertices << blCenter;
		}

		for (auto it = (vertices.begin() + 1); it != vertices.end();)
		{
			if (it->distanceFromSq(*(it - 1)) < epsilon)
			{
				it = vertices.erase(it);
			}
			else
			{
				++it;
			}
		}

		if ((vertices.size() > 3)
			&& (vertices.front().distanceFromSq(vertices.back()) < epsilon))
		{
			vertices.pop_back();
		}

		return Polygon{ vertices };
	}

	LineString RectF::outline(const CloseRing closeRing) const
	{
		if (closeRing)
		{
			return{ pos, tr(), br(), bl(), pos };
		}
		else
		{
			return{ pos, tr(), br(), bl() };
		}
	}

	LineString RectF::outline(double distanceFromOrigin, double length) const
	{
		if (length <= 0.0)
		{
			distanceFromOrigin += length;
			length = -length;
		}

		const Vec2 ps[4] = {
			pos, tr(), br(), bl()
		};
		constexpr size_t N = 4;
		const double lens[N] = {
			static_cast<double>(w), static_cast<double>(h), static_cast<double>(w), static_cast<double>(h)
		};
		const double perim = (w * 2 + h * 2);

		distanceFromOrigin = std::fmod(distanceFromOrigin, perim) + (distanceFromOrigin < 0 ? perim : 0);
		length = Min(length, perim);
		const double distanceToTarget = (distanceFromOrigin + length);

		LineString points;
		double currentLength = 0.0;

		for (size_t n = 0; n < (N * 2); ++n)
		{
			const size_t i = (n % N);
			const double len = lens[i];
			const Vec2 pFrom = ps[i];
			const Vec2 pTo = ps[(N <= (i + 1)) ? (i - (N - 1)) : (i + 1)];

			if (not points)
			{
				if ((distanceFromOrigin <= (currentLength + len)))
				{
					const Vec2 origin = pFrom + (pTo - pFrom)
						.setLength(distanceFromOrigin - currentLength);
					points << origin;

					if (distanceToTarget <= (currentLength + len))
					{
						const Vec2 target = pFrom + (pTo - pFrom)
							.setLength(distanceToTarget - currentLength);
						points << target;
						break;
					}

					points << pTo;
				}
			}
			else
			{
				if (distanceToTarget <= (currentLength + len))
				{
					const Vec2 target = pFrom + (pTo - pFrom)
						.setLength(distanceToTarget - currentLength);
					points << target;
					break;
				}

				points << pTo;
			}

			currentLength += len;
		}

		return points;
	}

	Polygon RectF::asPolygon() const
	{
		if ((w <= 0) || (h <= 0))
		{
			return{};
		}

		return Polygon{ { tl(), tr(), br(), bl() },
			{ {0, 1, 3}, {3, 1, 2}},
			*this,
			SkipValidation::Yes };
	}

	bool RectF::leftClicked() const noexcept
	{
		return (MouseL.down() && mouseOver());
	}

	bool RectF::leftPressed() const noexcept
	{
		return (MouseL.pressed() && mouseOver());
	}

	bool RectF::leftReleased() const noexcept
	{
		return (MouseL.up() && mouseOver());
	}

	bool RectF::rightClicked() const noexcept
	{
		return (MouseR.down() && mouseOver());
	}

	bool RectF::rightPressed() const noexcept
	{
		return (MouseR.pressed() && mouseOver());
	}

	bool RectF::rightReleased() const noexcept
	{
		return (MouseR.up() && mouseOver());
	}

	bool RectF::mouseOver() const noexcept
	{
		return Geometry2D::Intersect(Cursor::PosF(), *this);
	}

	const RectF& RectF::paint(Image& dst, const Color& color) const
	{
		asRect().paint(dst, color);

		return *this;
	}

	const RectF& RectF::overwrite(Image& dst, const Color& color) const
	{
		asRect().overwrite(dst, color);

		return *this;
	}

	const RectF& RectF::paintFrame(Image& dst, const int32 innerThickness, const int32 outerThickness, const Color& color) const
	{
		asRect().paintFrame(dst, innerThickness, outerThickness, color);

		return *this;
	}

	const RectF& RectF::overwriteFrame(Image& dst, const int32 innerThickness, const int32 outerThickness, const Color& color) const
	{
		asRect().overwriteFrame(dst, innerThickness, outerThickness, color);

		return *this;
	}

	const RectF& RectF::draw(const ColorF& color) const
	{
		SIV3D_ENGINE(Renderer2D)->addRect(FloatRect{ x, y, (x + w), (y + h) }, color.toFloat4());

		return *this;
	}

	const RectF& RectF::draw(const ColorF(&colors)[4]) const
	{
		SIV3D_ENGINE(Renderer2D)->addRect(FloatRect{ x, y, (x + w), (y + h) },
			{ colors[0].toFloat4(), colors[1].toFloat4(), colors[2].toFloat4(), colors[3].toFloat4() });

		return *this;
	}

	const RectF& RectF::draw(const Arg::top_<ColorF> topColor, const Arg::bottom_<ColorF> bottomColor) const
	{
		const Float4 color0 = topColor->toFloat4();
		const Float4 color1 = bottomColor->toFloat4();

		SIV3D_ENGINE(Renderer2D)->addRect(FloatRect{ x, y, (x + w), (y + h) },
			{ color0, color0, color1, color1 });

		return *this;
	}

	const RectF& RectF::draw(const Arg::left_<ColorF> leftColor, const Arg::right_<ColorF> rightColor) const
	{
		const Float4 color0 = leftColor->toFloat4();
		const Float4 color1 = rightColor->toFloat4();

		SIV3D_ENGINE(Renderer2D)->addRect(FloatRect{ x, y, (x + w), (y + h) },
			{ color0, color1, color1, color0 });

		return *this;
	}

	const RectF& RectF::drawFrame(const double thickness, const ColorF& color) const
	{
		return drawFrame((thickness * 0.5), (thickness * 0.5), color);
	}

	const RectF& RectF::drawFrame(const double thickness, const ColorF& innerColor, const ColorF& outerColor) const
	{
		return drawFrame((thickness * 0.5), (thickness * 0.5), innerColor, outerColor);
	}

	const RectF& RectF::drawFrame(const double innerThickness, const double outerThickness, const ColorF& color) const
	{
		if ((w <= 0.0) || (h <= 0.0)
			|| (innerThickness < 0.0) || (outerThickness < 0.0)
			|| ((innerThickness == 0.0) && (outerThickness == 0.0)))
		{
			return *this;
		}

		if (((w * 0.5) <= innerThickness) || ((h * 0.5) <= innerThickness))
		{
			stretched(outerThickness).draw(color);
			return *this;
		}

		const Float4 color0 = color.toFloat4();

		SIV3D_ENGINE(Renderer2D)->addRectFrame(
			FloatRect{ (x + innerThickness), (y + innerThickness), (x + w - innerThickness), (y + h - innerThickness) },
			static_cast<float>(innerThickness + outerThickness),
			color0, color0);

		return *this;
	}

	const RectF& RectF::drawFrame(const double innerThickness, const double outerThickness, const ColorF& innerColor, const ColorF& outerColor) const
	{
		SIV3D_ENGINE(Renderer2D)->addRectFrame(
			FloatRect{ (x + innerThickness), (y + innerThickness), (x + w - innerThickness), (y + h - innerThickness) },
			static_cast<float>(innerThickness + outerThickness),
			innerColor.toFloat4(), outerColor.toFloat4());

		return *this;
	}
	
	const RectF& RectF::drawShadow(const Vec2& offset, const double blurRadius, const double spread, const ColorF& color) const
	{
		if (blurRadius < 0.0)
		{
			return *this;
		}

		const Float4 colorF = color.toFloat4();
		const RectF rect	= RectF{ pos + offset, size }.stretched(spread + blurRadius * 0.5);
		const double rr		= Min({ (rect.w * 0.5), (rect.h * 0.5), blurRadius });
		const float xs[4] =
		{
			static_cast<float>(rect.x),
			static_cast<float>(rect.x + rr),
			static_cast<float>(rect.x + rect.w - rr),
			static_cast<float>(rect.x + rect.w)
		};
		const float ys[4] =
		{
			static_cast<float>(rect.y),
			static_cast<float>(rect.y + rr),
			static_cast<float>(rect.y + rect.h - rr),
			static_cast<float>(rect.y + rect.h)
		};
		const float uvs[4] = { 0.0f, 0.5f, 0.5f, 1.0f };

		Array<Vertex2D> vertices(16);
		{
			Vertex2D* pDst = vertices.data();

			for (int32 i = 0; i < 16; ++i)
			{
				pDst->pos.set(xs[i % 4], ys[i / 4]);
				pDst->tex.set(uvs[i % 4], uvs[i / 4]);
				pDst->color = colorF;
				++pDst;
			}
		}

		Array<TriangleIndex> indices(18);
		{
			TriangleIndex* pDst = indices.data();

			for (Vertex2D::IndexType ty = 0; ty < 3; ++ty)
			{
				for (Vertex2D::IndexType tx = 0; tx < 3; ++tx)
				{
					const Vertex2D::IndexType base = ((ty * 4) + tx);

					pDst->i0 = base;
					pDst->i1 = (base + 1);
					pDst->i2 = (base + 4);
					++pDst;

					pDst->i0 = (base + 4);
					pDst->i1 = (base + 1);
					pDst->i2 = (base + 5);
					++pDst;
				}
			}
		}

		const Texture& texture = SIV3D_ENGINE(Renderer2D)->getBoxShadowTexture();
		SIV3D_ENGINE(Renderer2D)->addTexturedVertices(texture, vertices.data(), vertices.size(), indices.data(), indices.size());

		return *this;
	}

	TexturedQuad RectF::operator ()(const Texture& texture) const
	{
		return{ texture,
			0.0f, 0.0f, 1.0f, 1.0f,
			Quad{ pos,{ (x + w), y },{ (x + w), (y + h) },{ x, (y + h) } },
			center() };
	}

	TexturedQuad RectF::operator ()(const TextureRegion& textureRegion) const
	{
		return{ textureRegion.texture,
			textureRegion.uvRect,
			Quad{ pos,{ (x + w), y },{ (x + w), (y + h) },{ x, (y + h) } },
			center() };
	}

	void Formatter(FormatData& formatData, const RectF& value)
	{
		formatData.string.push_back(U'(');
		formatData.string.append(ToString(value.x, formatData.decimalPlaces.value));
		formatData.string.append(U", "_sv);
		formatData.string.append(ToString(value.y, formatData.decimalPlaces.value));
		formatData.string.append(U", "_sv);
		formatData.string.append(ToString(value.w, formatData.decimalPlaces.value));
		formatData.string.append(U", "_sv);
		formatData.string.append(ToString(value.h, formatData.decimalPlaces.value));
		formatData.string.push_back(U')');
	}
}
