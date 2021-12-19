# version 300 es

//	Copyright (c) 2008-2021 Ryo Suzuki.
//	Copyright (c) 2016-2021 OpenSiv3D Project.
//	Licensed under the MIT License.

precision mediump float;


//
//	Textures
//
uniform sampler2D Texture0;

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


//
//	Constant Buffer
//
layout(std140) uniform VSPerView // slot 1
{
	mat4x4 g_worldToProjected;
};

layout(std140) uniform VSPerObject // slot 2
{
	mat4x4 g_localToWorld;
};

//
//	Functions
//
void main()
{
	float height = texture(Texture8, VertexUV).r;
	vec4 pos = vec4(VertexPosition.x, height, VertexPosition.zw);
	vec4 worldPosition = pos * g_localToWorld;

	gl_Position		= worldPosition * g_worldToProjected;
	WorldPosition	= worldPosition.xyz;
	UV				= VertexUV;
}
