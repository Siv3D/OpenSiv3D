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

# include <Siv3D/BasicCamera3D.hpp>

namespace s3d
{
	Float3 BasicCamera3D::screenToWorldPoint(const Float2& pos, const float depth) const noexcept
	{
		Float3 v{ pos, depth };
		v.x /= (m_sceneSize.x * 0.5f);
		v.y /= (m_sceneSize.y * 0.5f);
		v.x -= 1.0f;
		v.y -= 1.0f;
		v.y *= -1.0f;

		const SIMD_Float4 worldPos = DirectX::XMVector3TransformCoord(SIMD_Float4{ v, 0.0f }, m_invViewProj);

		return worldPos.xyz();
	}

	Ray BasicCamera3D::screenToRay(const Vec2& pos) const noexcept
	{
		const Vec3 rayEnd = screenToWorldPoint(pos, 0.000005f);

		return Ray{ m_eyePosition, (rayEnd - m_eyePosition).normalized() };
	}
}
