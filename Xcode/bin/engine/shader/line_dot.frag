#version 410
		
layout(location = 0) in vec4 Color;
layout(location = 1) in vec2 Tex;
		
layout(location = 0) out vec4 FragColor;
		
void main()
{
	FragColor = Color;
			
	float t = min(abs(1.5 - mod(Tex.x, 3.0)) * 1.7, 1.0);
			
	FragColor.a *= pow(t, 24);
}
