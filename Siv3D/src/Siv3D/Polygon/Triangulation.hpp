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

# pragma once
# include <Siv3D/Common.hpp>
# include <Siv3D/Array.hpp>
# include <Siv3D/PointVector.hpp>
# include <Siv3D/Vertex2D.hpp>

namespace s3d::detail
{
	void Triangulate(const Array<Vec2>& outer, const Array<Array<Vec2>>& holes, Array<Float2>& dstVertices, Array<Vertex2D::IndexType>& dstIndices);
}
