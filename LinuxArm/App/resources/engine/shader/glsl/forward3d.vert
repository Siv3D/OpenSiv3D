//	Copyright (c) 2008-2021 Ryo Suzuki.
//	Copyright (c) 2016-2021 OpenSiv3D Project.
//	Licensed under the MIT License.

# version 410

//
//	VSInput
//
layout(location = 0) in vec4 VertexPosition;
layout(location = 1) in vec3 VertexNormal;
layout(location = 2) in vec2 VertexUV;

//
//	VSOutput
//
layout(location = 0) out vec3 WorldPosition;
layout(location = 1) out vec2 UV;
layout(location = 2) out vec3 Normal;
out gl_PerVertex
{
	vec4 gl_Position;
};

//
//	Constant Buffer
//
layout(std140) uniform VSPerView
{
	mat4x4 g_worldToProjected;
};

layout(std140) uniform VSPerObject
{
	mat4x4 g_localToWorld;
};

//
//	Functions
//
void main()
{
	vec4 worldPosition = VertexPosition * g_localToWorld;

	gl_Position		= worldPosition * g_worldToProjected;
	WorldPosition	= worldPosition.xyz;
	UV				= VertexUV;
	Normal			= VertexNormal * mat3x3(g_localToWorld);
}
