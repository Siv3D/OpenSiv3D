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
var<uniform> PSConstants2D : PSConstants2DStruct;

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
	var t: f32 = UV.x % 2.0;
	var tex: vec2<f32> = UV;
	tex.x = abs(1.0 - t) * 2.0;
	var color : vec4<f32> = Color;

	var dist: f32 = dot(tex, tex) * 0.5;
	var delta: f32 = fwidth(dist);
	var alpha: f32 = smoothstep(0.5 - delta, 0.5, dist);
	color.a = color.a * (1.0 - alpha);

	return (color + PSConstants2D.colorAdd);
}
