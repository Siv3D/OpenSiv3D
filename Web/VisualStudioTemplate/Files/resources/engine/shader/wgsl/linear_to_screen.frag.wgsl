//	Copyright (c) 2008-2022 Ryo Suzuki.
//	Copyright (c) 2016-2022 OpenSiv3D Project.
//	Licensed under the MIT License.

//
//	Textures
//
@group(1) @binding(0) var Sampler0: sampler;
@group(1) @binding(1) var Texture0: texture_2d<f32>;

//
//	Functions
//
fn Gamma(color: vec3<f32>, g: f32) -> vec3<f32>
{
	return pow(color, vec3<f32>(g));
}

@fragment
fn main(
	@builtin(position) Position: vec4<f32>,
	@location(0) Color: vec4<f32>,
	@location(1) UV: vec2<f32>
) -> @location(0) vec4<f32> 
{
	var texColor: vec3<f32> = textureSample(Texture0, Sampler0, UV).rgb;

	return vec4<f32>(Gamma(abs(texColor), (1.0f / 2.2f)), 1.0f);
}
