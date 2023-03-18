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
# include <Siv3D/PointVector.hpp>
# include <Siv3D/Vertex3D.hpp>

namespace s3d
{
	struct VertexLine3D
	{
		Float4 pos;

		Float4 color;

		using IndexType = Vertex3D::IndexType;
	};

	struct VertexLine3DBufferPointer
	{
		VertexLine3D* pVertex;

		VertexLine3D::IndexType* pIndex;

		VertexLine3D::IndexType indexOffset;
	};
}
