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

	var od: f32 = (d - PSConstants2D.sdfParam.y);
	var outlineAlpha: f32 = clamp(od * dot(msdfUnit, 0.5 / fwidth(UV)) + 0.5, 0.0, 1.0);

	var td: f32 = (d - PSConstants2D.sdfParam.x);
	var textAlpha: f32 = clamp(td * dot(msdfUnit, 0.5 / fwidth(UV)) + 0.5, 0.0, 1.0);

	var baseAlpha: f32 = (outlineAlpha - textAlpha);

	var color: vec4<f32> = vec4<f32>
	(
		mix(PSConstants2D.sdfOutlineColor.rgb, Color.rgb, textAlpha),
	    baseAlpha * PSConstants2D.sdfOutlineColor.a + textAlpha * Color.a
	);

	return (color + PSConstants2D.colorAdd);
}
