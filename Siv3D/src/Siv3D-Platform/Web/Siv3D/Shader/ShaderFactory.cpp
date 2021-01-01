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

# include <Siv3D/ApplicationOptions.hpp>
# include <Siv3D/Shader/Null/CShader_Null.hpp>
# include <Siv3D/Shader/GLES3/CShader_GLES3.hpp>

namespace s3d
{
	ISiv3DShader* ISiv3DShader::Create()
	{
		if (g_applicationOptions.renderer == EngineOption::Renderer::Headless)
		{
			return new CShader_Null;
		}
		else if (g_applicationOptions.renderer == EngineOption::Renderer::PlatformDefault
			|| g_applicationOptions.renderer == EngineOption::Renderer::WebGL2)
		{
			return new CShader_GLES3;
		}
		else
		{
			return new CShader_Null;
		}
	}
}
