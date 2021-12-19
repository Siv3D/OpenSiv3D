//	Copyright (c) 2008-2021 Ryo Suzuki.
//	Copyright (c) 2016-2021 OpenSiv3D Project.
//	Licensed under the MIT License.

//
//	VSOutput
//
struct VertexOutput
{
	[[builtin(position)]] Position: vec4<f32>;
	[[location(0)]] WorldPosition: vec3<f32>;
	[[location(1)]] Color: vec4<f32>;
};

//
//	Constant Buffer
//
[[block]] struct VSPerViewStruct
{
	worldToProjected: mat4x4<f32>;
};

[[group(0), binding(1)]]
var<uniform> VSPerView: VSPerViewStruct;

[[block]] struct VSPerObjectStruct
{
	localToWorld: mat4x4<f32>;
};

[[group(0), binding(2)]]
var<uniform> VSPerObject: VSPerObjectStruct;

//
//	Functions
//
[[stage(vertex)]]
fn main(
	[[location(0)]] VertexPosition: vec4<f32>,
	[[location(1)]] VertexColor: vec4<f32>
) -> VertexOutput
{
	var output: VertexOutput;
	var worldPosition: vec4<f32> = VertexPosition * VSPerObject.localToWorld;

	output.Position		= worldPosition * VSPerView.worldToProjected;
	output.WorldPosition	= worldPosition.xyz;
	output.Color			= VertexColor;

	return output;
}
