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

struct SoftShapeStruct
{
	t: f32;
};

@group(0) @binding(1)
var<uniform> SoftShape: SoftShapeStruct;

//
//	Functions
//
fn Circular(r: f32, theta: f32) -> vec2<f32>
{
	return vec2<f32>(sin(theta), -cos(theta)) * r;
}

@vertex
fn main(
	@builtin(vertex_index) VertexIndex: u32
) -> VertexOutput
{
	var output: VertexOutput;
	let PI: f32 = 3.14159265;

	output.Color = vec4<f32>(0.2, 0.7, 0.4, 1.0);
	output.UV = vec2<f32>(0.0, 0.0);

	var pos: vec2<f32>;

	if (VertexIndex % 3u == 0u)
	{
		pos = vec2<f32>(640.0, 360.0);
	}
	else
	{
		var angle: f32 = PI * (f32((VertexIndex / 3u) + ((VertexIndex % 3u) - 1u))) / 180.0;
		var r: f32 = 200.0
			+ cos((angle * 2.0) + sin(SoftShape.t * 1.5)) * 40.0
			+ sin((angle * 2.0) + sin(SoftShape.t * 2.0)) * 30.0
			+ cos((angle * 3.0) + sin(SoftShape.t * 3.5)) * 20.0
			+ sin((angle * 3.0) + sin(SoftShape.t * 4.0)) * 10.0;
		pos = vec2<f32>(640.0, 360.0) + Circular(r, angle);
		output.Color.a = (1.0 - r / 360.0);
	}

	output.Position = s3d_Transform2D(pos, VSConstants2D.transform0, VSConstants2D.transform1);

	return output;	
}
