#version 410
				
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
layout(location = 0) out vec4 Color;
layout(location = 1) out vec2 UV;
out gl_PerVertex
{
	vec4 gl_Position;
};

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

	Color = VertexColor * g_colorMul;
	
	UV = VertexUV;
}
