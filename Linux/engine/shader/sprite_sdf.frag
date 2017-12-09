#version 410
		
layout(location = 0) in vec4 Color;
layout(location = 1) in vec2 Tex;
		
uniform sampler2D Tex0;
		
layout(location = 0) out vec4 FragColor;
		
void main()
{
	float a = texture(Tex0, Tex).a;
	
	float MIN_EDGE_VALUE = 0.48;

	float MAX_EDGE_VALUE = 0.52;
	
	if (a < MIN_EDGE_VALUE)
	{
		a = 0.0;
	}
	else if (MAX_EDGE_VALUE < a)
	{
		a = 1.0;
	}
	else
	{
		a = smoothstep(MIN_EDGE_VALUE, MAX_EDGE_VALUE, a);
	}
	
	FragColor = vec4(Color.rgb, Color.a * a);
}
