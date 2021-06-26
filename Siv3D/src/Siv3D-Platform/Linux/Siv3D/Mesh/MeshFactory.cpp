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

# include <Siv3D/EngineOptions.hpp>
# include <Siv3D/Mesh/Null/CMesh_Null.hpp>
# include <Siv3D/Mesh/GL4/CMesh_GL4.hpp>

namespace s3d
{
	ISiv3DMesh* ISiv3DMesh::Create()
	{
		if (g_engineOptions.renderer == EngineOption::Renderer::Headless)
		{
			return new CMesh_Null;
		}
		else
		{
			return new CMesh_GL4;
		}
	}
}
