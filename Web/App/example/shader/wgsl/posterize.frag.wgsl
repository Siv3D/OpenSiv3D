//	Copyright (c) 2008-2021 Ryo Suzuki.
//	Copyright (c) 2016-2021 OpenSiv3D Project.
//	Licensed under the MIT License.

//
//	Textures
//
[[group(2), binding(0)]] var Sampler0: sampler;
[[group(2), binding(1)]] var Texture0: texture_2d<f32>;

//
//	Constant Buffer
//
[[block]] struct PSConstants2DStruct
{
	colorAdd: vec4<f32>;
	sdfParam: vec4<f32>;
	sdfOutlineColor: vec4<f32>;
	sdfShadowColor: vec4<f32>;
	unused: vec4<f32>;
};

[[group(1), binding(0)]]
var<uniform> PSConstants2D: PSConstants2DStruct;

//
//	Functions
//
[[stage(fragment)]]
fn main(
	[[builtin(position)]] Position: vec4<f32>,
	[[location(0)]] Color: vec4<f32>,
	[[location(1)]] UV: vec2<f32>
) -> [[location(0)]] vec4<f32> 
{
	var step: f32 = 4.0;

	var texColor: vec4<f32> = textureSample(Texture0, Sampler0, UV);

	texColor = vec4<f32>(round(texColor.rgb * step) / step, texColor.a);

	return (texColor * Color) + PSConstants2D.colorAdd;
}
