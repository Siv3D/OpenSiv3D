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

// PS_1
struct SwirlStruct
{
	angle: f32;
};

@group(1) @binding(1)
var<uniform> Swirl: SwirlStruct;
// [C++]
//struct Swirl
//{
//	float angle;
//};

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
	var uv: vec2<f32> = UV - vec2<f32>(0.5, 0.5);

	var distanceFromCenter: f32 = length(uv);

	var angle: f32 = distanceFromCenter * Swirl.angle;

	var c: f32 = cos(angle);
	var s: f32 = sin(angle);

	uv = mat2x2<f32>(c, -s, s, c) * uv + vec2<f32>(0.5, 0.5);

	var texColor: vec4<f32> = textureSample(Texture0, Sampler0, uv);

	return (texColor * Color) + PSConstants2D.colorAdd;
}
