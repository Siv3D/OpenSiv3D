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
) -> @location(0) vec2<f32> 
{
	var size: vec2<f32> = vec2<f32>(textureDimensions(Texture0, 0));
	var offset: vec2<f32> = vec2<f32>(1.0, 1.0) / size;

	var n: f32 = textureSample(Texture0, Sampler0, UV + vec2<f32>(0.0, -offset.y)).r;
	var s: f32 = textureSample(Texture0, Sampler0, UV + vec2<f32>(0.0,  offset.y)).r;
	var w: f32 = textureSample(Texture0, Sampler0, UV + vec2<f32>(-offset.x, 0.0)).r;
	var e: f32 = textureSample(Texture0, Sampler0, UV + vec2<f32>( offset.x, 0.0)).r;

	var normal: vec3<f32> = normalize(vec3<f32>(w - e, 2.0, s - n));

	return normal.xz;
}
