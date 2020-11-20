//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2020 Ryo Suzuki
//	Copyright (c) 2016-2020 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# include <Siv3D/2DShapes.hpp>
# include <Siv3D/FormatFloat.hpp>
# include <Siv3D/Renderer2D/IRenderer2D.hpp>
# include <Siv3D/Common/Siv3DEngine.hpp>

namespace s3d
{
	namespace detail
	{
		//
		// http://imagingsolution.blog107.fc2.com/blog-entry-137.html
		//
		static Vec2 GetP(const Vec2& p0, const Vec2& p1, const Vec2& p2, const Vec2& p3) noexcept
		{
			const double a = (p3.x - p2.x) * (p0.y - p2.y) - (p3.y - p2.y) * (p0.x - p2.x);
			const double b = (p3.x - p2.x) * (p2.y - p1.y) - (p3.y - p2.y) * (p2.x - p1.x);
			const double c = a / (a + b);
			return{ (p0.x + (p1.x - p0.x) * c), (p0.y + (p1.y - p0.y) * c) };
		}
	}

	Triangle Triangle::stretched(const value_type size) const noexcept
	{
		Line lines[3] =
		{
			{ p0, p1 }, { p1, p2 }, { p2, p0 }
		};

		for (auto& line : lines)
		{
			const Vec2 v = (line.end - line.begin).setLength(size);
			line.moveBy(v.y, -v.x);
		}

		const Vec2 t0 = detail::GetP(lines[2].begin, lines[2].end, lines[0].begin, lines[0].end);
		const Vec2 t1 = detail::GetP(lines[0].begin, lines[0].end, lines[1].begin, lines[1].end);
		const Vec2 t2 = detail::GetP(lines[1].begin, lines[1].end, lines[2].begin, lines[2].end);
		return{ t0, t1, t2 };
	}

	const Triangle& Triangle::draw(const ColorF& color) const
	{
		SIV3D_ENGINE(Renderer2D)->addTriangle({ p0, p1, p2 }, color.toFloat4());

		return *this;
	}

	const Triangle& Triangle::draw(const ColorF& color0, const ColorF& color1, const ColorF& color2) const
	{
		SIV3D_ENGINE(Renderer2D)->addTriangle(
			{ p0, p1, p2 },
			{ color0.toFloat4(), color1.toFloat4(), color2.toFloat4() });

		return *this;
	}

	const Triangle& Triangle::drawFrame(const double thickness, const ColorF& color) const
	{
		SIV3D_ENGINE(Renderer2D)->addLineString(&p0, 3, none,
			static_cast<float>(thickness), false, color.toFloat4(), IsClosed::Yes);

		return *this;
	}

	const Triangle& Triangle::drawFrame(const double innerThickness, const double outerThickness, const ColorF& color) const
	{
		const double offset = (outerThickness - innerThickness) * 0.5;
		const Triangle t = stretched(offset);

		SIV3D_ENGINE(Renderer2D)->addLineString(&t.p0, 3, none,
			static_cast<float>(innerThickness + outerThickness),
			(outerThickness == 0.0), color.toFloat4(), IsClosed::Yes);

		return *this;
	}

	void Triangle::_Formatter(FormatData& formatData, const Triangle& value)
	{
		formatData.string.append(U"(("_sv);

		formatData.string.append(ToString(value.p0.x, formatData.decimalPlaces.value));
		formatData.string.append(U", "_sv);
		formatData.string.append(ToString(value.p0.y, formatData.decimalPlaces.value));
		formatData.string.append(U"), ("_sv);

		formatData.string.append(ToString(value.p1.x, formatData.decimalPlaces.value));
		formatData.string.append(U", "_sv);
		formatData.string.append(ToString(value.p1.y, formatData.decimalPlaces.value));
		formatData.string.append(U"), ("_sv);

		formatData.string.append(ToString(value.p2.x, formatData.decimalPlaces.value));
		formatData.string.append(U", "_sv);
		formatData.string.append(ToString(value.p2.y, formatData.decimalPlaces.value));
		formatData.string.append(U"))"_sv);
	}
}
