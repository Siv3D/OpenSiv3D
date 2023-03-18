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

# include <Siv3D/EngineOptions.hpp>
# include <Siv3D/Mesh/Null/CMesh_Null.hpp>
# include <Siv3D/Mesh/GLES3/CMesh_GLES3.hpp>

namespace s3d
{
	__attribute__((weak))
	ISiv3DMesh* ISiv3DMesh::Create()
	{
		if (g_engineOptions.renderer == EngineOption::Renderer::Headless)
		{
			return new CMesh_Null;
		}
		else
		{
			return new CMesh_GLES3;
		}
	}
}
