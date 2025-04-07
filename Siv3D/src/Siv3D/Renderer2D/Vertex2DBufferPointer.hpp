//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2025 Ryo Suzuki
//	Copyright (c) 2016-2025 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# pragma once
# include <Siv3D/Common.hpp>
# include <Siv3D/Vertex2D.hpp>

namespace s3d
{
	struct Vertex2DBufferPointer
	{
		Vertex2D* pVertex;

		Vertex2D::IndexType* pIndex;

		Vertex2D::IndexType indexOffset;
	};
}
