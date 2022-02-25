#version 300 es

//	Copyright (c) 2008-2022 Ryo Suzuki.
//	Copyright (c) 2016-2022 OpenSiv3D Project.
//	Licensed under the MIT License.

//
// VSOutput
//
out vec2 UV;
				
void main()
{
	float x = -1.0 + float((gl_VertexID & 1) << 2);
	float y = -1.0 + float((gl_VertexID & 2) << 1);
	gl_Position = vec4(x, y, 0, 1);
	
	UV.x = (x + 1.0) * 0.5;
	UV.y = (-y + 1.0) * 0.5;
}
