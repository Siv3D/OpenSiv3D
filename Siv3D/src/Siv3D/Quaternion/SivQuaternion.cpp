//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2022 Ryo Suzuki
//	Copyright (c) 2016-2022 OpenSiv3D Project
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

	std::pair<Float3, float> Quaternion::toAxisAngle() const noexcept
	{
		SIMD_Float4 axis;
		float angle;
		DirectX::XMQuaternionToAxisAngle(&axis.vec, &angle, value);

		return{ axis.xyz(), angle };
	}

	Quaternion Quaternion::Rotate(const Mat4x4& m) noexcept
	{
		return DirectX::XMQuaternionRotationMatrix(m);
	}

	Quaternion Quaternion::FromUnitVectors(const Vec3& from, const Vec3& to) noexcept
	{
		Vec4 q;

		if (const double r = (from.dot(to) + 1.0);
			(r < 0.0000001))
		{
			if (std::abs(from.z) < std::abs(from.x))
			{
				q.x = -from.y;
				q.y = from.x;
				q.z = 0.0;
				q.w = 0.0;
			}
			else
			{
				q.x = 0.0;
				q.y = -from.z;
				q.z = from.y;
				q.w = 0.0;
			}
		}
		else
		{
			q = Vec4{ from.cross(to), r };
		}

		return Quaternion{ q.normalized() };
	}

	Quaternion Quaternion::FromUnitVectorPairs(const std::pair<Vec3, Vec3>& from, const std::pair<Vec3, Vec3>& to) noexcept
	{
		// https://stackoverflow.com/questions/19445934/quaternion-from-two-vector-pairs
		// https://robokitchen.tumblr.com/post/67060392720/finding-a-quaternion-from-two-pairs-of-vectors

		const Vec3 u0 = from.first;
		const Vec3 v0 = from.second;

		const Vec3 u2 = to.first;
		const Vec3 v2 = to.second;

		const Quaternion q2 = Quaternion::FromUnitVectors(u0, u2);
		const Vec3 v1 = v2 * q2.conjugated();
		const Vec3 v0_proj = v0.projectOnPlane(u0);
		const Vec3 v1_proj = v1.projectOnPlane(u0);

		double angleInPlane = v0_proj.angleTo(v1_proj);

		if (v1_proj.dot(u0.cross(v0)) < 0.0)
		{
			angleInPlane *= -1;
		}

		const Quaternion q1 = Quaternion::RotationAxis(u0, angleInPlane);
		
		return (q1 * q2);
	}

	void Formatter(FormatData& formatData, const Quaternion& value)
	{
		Formatter(formatData, value.value);
	}
}
