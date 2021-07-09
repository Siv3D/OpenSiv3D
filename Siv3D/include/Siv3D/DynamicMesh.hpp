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

# pragma once
# include "Common.hpp"
# include "Mesh.hpp"

namespace s3d
{
	class DynamicMesh : public Mesh
	{
	public:

		// [Siv3D ToDo]


		void swap(DynamicMesh& other) noexcept;
	};
}

template <>
inline void std::swap(s3d::DynamicMesh& a, s3d::DynamicMesh& b) noexcept;

# include "detail/DynamicMesh.ipp"
