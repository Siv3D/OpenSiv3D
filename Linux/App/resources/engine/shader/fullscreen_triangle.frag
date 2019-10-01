#version 410

uniform sampler2D Texture0;

//
// PSInput
//
layout(location = 0) in vec2 UV;
		
//
// PSOutput
//
layout(location = 0) out vec4 FragColor;

void main()
{
	FragColor = texture(Texture0, UV);
}
