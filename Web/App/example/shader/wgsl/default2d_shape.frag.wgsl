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
//	Functions
//
[[stage(fragment)]]
fn main(
	[[builtin(position)]] Position: vec4<f32>,
	[[location(0)]] Color: vec4<f32>,
	[[location(1)]] UV: vec2<f32>
) -> [[location(0)]] vec4<f32> 
{
	return (Color + PSConstants2D.colorAdd);
}
