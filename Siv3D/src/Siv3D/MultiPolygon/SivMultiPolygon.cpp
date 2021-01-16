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

# include <Siv3D/MultiPolygon.hpp>
# include <Siv3D/Mouse.hpp>
# include <Siv3D/Cursor.hpp>
# include <Siv3D/Geometry2D.hpp>

namespace s3d
{
	RectF MultiPolygon::calculateBoundingRect() const noexcept
	{
		if (isEmpty())
		{
			return RectF{ 0 };
		}

		auto it				= begin();
		const auto itEnd	= end();

		const RectF rect = it->boundingRect();
		double left		= rect.x;
		double top		= rect.y;
		double right	= (rect.x + rect.w);
		double bottom	= (rect.y + rect.h);

		++it;

		while (it != itEnd)
		{
			if (rect.x < left)
			{
				left = rect.x;
			}

			if (right < (rect.x + rect.w))
			{
				right = (rect.x + rect.w);
			}

			if (rect.y < top)
			{
				top = rect.y;
			}

			if (bottom < (rect.y + rect.h))
			{
				bottom = (rect.y + rect.h);
			}

			++it;
		}

		return RectF{ left, top, (right - left), (bottom - top) };
	}

	bool MultiPolygon::leftClicked() const noexcept
	{
		return (MouseL.down() && mouseOver());
	}

	bool MultiPolygon::leftPressed() const noexcept
	{
		return (MouseL.pressed() && mouseOver());
	}

	bool MultiPolygon::leftReleased() const noexcept
	{
		return (MouseL.up() && mouseOver());
	}

	bool MultiPolygon::rightClicked() const noexcept
	{
		return (MouseR.down() && mouseOver());
	}

	bool MultiPolygon::rightPressed() const noexcept
	{
		return (MouseR.pressed() && mouseOver());
	}

	bool MultiPolygon::rightReleased() const noexcept
	{
		return (MouseR.up() && mouseOver());
	}

	bool MultiPolygon::mouseOver() const noexcept
	{
		return Geometry2D::Intersect(Cursor::PosF(), *this);
	}
}
