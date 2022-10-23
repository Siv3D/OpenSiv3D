//	Copyright (c) 2008-2022 Ryo Suzuki.
//	Copyright (c) 2016-2022 OpenSiv3D Project.
//	Licensed under the MIT License.

//
//	Functions
//
@fragment
fn main(
	@builtin(position) Position: vec4<f32>,
	@location(0) WorldPosition: vec3<f32>,
	@location(1) Color: vec4<f32>
) -> @location(0) vec4<f32>
{
	return Color;
}
