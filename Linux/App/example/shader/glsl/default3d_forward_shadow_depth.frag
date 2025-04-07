//	Copyright (c) 2008-2025 Ryo Suzuki.
//	Copyright (c) 2016-2025 OpenSiv3D Project.
//	Licensed under the MIT License.

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
layout(location = 0) out vec2 FragColor;

//
//	Constant Buffer
//
layout(std140) uniform PSPerFrame // slot 0
{
	vec3 g_globalAmbientColor;
	vec3 g_sunColor;
	vec3 g_sunDirection;
};

layout(std140) uniform PSPerView // slot 1
{
	vec3 g_eyePosition;
};

layout(std140) uniform PSPerMaterial // slot 3
{
	vec3  g_ambientColor;
	uint  g_hasTexture;
	vec4  g_diffuseColor;
	vec3  g_specularColor;
	float g_shininess;
	vec3  g_emissionColor;
};

////////////////////////////////////////////////////////////
//
//	Depth
//

layout(std140) uniform PSShadow // slot 4
{
	mat4x4 g_worldToProjectedShadow;
	vec3 g_sunPosition;
	float g_lightBleedingReduction;
};

void main()
{
	float depth = length(g_sunPosition - WorldPosition);
	FragColor = vec2(depth, (depth * depth));
}

//
////////////////////////////////////////////////////////////
