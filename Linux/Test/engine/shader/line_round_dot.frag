#version 410
		
layout(location = 0) in vec4 Color;
layout(location = 1) in vec2 Tex;
		
layout(location = 0) out vec4 FragColor;
		
void main()
{
	FragColor = Color;
			
	float t = mod(Tex.x, 2.0);
			
	t = abs(1.0 - t) * 2.0;
			
	FragColor.a *= 1.0 - clamp(pow(dot(vec2(t, Tex.y), vec2(t, Tex.y)), 12), 0.0, 1.0);
}
