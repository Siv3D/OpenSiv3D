//	Copyright (c) 2008-2022 Ryo Suzuki.
//	Copyright (c) 2016-2022 OpenSiv3D Project.
//	Licensed under the MIT License.

//
//	VSOutput
//
struct VertexOutput
{
	@builtin(position) Position: vec4<f32>,
   	@location(0) Color: vec4<f32>,
   	@location(1) UV: vec2<f32>,
};

//
//	Siv3D Functions
//
fn s3d_Transform2D(pos: vec2<f32>, t0: vec4<f32>, t1: vec4<f32>) -> vec4<f32>
{
	return vec4<f32>(t0.zw + (pos.x * t0.xy) + (pos.y * t1.xy), t1.zw);
}

//
//	Constant Buffer
//
struct VSConstants2DStruct
{
	transform0: vec4<f32>,
	transform1: vec4<f32>,
    colorMul: vec4<f32>,
};

@group(0) @binding(0)
var<uniform> VSConstants2D: VSConstants2DStruct;

//
//	Functions
//
@vertex
fn main(
	@location(0) VertexPosition: vec2<f32>,
	@location(1) VertexUV: vec2<f32>,
	@location(2) VertexColor: vec4<f32>,
) -> VertexOutput
{
	var output: VertexOutput;

	output.Position = s3d_Transform2D(VertexPosition, VSConstants2D.transform0, VSConstants2D.transform1);

	output.Color = (VertexColor * VSConstants2D.colorMul);
	
	output.UV = VertexUV;

	return output;
}
