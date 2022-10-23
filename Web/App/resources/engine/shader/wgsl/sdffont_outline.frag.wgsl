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
	unused: vec4<f32>,
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
	var d: f32 = textureSample(Texture0, Sampler0, UV).a;

	var od: f32 = (d - PSConstants2D.sdfParam.y);
	var outlineAlpha: f32 = clamp(od / fwidth(od) + 0.5, 0.0, 1.0);

	var td: f32 = (d - PSConstants2D.sdfParam.x);
	var textAlpha: f32 = clamp(td / fwidth(td) + 0.5, 0.0, 1.0);

	var baseAlpha: f32 = (outlineAlpha - textAlpha);

	var color: vec4<f32> = vec4<f32>
	(
		mix(PSConstants2D.sdfOutlineColor.rgb, Color.rgb, textAlpha),
		baseAlpha * PSConstants2D.sdfOutlineColor.a + textAlpha * Color.a
	);

	return (color + PSConstants2D.colorAdd);
}
