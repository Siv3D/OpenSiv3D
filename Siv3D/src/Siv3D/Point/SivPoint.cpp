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

# include <Siv3D/PointVector.hpp>
# include <Siv3D/FormatInt.hpp>
# include <Siv3D/2DShapes.hpp>
# include <Siv3D/Mouse.hpp>
# include <Siv3D/Cursor.hpp>
# include <Siv3D/Image.hpp>

namespace s3d
{
	Circle Point::asCircle(const double r) const noexcept
	{
		return{ *this, r };
	}

	bool Point::leftClicked() const noexcept
	{
		return (MouseL.down() && mouseOver());
	}

	bool Point::leftPressed() const noexcept
	{
		return (MouseL.pressed() && mouseOver());
	}

	bool Point::leftReleased() const noexcept
	{
		return (MouseL.up() && mouseOver());
	}

	bool Point::rightClicked() const noexcept
	{
		return (MouseR.down() && mouseOver());
	}

	bool Point::rightPressed() const noexcept
	{
		return (MouseR.pressed() && mouseOver());
	}

	bool Point::rightReleased() const noexcept
	{
		return (MouseR.up() && mouseOver());
	}

	bool Point::mouseOver() const noexcept
	{
		return Geometry2D::Intersect(Cursor::PosF(), *this);
	}

	const Point& Point::paint(Image& dst, const Color& color) const
	{
		if ((x < 0) || (dst.width() <= x) || (y < 0) || (dst.height() <= y))
		{
			return *this;
		}

		const uint32 srcBlend = color.a;
		const uint32 dstBlend = (255 - srcBlend);

		Color* const pDst = (dst.data() + y * dst.width() + x);
		pDst->r = static_cast<uint8>(((pDst->r * dstBlend) + (color.r * srcBlend)) / 255);
		pDst->g = static_cast<uint8>(((pDst->g * dstBlend) + (color.g * srcBlend)) / 255);
		pDst->b = static_cast<uint8>(((pDst->b * dstBlend) + (color.b * srcBlend)) / 255);

		return *this;
	}

	const Point& Point::overwrite(Image& dst, const Color& color) const
	{
		if ((x < 0) || (dst.width() <= x) || (y < 0) || (dst.height() <= y))
		{
			return *this;
		}

		Color* const pDst = (dst.data() + y * dst.width() + x);
		*pDst = color;

		return *this;
	}

	void Formatter(FormatData& formatData, const Point& value)
	{
		const size_t bufferSize = ((detail::Int32Width * 2) + 4 + 1);
		char32 buf[bufferSize];
		char32* p = buf;

		*(p++) = U'(';
		detail::AppendInt32(&p, value.x);
		*(p++) = U',';
		*(p++) = U' ';
		detail::AppendInt32(&p, value.y);
		*(p++) = U')';

		formatData.string.append(buf, p - buf);
	}
}
