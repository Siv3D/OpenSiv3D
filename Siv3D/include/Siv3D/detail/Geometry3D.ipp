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

namespace s3d
{
	namespace detail
	{
		[[nodiscard]]
		Sphere ToSphere(const DirectX::BoundingSphere& sphere) noexcept;

		[[nodiscard]]
		Box ToBox(const DirectX::BoundingBox& box) noexcept;

		[[nodiscard]]
		OrientedBox ToOrientedBox(const DirectX::BoundingOrientedBox& box) noexcept;

		[[nodiscard]]
		DirectX::BoundingSphere FromSphere(const Sphere& sphere) noexcept;

		[[nodiscard]]
		DirectX::BoundingBox FromBox(const Box& box) noexcept;

		[[nodiscard]]
		DirectX::BoundingOrientedBox FromOrientedBox(const OrientedBox& box) noexcept;
	}
}
