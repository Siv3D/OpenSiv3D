/*
* clip2tri.h
*
* Authors: kaen, raptor, sam686, watusimoto
*
* Originally from the bitfighter source code
*/

# pragma once
# include <Siv3D/Fwd.hpp>
# include <Siv3D/Array.hpp>
# include <Siv3D/PointVector.hpp>
# include "../clipper/clipper.hpp"

namespace s3d
{
	bool Triangulate(const Array<Array<Vec2>>& inputPolygons, const Array<Vec2>& boundingPolygon, Array<Float2> &vertices, Array<uint16>& indices);
}
