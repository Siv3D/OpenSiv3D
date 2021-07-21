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

# version 410

//
//	Textures
//
uniform sampler2D Texture0;

//
//	PSInput
//
layout(location = 0) in vec3 WorldPosition;
layout(location = 1) in vec2 UV;
layout(location = 2) in vec3 Normal;

//
//	PSOutput
//
layout(location = 0) out vec4 FragColor;

//
//	Constant Buffer
//
layout(std140) uniform PSPerView
{
	vec3 g_eyePosition;
};

layout(std140) uniform PSPerMaterial
{
	vec3  g_amibientColor;
	bool  g_hasTexture;
	vec4  g_diffuseColor;
	vec3  g_specularColor;
	float g_shinness;
	vec3  g_emission;
};

//
//	Functions
//
void main()
{
	vec4 texColor = texture(Texture0, UV);

	FragColor = (g_diffuseColor * texColor);
}
