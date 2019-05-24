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

# include <Siv3D/Point.hpp>
# include <Siv3D/Mouse.hpp>
# include <Siv3D/Cursor.hpp>

namespace s3d
{
	bool Point::leftClicked() const
	{
		return MouseL.down() && mouseOver();
	}

	bool Point::leftPressed() const
	{
		return MouseL.pressed() && mouseOver();
	}

	bool Point::leftReleased() const
	{
		return MouseL.up() && mouseOver();
	}

	bool Point::rightClicked() const
	{
		return MouseR.down() && mouseOver();
	}

	bool Point::rightPressed() const
	{
		return MouseR.pressed() && mouseOver();
	}

	bool Point::rightReleased() const
	{
		return MouseR.up() && mouseOver();
	}

	bool Point::mouseOver() const
	{
		return Geometry2D::Intersect(*this, Cursor::PosF());
	}

	void Formatter(FormatData& formatData, const Point& value)
	{
		const size_t bufferSize = 12 * 2 + 5;
		char32 buf[bufferSize];
		char32* p = buf;

		*(p++) = U'(';
		detail::AppendInt(&p, value.x);
		*(p++) = U',';
		*(p++) = U' ';
		detail::AppendInt(&p, value.y);
		*(p++) = U')';

		formatData.string.append(buf, p - buf);
	}
}
