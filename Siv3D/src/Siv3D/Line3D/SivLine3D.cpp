//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2021 Ryo Suzuki
//	Copyright (c) 2016-2021 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# include <Siv3D/Line3D.hpp>
# include <Siv3D/Mat4x4.hpp>
# include <Siv3D/Graphics2D.hpp>

namespace s3d
{
	Line3D Line3D::toScreen(const Mat4x4& vp) const noexcept
	{
		constexpr size_t vertexCount = 2;
		Float3 vertices[vertexCount] = { begin, end };
		DirectX::XMVector3TransformCoordStream(
			reinterpret_cast<DirectX::XMFLOAT3*>(vertices),
			sizeof(Float3),
			reinterpret_cast<const DirectX::XMFLOAT3*>(vertices),
			sizeof(Float3), vertexCount, vp);

		const Float2 resolution = Graphics2D::GetRenderTargetSize();

		for (auto& v : vertices)
		{
			v.x += 1.0f;
			v.y += 1.0f;
			v.x *= 0.5f * resolution.x;
			v.y *= 0.5f;
			v.y = 1.0f - v.y;
			v.y *= resolution.y;
		}

		return{ vertices[0], vertices[1] };
	}

	Line Line3D::toScreenLine(const Mat4x4& vp) const noexcept
	{
		const Line3D line = toScreen(vp);

		return{ line.begin.xy(), line.end.xy() };
	}
}
