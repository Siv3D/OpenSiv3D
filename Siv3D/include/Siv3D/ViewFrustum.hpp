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

# pragma once
# include <array>
# include "Common.hpp"
# include "PointVector.hpp"
# include "ColorHSV.hpp"
# include "SIMDMath.hpp"
# include "BasicCamera3D.hpp"

namespace s3d
{
	class ViewFrustum
	{
	public:

		SIV3D_NODISCARD_CXX20
		ViewFrustum() = default;

		SIV3D_NODISCARD_CXX20
		ViewFrustum(const BasicCamera3D& camera, double farClip) noexcept;

		SIV3D_NODISCARD_CXX20
		ViewFrustum(const BasicCamera3D& camera, double nearClip, double farClip) noexcept;

		SIV3D_NODISCARD_CXX20
		ViewFrustum(const Size& sceneSize, double verticalFOV, const Vec3& eyePosition, const Vec3& focusPosition, const Vec3& upDirection, double nearClip, double farClip) noexcept;

		[[nodiscard]]
		std::array<Vec3, 8> getCorners() const noexcept;


		[[nodiscard]]
		bool intersects(const Vec3& point) const noexcept;

		[[nodiscard]]
		bool intersects(const Triangle3D& triangle) const noexcept;

		[[nodiscard]]
		bool intersects(const Sphere& sphere) const noexcept;

		[[nodiscard]]
		bool intersects(const Box& box) const noexcept;

		[[nodiscard]]
		bool intersects(const OrientedBox& box) const noexcept;

		[[nodiscard]]
		bool intersects(const ViewFrustum& frustum) const noexcept;

		[[nodiscard]]
		Optional<float> intersects(const Ray& ray) const noexcept;


		[[nodiscard]]
		bool contains(const Vec3& point) const noexcept;

		[[nodiscard]]
		bool contains(const Triangle3D& triangle) const noexcept;

		[[nodiscard]]
		bool contains(const Sphere& sphere) const noexcept;

		[[nodiscard]]
		bool contains(const Box& box) const noexcept;

		[[nodiscard]]
		bool contains(const OrientedBox& box) const noexcept;

		[[nodiscard]]
		bool contains(const ViewFrustum& frustum) const noexcept;



		[[nodiscard]]
		Vec3 getOrigin() const noexcept;

		[[nodiscard]]
		Quaternion getOrientation() const noexcept;

		[[nodiscard]]
		Sphere computeBoundingSphere() const noexcept;


		const ViewFrustum& drawFrame(const ColorF& color = Palette::White) const;
		
		const DirectX::BoundingFrustum& getData() const noexcept;

	private:

		DirectX::BoundingFrustum m_frustum;
	};
}
