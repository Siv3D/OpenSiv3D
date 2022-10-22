//	Copyright (c) 2008-2022 Ryo Suzuki.
//	Copyright (c) 2016-2022 OpenSiv3D Project.
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
	//
	// http://rastergrid.com/blog/2010/09/efficient-gaussian-blur-with-linear-sampling/
	//
	var offset1: vec2<f32> = 1.38461538461538 * PSConstants2D.direction;
	var offset2: vec2<f32> = 3.23076923076923 * PSConstants2D.direction;

	var color: vec4<f32> = textureSample(Texture0, Sampler0, UV) * 0.227027027027027;
	color = color + textureSample(Texture0, Sampler0, UV + (offset1 * PSConstants2D.pixelSize)) * 0.316216216216216;
	color = color + textureSample(Texture0, Sampler0, UV - (offset1 * PSConstants2D.pixelSize)) * 0.316216216216216;
	color = color + textureSample(Texture0, Sampler0, UV + (offset2 * PSConstants2D.pixelSize)) * 0.070270270270270;
	color = color + textureSample(Texture0, Sampler0, UV - (offset2 * PSConstants2D.pixelSize)) * 0.070270270270270;

	return color;
}
