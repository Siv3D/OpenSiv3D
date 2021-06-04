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

# include <Siv3D/Quaternion.hpp>
# include <Siv3D/Mat4x4.hpp>

namespace s3d
{
	Quaternion::Quaternion(const Mat4x4& m) noexcept
		: value{ DirectX::XMQuaternionRotationMatrix(m) } {}

	Quaternion Quaternion::Rotate(const Mat4x4& m) noexcept
	{
		return DirectX::XMQuaternionRotationMatrix(m);
	}
}
