//	Copyright (c) 2008-2025 Ryo Suzuki.
//	Copyright (c) 2016-2025 OpenSiv3D Project.
//	Licensed under the MIT License.

# version 410

//
//	Textures
//
uniform sampler2D Texture0;

//
//	PSInput
//
layout(location = 0) in vec4 Color;
layout(location = 1) in vec2 UV;

//
//	PSOutput
//
layout(location = 0) out vec4 FragColor;

//
//	Functions
//

//
//	https://github.com/microsoft/DirectX-Graphics-Samples/blob/master/MiniEngine/Core/Shaders/ColorSpaceUtility.hlsli
// 
//	Copyright(c) 2015 Microsoft
//
//	Permission is hereby granted, free of charge, to any person obtaining a copy
//	of this software and associated documentation files(the "Software"), to deal
//	in the Software without restriction, including without limitation the rights
//	to use, copy, modify, merge, publish, distribute, sublicense, and / or sell
//	copies of the Software, and to permit persons to whom the Software is
//	furnished to do so, subject to the following conditions :
//
//	The above copyright notice and this permission notice shall be included in
//	all copies or substantial portions of the Software.
//
//	THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
//	IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
//	FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL THE
//	AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
//	LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
//	OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
//	THE SOFTWARE.
float ApplySRGBCurve_Fast(float x)
{
	return x < 0.0031308f ? 12.92f * x : 1.13005f * sqrt(x - 0.00228f) - 0.13448f * x + 0.005719f;
}

float ApplySRGBCurve(float x)
{
	return x < 0.0031308f ? 12.92f * x : 1.055f * pow(x, 1.0f / 2.4f) - 0.055f;
}

vec3 ApplySRGBCurve0(vec3 color)
{
	return pow(color, vec3(1.0f / 2.2f));
}

vec3 ApplySRGBCurve1(vec3 color)
{
	float r = ApplySRGBCurve_Fast(color.r);
	float g = ApplySRGBCurve_Fast(color.g);
	float b = ApplySRGBCurve_Fast(color.b);
	return vec3(r, g, b);	
}

vec3 ApplySRGBCurve2(vec3 color)
{
	float r = ApplySRGBCurve(color.r);
	float g = ApplySRGBCurve(color.g);
	float b = ApplySRGBCurve(color.b);
	return vec3(r, g, b);	
}

void main()
{
	vec3 texColor = texture(Texture0, UV).rgb;

	FragColor = vec4(ApplySRGBCurve2(texColor), 1.0f);
}
