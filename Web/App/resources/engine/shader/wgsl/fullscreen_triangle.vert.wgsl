//	Copyright (c) 2008-2022 Ryo Suzuki.
//	Copyright (c) 2016-2022 OpenSiv3D Project.
//	Licensed under the MIT License.

struct VertexOutput
{
	@builtin(position) Position: vec4<f32>,
   	@location(0) UV: vec2<f32>,
};

@vertex
fn main(
   @builtin(vertex_index) VertexIndex: u32,
) -> VertexOutput
{
	var output: VertexOutput;

	var x: f32 = -1.0 + f32((VertexIndex & 1u) << 2u);
	var y: f32 = -1.0 + f32((VertexIndex & 2u) << 1u);

	output.Position = vec4<f32>(x, y, 0.0, 1.0);
	output.UV = vec2<f32>(
		(x + 1.0) * 0.5,
		(-y + 1.0) * 0.5
	);

	return output;
}
