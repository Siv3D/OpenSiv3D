#version 410

//
// VSOutput
//
layout(location = 0) out vec2 UV;
				
void main()
{
	float x = -1.0 + float((gl_VertexID & 1) << 2);
	float y = -1.0 + float((gl_VertexID & 2) << 1);
	gl_Position = vec4(x, y, 0, 1);
	
	UV.x = (x + 1.0) * 0.5;
	UV.y = (-y + 1.0) * 0.5;
}
