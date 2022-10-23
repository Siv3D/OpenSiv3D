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
//	Functions
//
@fragment
fn main(
	@builtin(position) Position: vec4<f32>,
	@location(0) Color: vec4<f32>,
	@location(1) UV: vec2<f32>
) -> @location(0) vec4<f32> 
{
	var tr: f32 = UV.y;
	var d: f32 = abs(UV.x % 3.0 - 1.0);
	var range: f32 = 1.0 - tr;
	var color: vec4<f32> = Color;

	if (d < range)
	{
		color.a = color.a * 1.0;
	} 
	else if (d < 1.0)
	{
		color.a = color.a * (1.0 - d) / tr;
	}
	else
	{
		color.a = 0.0;
	}

	return (color + PSConstants2D.colorAdd);
}
