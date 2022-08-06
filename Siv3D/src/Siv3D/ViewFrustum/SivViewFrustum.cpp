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

# include <Siv3D/ViewFrustum.hpp>
# include <Siv3D/SIMD_Float4.hpp>
# include <Siv3D/Quaternion.hpp>
# include <Siv3D/Spherical.hpp>
# include <Siv3D/Line3D.hpp>
# include <Siv3D/Geometry3D.hpp>

namespace s3d
{
	namespace detail
	{
		constexpr std::array<size_t, 8> CornerIndices =
		{
			0, 1, 3, 2, 4, 5, 7, 6
		};
	}

	ViewFrustum::ViewFrustum(const BasicCamera3D& camera, const double farClip) noexcept
		: ViewFrustum{ camera.getSceneSize(), camera.getVerticalFOV(), camera.getEyePosition(), camera.getFocusPosition(), camera.getUpDirection(), camera.getNearClip(), farClip } {}

	ViewFrustum::ViewFrustum(const BasicCamera3D& camera, const double nearClip, const double farClip) noexcept
		: ViewFrustum{ camera.getSceneSize(), camera.getVerticalFOV(), camera.getEyePosition(), camera.getFocusPosition(), camera.getUpDirection(), nearClip, farClip } {}

	ViewFrustum::ViewFrustum(const Size& sceneSize, const double verticalFOV, const Vec3& eyePosition, const Vec3& focusPosition, const Vec3& upDirection, const double nearClip, const double farClip) noexcept
	{
		const auto proj = DirectX::XMMatrixPerspectiveFovLH(
			static_cast<float>(verticalFOV),
			(static_cast<float>(sceneSize.x) / sceneSize.y),
			static_cast<float>(nearClip),
			static_cast<float>(farClip));

		DirectX::BoundingFrustum::CreateFromMatrix(m_frustum, proj);
		m_frustum.Origin = DirectX::XMFLOAT3{ static_cast<float>(eyePosition.x), static_cast<float>(eyePosition.y), static_cast<float>(eyePosition.z) };

		const Quaternion q = Quaternion::FromUnitVectorPairs(
			{ Vec3::Forward(), Vec3::Up() }, { (focusPosition - eyePosition).normalized(), upDirection });

		const Float4 o = q.toFloat4();

		m_frustum.Orientation = { o.x, o.y, o.z, o.w };
	}

	std::array<Vec3, 8> ViewFrustum::getCorners() const noexcept
	{
		std::array<DirectX::XMFLOAT3, 8> corners;

		m_frustum.GetCorners(corners.data());

		std::array<Vec3, 8> results;

		for (size_t i = 0; i < 8; ++i)
		{
			const auto& corner = corners[detail::CornerIndices[i]];

			results[i].set(corner.x, corner.y, corner.z);
		}

		return results;
	}

	bool ViewFrustum::intersects(const Vec3& point) const noexcept
	{
		const auto result = m_frustum.Contains(SIMD_Float4{ point, 0.0f });

		return (result == DirectX::ContainmentType::CONTAINS);
	}

	bool ViewFrustum::intersects(const Triangle3D& triangle) const noexcept
	{
		return m_frustum.Intersects(triangle.p0, triangle.p1, triangle.p2);
	}

	bool ViewFrustum::intersects(const Sphere& sphere) const noexcept
	{
		return m_frustum.Intersects(detail::FromSphere(sphere));
	}

	bool ViewFrustum::intersects(const Box& box) const noexcept
	{
		return m_frustum.Intersects(detail::FromBox(box));
	}

	bool ViewFrustum::intersects(const OrientedBox& box) const noexcept
	{
		return m_frustum.Intersects(detail::FromOrientedBox(box));
	}

	bool ViewFrustum::intersects(const ViewFrustum& frustum) const noexcept
	{
		return m_frustum.Intersects(frustum.getData());
	}

	Optional<float> ViewFrustum::intersects(const Ray& ray) const noexcept
	{
		return ray.intersects(*this);
	}

	bool ViewFrustum::contains(const Vec3& point) const noexcept
	{
		return intersects(point);
	}

	bool ViewFrustum::contains(const Triangle3D& triangle) const noexcept
	{
		const auto result = m_frustum.Contains(triangle.p0, triangle.p1, triangle.p2);

		return (result == DirectX::ContainmentType::CONTAINS);
	}

	bool ViewFrustum::contains(const Sphere& sphere) const noexcept
	{
		const auto result = m_frustum.Contains(detail::FromSphere(sphere));

		return (result == DirectX::ContainmentType::CONTAINS);
	}

	bool ViewFrustum::contains(const Box& box) const noexcept
	{
		const auto result = m_frustum.Contains(detail::FromBox(box));

		return (result == DirectX::ContainmentType::CONTAINS);
	}

	bool ViewFrustum::contains(const OrientedBox& box) const noexcept
	{
		const auto result = m_frustum.Contains(detail::FromOrientedBox(box));

		return (result == DirectX::ContainmentType::CONTAINS);
	}

	bool ViewFrustum::contains(const ViewFrustum& frustum) const noexcept
	{
		const auto result = m_frustum.Contains(frustum.getData());

		return (result == DirectX::ContainmentType::CONTAINS);
	}
	
	Vec3 ViewFrustum::getOrigin() const noexcept
	{
		return{
			m_frustum.Origin.x,
			m_frustum.Origin.y,
			m_frustum.Origin.z
		};
	}

	Quaternion ViewFrustum::getOrientation() const noexcept
	{
		return{
			m_frustum.Orientation.x,
			m_frustum.Orientation.y,
			m_frustum.Orientation.z,
			m_frustum.Orientation.w,
		};
	}

	Sphere ViewFrustum::computeBoundingSphere() const noexcept
	{
		DirectX::BoundingSphere result;
		DirectX::BoundingSphere::CreateFromFrustum(result, m_frustum);
		return detail::ToSphere(result);
	}

	const ViewFrustum& ViewFrustum::drawFrame(const ColorF& color) const
	{
		const std::array<Vec3, 8> c = getCorners();

		Line3D{ c[0], c[1] }.draw(color);
		Line3D{ c[1], c[3] }.draw(color);
		Line3D{ c[3], c[2] }.draw(color);
		Line3D{ c[2], c[0] }.draw(color);

		Line3D{ c[0], c[4] }.draw(color);
		Line3D{ c[1], c[5] }.draw(color);
		Line3D{ c[2], c[6] }.draw(color);
		Line3D{ c[3], c[7] }.draw(color);

		Line3D{ c[4], c[5] }.draw(color);
		Line3D{ c[5], c[7] }.draw(color);
		Line3D{ c[7], c[6] }.draw(color);
		Line3D{ c[6], c[4] }.draw(color);

		return *this;
	}

	const DirectX::BoundingFrustum& ViewFrustum::getData() const noexcept
	{
		return m_frustum;
	}
}
