#version 410

layout(std140) uniform PSConstants2D
{
	vec4 g_colorAdd;
	vec4 g_sdfParam;
	vec4 g_internal;	
};

//
// PSInput
//
layout(location = 0) in vec4 Color;

//
// PSOutput
//
layout(location = 0) out vec4 FragColor;
		
void main()
{
	FragColor = Color + g_colorAdd;
}
