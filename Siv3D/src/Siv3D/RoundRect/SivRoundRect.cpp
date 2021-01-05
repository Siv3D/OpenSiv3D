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

# include <Siv3D/2DShapes.hpp>
# include <Siv3D/Polygon.hpp>
# include <Siv3D/FormatFloat.hpp>
# include <Siv3D/FloatRect.hpp>
# include <Siv3D/Mouse.hpp>
# include <Siv3D/Cursor.hpp>
# include <Siv3D/Geometry2D.hpp>
# include <Siv3D/Renderer2D/IRenderer2D.hpp>
# include <Siv3D/Common/Siv3DEngine.hpp>

namespace s3d
{
	namespace detail
	{
		inline constexpr uint16 CaluculateFanQuality(const double r) noexcept
		{
			return r <= 1.0 ? 3
				: r <= 6.0 ? 5
				: r <= 12.0 ? 8
				: static_cast<uint16>(Min(64.0, r * 0.2 + 6));
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
		if ((rect.w == 0.0) && (rect.h == 0.0))
		{
			return *this;
		}

		const Array<Vec2> vertices = detail::GetOuterVertices(*this, (outerThickness - innerThickness) * 0.5, none);

		SIV3D_ENGINE(Renderer2D)->addLineString(
			vertices.data(),
			static_cast<uint16>(vertices.size()),
			none,
			static_cast<float>(innerThickness + outerThickness),
			false,
			color.toFloat4(),
			IsClosed::Yes
		);

		return *this;
	}

	void RoundRect::_Formatter(FormatData& formatData, const RoundRect& value)
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
