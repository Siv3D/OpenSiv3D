//	Copyright (c) 2008-2021 Ryo Suzuki.
//	Copyright (c) 2016-2021 OpenSiv3D Project.
//	Licensed under the MIT License.

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
//	Textures
//
[[group(2), binding(0)]] var Sampler0: sampler;
[[group(2), binding(1)]] var Texture0: texture_2d<f32>;

//
//	Functions
//
fn median(r: f32, g: f32, b: f32) -> f32
{
	return max(min(r, g), min(max(r, g), b));
}

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
	var size: vec2<f32> = vec2<f32>(textureDimensions(Texture0, 0));
	var pxRange: f32 = 4.0;
	var msdfUnit: vec2<f32> = (pxRange / size);

	var s: vec3<f32> = textureSample(Texture0, Sampler0, UV).rgb;
	var d: f32 = median(s.r, s.g, s.b);

	var td: f32 = (d - 0.5);
	var textAlpha: f32 = clamp(td * dot(msdfUnit, 0.5 / fwidth(UV)) + 0.5, 0.0, 1.0);

	var shadowOffset: vec2<f32> = vec2<f32>(0.875, 0.875) / size;
	var s2: vec3<f32> = textureSample(Texture0, Sampler0, UV - shadowOffset).rgb;
	var d2: f32 = median(s2.r, s2.g, s2.b);
	var sd: f32 = (d2 - 0.5);
	var shadowAlpha: f32 = sqrt(clamp(sd * dot(msdfUnit, 0.5 / fwidth(UV)) + 0.5, 0.0, 1.0));

	return vec4<f32>(textAlpha, textAlpha, textAlpha, max(textAlpha, shadowAlpha));
}
