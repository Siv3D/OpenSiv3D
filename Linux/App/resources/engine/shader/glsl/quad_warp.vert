//	Copyright (c) 2008-2023 Ryo Suzuki.
//	Copyright (c) 2016-2023 OpenSiv3D Project.
//	Licensed under the MIT License.

# version 410

//
//	VSInput
//
layout(location = 0) in vec2 VertexPosition;
layout(location = 1) in vec2 VertexUV;
layout(location = 2) in vec4 VertexColor;

//
//	VSOutput
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

layout(std140) uniform VSQuadWarp
{
	mat3x3 g_homography;
};

vec2 Transform(vec2 pos, mat3x3 mat)
{
	float s = (mat[0][2] * pos.x + mat[1][2] * pos.y + mat[2][2]);
	float x = (mat[0][0] * pos.x + mat[1][0] * pos.y + mat[2][0]) / s;
	float y = (mat[0][1] * pos.x + mat[1][1] * pos.y + mat[2][1]) / s;
	return vec2(x, y);
}

//
//	Functions
//
void main()
{
	vec2 position = Transform(VertexPosition, g_homography);

	gl_Position = s3d_Transform2D(position, g_transform);

	Color = (VertexColor * g_colorMul);
	
	UV = position;
}
