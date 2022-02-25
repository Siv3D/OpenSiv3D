# version 300 es

//	Copyright (c) 2008-2022 Ryo Suzuki.
//	Copyright (c) 2016-2022 OpenSiv3D Project.
//	Licensed under the MIT License.

precision mediump float;

//
//	PSInput
//
in vec3 WorldPosition;
in vec4 Color;

//
//	PSOutput
//
layout(location = 0) out vec4 FragColor;

//
//	Functions
//
void main()
{
	FragColor = Color;
}
