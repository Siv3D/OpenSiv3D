//	Copyright (c) 2008-2022 Ryo Suzuki.
//	Copyright (c) 2016-2022 OpenSiv3D Project.
//	Licensed under the MIT License.

# version 410

//
//	VS Input (nothing)
//

//
//	VS Output
//
layout(location = 0) out vec4 Color;
layout(location = 1) out vec2 UV;
out gl_PerVertex
{
	vec4 gl_Position;
};

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
	Color = vec4(0.2, 0.7, 0.4, 1);
	UV = vec2(0, 0);

	vec2 pos;

	if (gl_VertexID % 3 == 0)
	{
		pos = vec2(640, 360);
	}
	else
	{
		float angle = radians((gl_VertexID / 3) + ((gl_VertexID % 3) - 1));
		float r = 200
			+ cos((angle * 2) + sin(g_t * 1.5)) * 40
			+ sin((angle * 2) + sin(g_t * 2.0)) * 30
			+ cos((angle * 3) + sin(g_t * 3.5)) * 20
			+ sin((angle * 3) + sin(g_t * 4.0)) * 10;
		pos = vec2(640, 360) + Circular(r, angle);
		Color.a = (1.0 - r / 360.0);
	}

	gl_Position = s3d_Transform2D(pos, g_transform);	
}
