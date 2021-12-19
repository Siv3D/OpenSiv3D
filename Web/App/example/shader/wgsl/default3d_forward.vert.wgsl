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
   	[[location(1)]] UV: vec2<f32>;
   	[[location(2)]] Normal: vec3<f32>;
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
	[[location(0)]] VertexPosition: vec3<f32>,
	[[location(1)]] VertexNormal: vec3<f32>,
	[[location(2)]] VertexUV: vec2<f32>,
) -> VertexOutput
{
	var output: VertexOutput;
	var worldPosition: vec4<f32> = vec4<f32>(VertexPosition, 1.0) * VSPerObject.localToWorld;

	output.Position			= worldPosition * VSPerView.worldToProjected;
	output.WorldPosition	= worldPosition.xyz;
	output.UV				= VertexUV;
	output.Normal			= (vec4<f32>(VertexNormal, 0.0) * VSPerObject.localToWorld).xyz;

	return output;
}
