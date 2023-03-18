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
# include <Siv3D/Image.hpp>

namespace s3d
{
	namespace ShapePainting
	{
		void PaintLineString(Array<uint32>& pBuffer, const LineString& lineString, int32 width, int32 height, int32 thickness, bool isClosed);

		void PaintLine(Array<uint32>& pBuffer, const Line& line, int32 width, int32 height, int32 thickness);

		void PaintTriangle(Array<uint32>& pBuffer, const Triangle& triangle, int32 width, int32 height);

		void PaintQuad(Array<uint32>& pBuffer, const Quad& quad, int32 width, int32 height);

		void PaintPolygon(Array<uint32>& pBuffer, const Array<const Point*>& ptsList, const Array<int32>& npts, int32 width, int32 height);
	}
}
