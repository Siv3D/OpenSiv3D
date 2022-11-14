//	Copyright (c) 2008-2022 Ryo Suzuki.
//	Copyright (c) 2016-2022 OpenSiv3D Project.
//	Licensed under the MIT License.

//
//	Textures
//
@group(2) @binding(0) var Sampler0: sampler;
@group(2) @binding(1) var Texture0: texture_2d<f32>;

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

fn ApplySRGBCurve_Fast(x: f32) -> f32
{
	if (x < 0.0031308) 
	{ 
		return 12.92 * x;
	}
	
	return 1.13005 * sqrt(x - 0.00228) - 0.13448 * x + 0.005719;
}

fn ApplySRGBCurve(x: f32) -> f32
{
	if (x < 0.0031308)
	{ 
		return 12.92 * x;
	}
	
	return 1.055 * pow(x, 1.0 / 2.4) - 0.055;
}

fn ApplySRGBCurve0(color: vec3<f32>) -> vec3<f32>
{
	return pow(color, vec3<f32>(1.0 / 2.2));
}

fn ApplySRGBCurve1(color: vec3<f32>) -> vec3<f32>
{
	var r: f32 = ApplySRGBCurve_Fast(color.r);
	var g: f32 = ApplySRGBCurve_Fast(color.g);
	var b: f32 = ApplySRGBCurve_Fast(color.b);
	return vec3<f32>(r, g, b);	
}

fn ApplySRGBCurve2(color: vec3<f32>) -> vec3<f32>
{
	var r: f32 = ApplySRGBCurve(color.r);
	var g: f32 = ApplySRGBCurve(color.g);
	var b: f32 = ApplySRGBCurve(color.b);
	return vec3<f32>(r, g, b);	
}

//
//	Functions
//
@fragment
fn main(
	@builtin(position) Position: vec4<f32>,
	@location(0) Color: vec4<f32>,
	@location(1) UV: vec2<f32>
) -> @location(0) vec4<f32> 
{
	var texColor: vec3<f32> = textureSample(Texture0, Sampler0, UV).rgb;

	return vec4<f32>(ApplySRGBCurve2(texColor), 1.0);
}
