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

# include <Siv3D/Line.hpp>

namespace s3d
{
	Line::position_type Line::closest(const position_type& pos) const
	{
		Vec2 v = end - begin;
		const double d = v.length();
		
		if (d == 0.0)
		{
			return begin;
		}
		
		v /= d;
		const double t = v.dot(pos - begin);
		
		if (t < 0.0)
		{
			return begin;
		}
		
		if (t > d)
		{
			return end;
		}
		
		return begin + v * t;
	}
	
	//Optional<Line::position_type> Line::intersectsAt(const Line& line) const
	//{
	//
	//}
}
