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
# include <Siv3D/ConstantBuffer/Null/ConstantBufferDetail_Null.hpp>
# include <Siv3D/ConstantBuffer/GL4/ConstantBufferDetail_GL4.hpp>

namespace s3d
{
	IConstantBufferDetail* IConstantBufferDetail::Create(const size_t size)
	{
		if (g_applicationOptions.renderer == EngineOption::Renderer::Headless)
		{
			return new ConstantBufferDetail_Null(size);
		}
		else if (g_applicationOptions.renderer == EngineOption::Renderer::PlatformDefault
			|| g_applicationOptions.renderer == EngineOption::Renderer::OpenGL)
		{
			return new ConstantBufferDetail_GL4(size);
		}
		else
		{
			return new ConstantBufferDetail_Null(size);
		}
	}
}
