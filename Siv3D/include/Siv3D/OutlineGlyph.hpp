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

# pragma once
# include "Fwd.hpp"
# include "Array.hpp"
# include "PointVector.hpp"
# include "Bezier2.hpp"
# include "Bezier3.hpp"

namespace s3d
{
	struct OutlineGlyph
	{
		Array<Array<Array<Vec2>>> contourPaths;

		OutlineGlyph();

		~OutlineGlyph();

		//void draw(double thickness = 1.0, const ColorF& color = Palette::White) const
		//{
		//	for (const auto& contourPath : contourPaths)
		//	{
		//		for (const auto& path : contourPath)
		//		{
		//			if (path.size() == 2)
		//			{
		//				Line(path[0], path[1]).draw(thickness, color);
		//			}
		//			else if (path.size() == 3)
		//			{
		//				Bezier2(path[0], path[1], path[2]).draw(thickness, color);
		//			}
		//			else if (path.size() == 4)
		//			{
		//				Bezier3(path[0], path[1], path[2], path[3]).draw(thickness, color);
		//			}
		//		}
		//	}
		//}
	};
}
