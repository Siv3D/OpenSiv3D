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

# include <Siv3D/PointVector.hpp>
# include <Siv3D/FormatInt.hpp>
# include <Siv3D/2DShapes.hpp>
# include <Siv3D/Mouse.hpp>
# include <Siv3D/Cursor.hpp>

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

	void Point::_Formatter(FormatData& formatData, const Point& value)
	{
		const size_t bufferSize = (detail::Int32Width * 2) + 4 + 1;
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
