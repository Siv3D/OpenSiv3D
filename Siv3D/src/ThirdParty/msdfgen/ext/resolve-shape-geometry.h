
#pragma once

#include "../core/Shape.h"

namespace msdfgen {

/// Resolves any intersections within the shape by subdividing its contours using the Skia library and makes sure its contours have a consistent winding.
bool resolveShapeGeometry(Shape &shape);

}
