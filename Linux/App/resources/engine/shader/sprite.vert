#version 410
		
layout(location = 0) in vec2 VertexPosition;
layout(location = 1) in vec2 VertexTex;
layout(location = 2) in vec4 VertexColor;
		
layout(location = 0) out vec4 Color;
layout(location = 1) out vec2 Tex;
out gl_PerVertex
{
	vec4 gl_Position;
};
		
layout(std140) uniform vscbSprite
{
	vec4 g_transform[2];
	vec4 g_colorMul;
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
	Color = VertexColor * g_colorMul;
	gl_Position = StandardTransform(VertexPosition);
	Tex = VertexTex;
}
