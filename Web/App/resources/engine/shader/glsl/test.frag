#version 300 es

precision mediump float;

//
// PSInput
//
in vec4 Color;

//
// PSOutput
//
layout(location = 0) out vec4 FragColor;
		
void main()
{
	FragColor = Color;
}
