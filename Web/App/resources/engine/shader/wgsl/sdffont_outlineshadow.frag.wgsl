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
[[stage(fragment)]]
fn main(
	[[builtin(position)]] Position: vec4<f32>,
	[[location(0)]] Color: vec4<f32>,
	[[location(1)]] UV: vec2<f32>
) -> [[location(0)]] vec4<f32> 
{
	var d: f32 = textureSample(Texture0, Sampler0, UV).a;

	var od: f32 = (d - PSConstants2D.sdfParam.y);
	var outlineAlpha: f32 = clamp(od / fwidth(od) + 0.5, 0.0, 1.0);

	var td: f32 = (d - PSConstants2D.sdfParam.x);
	var textAlpha: f32 = clamp(td / fwidth(td) + 0.5, 0.0, 1.0);

	var baseAlpha: f32 = (outlineAlpha - textAlpha);

	var textColor: vec4<f32> = vec4<f32>
	(
		mix(PSConstants2D.sdfOutlineColor.rgb, Color.rgb, textAlpha),
		baseAlpha * PSConstants2D.sdfOutlineColor.a + textAlpha * Color.a
	);

	var size: vec2<f32> = vec2<f32>(textureDimensions(Texture0, 0));
	var shadowOffset: vec2<f32> = (PSConstants2D.sdfParam.zw / size);
	var d2: f32 = textureSample(Texture0, Sampler0, UV - shadowOffset).a;

	var sd: f32 = (d2 - PSConstants2D.sdfParam.y);
	var shadowAlpha: f32 = clamp(sd / fwidth(sd) + 0.5, 0.0, 1.0);
	var sBase: f32 = shadowAlpha * (1.0 - textColor.a);

	var color: vec4<f32>;
	if (textColor.a == 0.0)
	{
		color = vec4<f32>(PSConstants2D.sdfShadowColor.rgb, 1.0);
	}
	else
	{
		color = vec4<f32>(mix(textColor.rgb, PSConstants2D.sdfShadowColor.rgb, sBase), 1.0);
	}
	color.a = (sBase * PSConstants2D.sdfShadowColor.a) + textColor.a;

	return (color + PSConstants2D.colorAdd);
}
