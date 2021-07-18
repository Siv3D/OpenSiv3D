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
# include "Material.hpp"
# include "Mesh.hpp"

namespace s3d
{
	struct ModelMesh
	{
		String name;

		Mesh mesh;

		Material material;
	};
}
