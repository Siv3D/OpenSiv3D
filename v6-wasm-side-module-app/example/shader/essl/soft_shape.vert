# version 300 es

//	Copyright (c) 2008-2022 Ryo Suzuki.
//	Copyright (c) 2016-2022 OpenSiv3D Project.
//	Licensed under the MIT License.

//
//	VS Input (nothing)
//

//
//	VS Output
//
out vec4 Color;
out vec2 UV;

//
//	Siv3D Functions
//
vec4 s3d_Transform2D(const vec2 pos, const vec4 t[2])
{
	return vec4(t[0].zw + (pos.x * t[0].xy) + (pos.y * t[1].xy), t[1].zw);
}

//
//	Constant Buffer
//
layout(std140) uniform VSConstants2D
{
	vec4 g_transform[2];
	vec4 g_colorMul;
};

layout(std140) uniform SoftShape
{
	float g_t;
};

//
//	Functions
//
vec2 Circular(float r, float theta)
{
	return vec2(sin(theta), -cos(theta)) * r;
}

void main()
{
	Color = vec4(0.2f, 0.7f, 0.4f, 1.0f);
	UV = vec2(0.0f, 0.0f);

	vec2 pos;

	if (gl_VertexID % 3 == 0)
	{
		pos = vec2(640.0f, 360.0f);
	}
	else
	{
		float angle = radians(float((gl_VertexID / 3) + ((gl_VertexID % 3) - 1)));
		float r = 200.0f
			+ cos((angle * 2.0f) + sin(g_t * 1.5f)) * 40.0f
			+ sin((angle * 2.0f) + sin(g_t * 2.0f)) * 30.0f
			+ cos((angle * 3.0f) + sin(g_t * 3.5f)) * 20.0f
			+ sin((angle * 3.0f) + sin(g_t * 4.0f)) * 10.0f;
		pos = vec2(640.0f, 360.0f) + Circular(r, angle);
		Color.a = (1.0f - r / 360.0f);
	}

	gl_Position = s3d_Transform2D(pos, g_transform);	
}
