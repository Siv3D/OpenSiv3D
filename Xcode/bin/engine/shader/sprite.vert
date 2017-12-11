﻿#version 410
		
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
