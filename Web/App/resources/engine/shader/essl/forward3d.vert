#version 300 es

//	Copyright (c) 2008-2021 Ryo Suzuki.
//	Copyright (c) 2016-2021 OpenSiv3D Project.
//	Licensed under the MIT License.

//
//	VSInput
//
layout(location = 0) in vec4 VertexPosition;
layout(location = 1) in vec3 VertexNormal;
layout(location = 2) in vec2 VertexUV;

//
//	VSOutput
//
out vec3 WorldPosition;
out vec2 UV;
out vec3 Normal;

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
