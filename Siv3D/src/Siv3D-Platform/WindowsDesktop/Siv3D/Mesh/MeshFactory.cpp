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
# include <Siv3D/Mesh/GL4/CMesh_GL4.hpp>
# include <Siv3D/Mesh/D3D11/CMesh_D3D11.hpp>

namespace s3d
{
	ISiv3DMesh* ISiv3DMesh::Create()
	{
		if (g_engineOptions.renderer == EngineOption::Renderer::Headless)
		{
			return new CMesh_Null;
		}
		else if (g_engineOptions.renderer == EngineOption::Renderer::PlatformDefault
			|| g_engineOptions.renderer == EngineOption::Renderer::Direct3D11)
		{
			return new CMesh_D3D11;
		}
		else
		{
			return new CMesh_GL4;
		}
	}
}
