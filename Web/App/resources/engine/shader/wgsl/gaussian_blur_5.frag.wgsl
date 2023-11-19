//	Copyright (c) 2008-2023 Ryo Suzuki.
//	Copyright (c) 2016-2023 OpenSiv3D Project.
//	Licensed under the MIT License.

//
//	Constant Buffer
//
struct PSConstants2DStruct
{
	colorAdd: vec4<f32>,
	sdfParam: vec4<f32>,
	sdfOutlineColor: vec4<f32>,
	sdfShadowColor: vec4<f32>,
	pixelSize: vec2<f32>,
	direction: vec2<f32>,
};

@group(1) @binding(0)
var<uniform> PSConstants2D: PSConstants2DStruct;

//
//	Textures
//
@group(2) @binding(0) var Sampler0: sampler;
@group(2) @binding(1) var Texture0: texture_2d<f32>;

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
	var offset1: vec2<f32> = (1.33333333333333 * PSConstants2D.direction);

	var color: vec4<f32> = (textureSample(Texture0, Sampler0, UV) * 0.294117647058824);
	color = (color + textureSample(Texture0, Sampler0, UV + (offset1 * PSConstants2D.pixelSize)) * 0.352941176470588);
	color = (color + textureSample(Texture0, Sampler0, UV - (offset1 * PSConstants2D.pixelSize)) * 0.352941176470588);

	return color;
}
