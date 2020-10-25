#version 300 es

precision mediump float;

layout(std140) uniform VSConstants2D
{
	vec4 g_transform[2];
	vec4 g_colorMul;
};

//
// VSInput
//
layout(location = 0) in vec2 VertexPosition;
layout(location = 1) in vec2 VertexUV;
layout(location = 2) in vec4 VertexColor;

//
// VSOutput
//
out vec4 Color;
out vec2 UV;
// out vec4 Position;

vec4 StandardTransform(const vec2 pos)
{
	vec4 result;
	result.xy = g_transform[0].zw + pos.x * g_transform[0].xy + pos.y * g_transform[1].xy;
	result.zw = g_transform[1].zw;
	return result;
}

void main()
{
	gl_Position = StandardTransform(VertexPosition);

	Color = (VertexColor * g_colorMul);
	
	UV = VertexUV;
}
