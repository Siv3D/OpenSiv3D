//	Copyright (c) 2008-2022 Ryo Suzuki.
//	Copyright (c) 2016-2022 OpenSiv3D Project.
//	Licensed under the MIT License.

//
//	Textures
//
@group(2) @binding(0) var Sampler0: sampler;
@group(2) @binding(1) var Texture0: texture_2d<f32>;

//
//	Constant Buffer
//
struct PSConstants2DStruct
{
	colorAdd: vec4<f32>,
	sdfParam: vec4<f32>,
	sdfOutlineColor: vec4<f32>,
	sdfShadowColor: vec4<f32>,
	unused: vec4<f32>,
};

@group(1) @binding(0)
var<uniform> PSConstants2D: PSConstants2DStruct;

//
//	Functions
//
fn ApplySRGBCurve_Fast(color: vec3<f32>) -> vec3<f32>
{
	return pow(color, vec3<f32>(1.0 / 2.2));
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

	var brightness: f32 = dot(texColor, vec3<f32>(0.2126, 0.7152, 0.0722));

	if (0.25 < brightness)
	{
		return vec4<f32>(ApplySRGBCurve_Fast(abs(texColor)) * 0.25, 1.0);
	}
	
	return vec4<f32>(0.0, 0.0, 0.0, 1.0);
}
