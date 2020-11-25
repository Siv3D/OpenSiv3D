#version 300 es

precision mediump float;

layout(std140) uniform PSConstants2D
{
	vec4 g_colorAdd;
	vec4 g_sdfParam;
	vec4 g_internal;	
};

//
// PSInput
//
in vec4 Color;

//
// PSOutput
//
layout(location = 0) out vec4 FragColor;
		
void main()
{
	FragColor = Color + g_colorAdd;
}
