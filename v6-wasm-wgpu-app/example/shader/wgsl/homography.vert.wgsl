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

struct VSHomographyStruct
{
	homography: mat3x3<f32>,
};

@group(0) @binding(1)
var<uniform> VSHomography: VSHomographyStruct;

//
//	Functions
//
fn Transform(pos: vec3<f32>, mat: mat3x3<f32>) -> vec2<f32>
{
	var s: f32 = (mat[0][2] * pos.x + mat[1][2] * pos.y + mat[2][2]);
	var x: f32 = (mat[0][0] * pos.x + mat[1][0] * pos.y + mat[2][0]) / s;
	var y: f32 = (mat[0][1] * pos.x + mat[1][1] * pos.y + mat[2][1]) / s;
	return vec2<f32>(x, y);
}

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
	var pos: vec2<f32> = Transform(VertexPosition, VSHomography.homography);
	var output: VertexOutput;

	output.Position = s3d_Transform2D(pos, VSConstants2D.transform0, VSConstants2D.transform1);

	output.Color = (VertexColor * VSConstants2D.colorMul);
	
	output.UV = pos;
}
