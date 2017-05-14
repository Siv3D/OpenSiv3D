//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2017 Ryo Suzuki
//	Copyright (c) 2016-2017 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# include <Siv3D/Platform.hpp>
# if defined(SIV3D_TARGET_MACOS) || defined(SIV3D_TARGET_LINUX)

# include "CShader_GL.hpp"

namespace s3d
{
	namespace detail
	{
		const String vsCode =
		LR"(
#version 410
		
layout(location = 0) in vec2 VertexPosition;
layout(location = 1) in vec2 VertexTex;
layout(location = 2) in vec4 VertexColor;
		
layout(location = 0) out vec4 Color;
layout(location = 1) out vec2 Tex;
out vec4 gl_Position;
		
layout(std140) uniform SpriteCB
{
	vec4 g_transform[2];
};
		
void main()
{
	Color = VertexColor;
	gl_Position.xy	= g_transform[0].zw + VertexPosition.x * g_transform[0].xy + VertexPosition.y * g_transform[1].xy;
	gl_Position.zw	= g_transform[1].zw;
	Tex = VertexTex;
}
)";
		
		const String psCodeShape =
		LR"(
#version 410
		
layout(location = 0) in vec4 Color;
		
layout(location = 0) out vec4 FragColor;
		
void main()
{
	FragColor = Color;
}
)";
		
		const String psCodeSprite =
		LR"(
#version 410
		
layout(location = 0) in vec4 Color;
layout(location = 1) in vec2 Tex;
		
uniform sampler2D Tex0;
		
layout(location = 0) out vec4 FragColor;
		
void main()
{
	FragColor = texture(Tex0, Tex) * Color;
}
)";
		
		const String psCodeLineDot =
		LR"(
#version 410
		
layout(location = 0) in vec4 Color;
layout(location = 1) in vec2 Tex;
		
layout(location = 0) out vec4 FragColor;
		
void main()
{
	FragColor = Color;
			
	float t = min(abs(1.5 - mod(Tex.x, 3.0)) * 1.7, 1.0);
			
	FragColor.a *= pow(t, 24);
}
)";
		
		const String psCodeLineRoundDot =
		LR"(
#version 410
		
layout(location = 0) in vec4 Color;
layout(location = 1) in vec2 Tex;
		
layout(location = 0) out vec4 FragColor;
		
void main()
{
	FragColor = Color;
			
	float t = mod(Tex.x, 2.0);
			
	t = abs(1.0 - t) * 2.0;
			
	FragColor.a *= 1.0 - clamp(pow(dot(vec2(t, Tex.y), vec2(t, Tex.y)), 12), 0.0, 1.0);
}
)";
	}
	
	CShader_GL::CShader_GL()
	{

	}

	CShader_GL::~CShader_GL()
	{
		m_standardVSs.clear();
		
		m_standardPSs.clear();
		
		m_vertexShaders.destroy();
		
		m_pixelShaders.destroy();
	}

	bool CShader_GL::init()
	{		
		{
			const auto nullVertexShader = std::make_shared<VertexShader_GL>(VertexShader_GL::Null{});
			
			if (!nullVertexShader->isInitialized())
			{
				return false;
			}
			
			m_vertexShaders.setNullData(nullVertexShader);
		}
		
		{
			const auto nullPixelShader = std::make_shared<PixelShader_GL>(PixelShader_GL::Null{});
			
			if (!nullPixelShader->isInitialized())
			{
				return false;
			}
			
			m_pixelShaders.setNullData(nullPixelShader);
		}
		
		m_standardVSs.push_back(VertexShader(Arg::source = detail::vsCode, { { S3DSTR("SpriteCB"), 0 } }));
		m_standardPSs.push_back(PixelShader(Arg::source = detail::psCodeShape));
		m_standardPSs.push_back(PixelShader(Arg::source = detail::psCodeLineDot));
		m_standardPSs.push_back(PixelShader(Arg::source = detail::psCodeLineRoundDot));
		m_standardPSs.push_back(PixelShader(Arg::source = detail::psCodeSprite));
		
		return true;
	}
	
	VertexShader::IDType CShader_GL::createVSFromSource(const String& source, const Array<BindingPoint>& bindingPoints)
	{
		const auto vertexShader = std::make_shared<VertexShader_GL>(source);
		
		if (!vertexShader->isInitialized())
		{
			return VertexShader::IDType(0);
		}
		
		for (const auto& bindingPoint : bindingPoints)
		{
			vertexShader->setUniformBlockBinding(bindingPoint.bufferName.narrow().c_str(), bindingPoint.index);
		}
		
		return m_vertexShaders.add(vertexShader);
	}
	
	PixelShader::IDType CShader_GL::createPSFromSource(const String& source, const Array<BindingPoint>& bindingPoints)
	{
		const auto pixelShader = std::make_shared<PixelShader_GL>(source);
		
		if (!pixelShader->isInitialized())
		{
			return PixelShader::IDType(0);
		}
		
		for (const auto& bindingPoint : bindingPoints)
		{
			pixelShader->setUniformBlockBinding(bindingPoint.bufferName.narrow().c_str(), bindingPoint.index);
		}
		
		return m_pixelShaders.add(pixelShader);
	}
	
	void CShader_GL::releaseVS(const VertexShader::IDType handleID)
	{
		m_vertexShaders.erase(handleID);
	}
	
	void CShader_GL::releasePS(const PixelShader::IDType handleID)
	{
		m_pixelShaders.erase(handleID);
	}
	
	GLuint CShader_GL::getVSProgram(const VertexShader::IDType handleID)
	{
		return m_vertexShaders[handleID]->getProgram();
	}
	
	GLuint CShader_GL::getPSProgram(const PixelShader::IDType handleID)
	{
		return m_pixelShaders[handleID]->getProgram();
	}
	
	void CShader_GL::setPSSamplerUniform(const PixelShader::IDType handleID)
	{
		m_pixelShaders[handleID]->setPSSamplerUniform();
	}
}

# endif
