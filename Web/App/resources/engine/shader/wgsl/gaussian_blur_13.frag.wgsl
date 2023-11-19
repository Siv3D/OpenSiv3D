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
	var offset1: vec2<f32> = (1.41176470588235 * PSConstants2D.direction);
	var offset2: vec2<f32> = (3.29411764705882 * PSConstants2D.direction);
	var offset3: vec2<f32> = (5.17647058823529 * PSConstants2D.direction);

	var color: vec4<f32> = textureSample(Texture0, Sampler0, UV) * 0.196482550151140;
	color = (color + textureSample(Texture0, Sampler0, UV + (offset1 * PSConstants2D.pixelSize)) * 0.296906964672834);
	color = (color + textureSample(Texture0, Sampler0, UV - (offset1 * PSConstants2D.pixelSize)) * 0.296906964672834);
	color = (color + textureSample(Texture0, Sampler0, UV + (offset2 * PSConstants2D.pixelSize)) * 0.0944703978504473);
	color = (color + textureSample(Texture0, Sampler0, UV - (offset2 * PSConstants2D.pixelSize)) * 0.0944703978504473);
	color = (color + textureSample(Texture0, Sampler0, UV + (offset3 * PSConstants2D.pixelSize)) * 0.0103813624011481);
	color = (color + textureSample(Texture0, Sampler0, UV - (offset3 * PSConstants2D.pixelSize)) * 0.0103813624011481);

	return color;
}
