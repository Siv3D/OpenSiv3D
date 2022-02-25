//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2022 Ryo Suzuki
//	Copyright (c) 2016-2022 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# pragma once

namespace s3d
{
	inline const Array<Float2>& Shape2D::vertices() const noexcept
	{
		return m_vertices;
	}

	inline const Array<TriangleIndex> Shape2D::indices() const noexcept
	{
		return m_indices;
	}
}
