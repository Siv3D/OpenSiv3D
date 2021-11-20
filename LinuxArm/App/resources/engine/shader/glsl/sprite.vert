//	Copyright (c) 2008-2021 Ryo Suzuki.
//	Copyright (c) 2016-2021 OpenSiv3D Project.
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

//
//	Functions
//
void main()
{
	gl_Position = s3d_Transform2D(VertexPosition, g_transform);

	Color = (VertexColor * g_colorMul);
	
	UV = VertexUV;
}
