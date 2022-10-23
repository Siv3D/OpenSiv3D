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
@fragment
fn main(
	@builtin(position) Position: vec4<f32>,
	@location(0) Color: vec4<f32>,
	@location(1) UV: vec2<f32>
) -> @location(0) vec4<f32> 
{
	var ra: vec2<f32> = textureSample(Texture0, Sampler0, UV + vec2<f32>(-0.02, 0.0)).ra;
	var ga: vec2<f32> = textureSample(Texture0, Sampler0, UV).ga;
	var ba: vec2<f32> = textureSample(Texture0, Sampler0, UV + vec2<f32>( 0.02, 0.0)).ba;

	var a: f32 = (ra.y + ga.y + ba.y) / 3.0;
	var texColor: vec4<f32> = vec4<f32>(ra.x, ga.x, ba.x, a);	

	return (texColor * Color) + PSConstants2D.colorAdd;
}
